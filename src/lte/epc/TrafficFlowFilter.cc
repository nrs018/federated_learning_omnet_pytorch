//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#include "lte/epc/TrafficFlowFilter.h"
#include <inet/networklayer/common/L3AddressResolver.h>
#include <inet/networklayer/ipv4/Ipv4Header_m.h>
#include <inet/common/IProtocolRegistrationListener.h>

#include "lte/common/LteControlInfo.h"

using namespace inet;

Define_Module(TrafficFlowFilter);

void TrafficFlowFilter::initialize(int stage) {
    // wait until all the IP addresses are configured
    if (stage == inet::INITSTAGE_TRANSPORT_LAYER) {
        // reading and setting owner type
        ownerType_ = selectOwnerType(par("ownerType"));

        //============= Reading XML files =============
        const char *filename = par("filterFileName");
        if (filename == nullptr || (!strcmp(filename, "")))
            error("TrafficFlowFilter::initialize - Error reading configuration from file %s",
                    filename);
        loadFilterTable(filename);
        //=============================================

        // register service processing IP-packets on the LTE Uu Link
        registerService(LteProtocol::ipv4uu, gate("internetFilterGateIn"),
                gate("internetFilterGateIn"));
    }
}

EpcNodeType TrafficFlowFilter::selectOwnerType(const char * type)
{
    EV << "TrafficFlowFilter::selectOwnerType - setting owner type to " << type << endl;
    if(strcmp(type,"ENODEB") == 0)
    return ENB;
    else if(strcmp(type,"PGW") == 0)
    return PGW;

    throw new cRuntimeError ("TrafficFlowFilter::selectOwnerType - unknown owner type [%s]. Aborting...",type);
}

void TrafficFlowFilter::handleMessage(cMessage *msg)
{
    EV << "TrafficFlowFilter::handleMessage - Received Packet:" << endl;
    EV << "name: " << msg->getFullName() << endl;

    Packet* pkt = check_and_cast<Packet *>(msg);

    // receive and read IP datagram
    // TODO: needs to be adapted for IPv6
    const auto& ipv4Header = pkt->peekAtFront<Ipv4Header>();
    const Ipv4Address &destAddr = ipv4Header->getDestAddress();
    const Ipv4Address &srcAddr = ipv4Header->getSrcAddress();
    pkt->addTagIfAbsent<DispatchProtocolReq>()->setProtocol(&Protocol::ipv4);
    pkt->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&Protocol::ipv4);

    // TODO check for source and dest port number

    Ipv4Address primaryKey , secondaryKeyAddr;

    EV << "TrafficFlowFilter::handleMessage - Received datagram : " << pkt->getName() << " - src[" << destAddr << "] - dest[" << srcAddr << "]\n";

    // run packet filter and associate a flowId to the connection (default bearer?)
    // search within tftTable the proper entry for this destination

    // check the ownerType and create the primary and secondary key consequently
    if(ownerType_==PGW)
    {
        primaryKey = destAddr;
        secondaryKeyAddr = srcAddr;
    }
    else    //(ownerType_==ENB)
    {
        primaryKey = srcAddr;
        secondaryKeyAddr = destAddr;
    }

    // TODO decide whether specifying src and dest ports or not
    TrafficFlowTemplate secondaryKey( secondaryKeyAddr , UNSPECIFIED_PORT , UNSPECIFIED_PORT );

    // search for the tftId in the table
    unsigned int tftId = findTrafficFlow( primaryKey , secondaryKey );
    if(tftId == UNSPECIFIED_TFT)
        error("TrafficFlowFilter::handleMessage - Cannot find corresponding tftId. Aborting...");

    // add control info to the normal ip datagram. This info will be read by the GTP-U application

    auto trafficFlowInfo = pkt->addTag<TftControlInfo>();
    trafficFlowInfo->setTft(tftId);

    EV << "TrafficFlowFilter::handleMessage - setting tft=" << tftId << endl;

    // send the datagram to the GTP-U module
    send(pkt,"gtpUserGateOut");
}

TrafficFlowTemplateId TrafficFlowFilter::findTrafficFlow(L3Address firstKey, TrafficFlowTemplate secondKey)
{
    TrafficFilterTemplateTable::iterator tftIt;
    tftIt = filterTable_.find(firstKey);

    // if no entry found
    if (tftIt == filterTable_.end())
    {
        EV << "TrafficFlowFilter::findTrafficFlow - Cannot find tft list for destAddress " << firstKey << "." << endl;
        return UNSPECIFIED_TFT;
    }

        // obtain the filter list associated to the given address
    TrafficFilterTemplateList & filterList = tftIt->second;

    // search for the second key within the list
    TrafficFilterTemplateList::iterator templIt = filterList.begin(),
        templFirst = filterList.begin(),
        templEt = filterList.end();

    // try searching for the full entry (src-dest addresses and ports)
    for (templIt = templFirst; templIt != templEt; templIt++)
    {
        if ((*templIt) == secondKey)
            return templIt->tftId;
    }
    EV << "TrafficFlowFilter::findTrafficFlow - Cannot find entry for the 4-tuple. Now trying with src and dest addresses" << endl;

    // if no result is found, try leaving port fields unspecified
    secondKey.srcPort = secondKey.destPort = UNSPECIFIED_PORT;
    for (templIt = templFirst; templIt != templEt; templIt++)
    {
        if ((*templIt) == secondKey)
            return templIt->tftId;
    }
    EV << "TrafficFlowFilter::findTrafficFlow - Cannot find entry for src and dest addresses. Now trying with first key only" << endl;

    // if no result is found again, search only for the first key
    secondKey.addr.set(Ipv4Address("0.0.0.0"));
    for (templIt = templFirst; templIt != templEt; templIt++)
    {
        if ((*templIt) == secondKey)
            return templIt->tftId;
    }

    EV << "TrafficFlowFilter::findTrafficFlow - Cannot find entry for destAddress " << firstKey << " and values: ["
       << secondKey.addr << "," << secondKey.destPort << "," << secondKey.srcPort << "]" << endl;

    return UNSPECIFIED_TFT;
}

bool TrafficFlowFilter::addTrafficFlow(L3Address firstKey, TrafficFlowTemplate tft)
{
    EV << "TrafficFlowFilter::addTrafficFlow - checking existence of an entry for destAddress " << firstKey << " and values: ["
       << tft.addr << "," << tft.destPort << "," << tft.srcPort << "]" << endl;

    // check if an entry for the given keys already exists
    TrafficFlowTemplateId ret= findTrafficFlow(firstKey,tft);
    if( ret ==! UNSPECIFIED_TFT )
    {
        EV << "TrafficFlowFilter::addTrafficFlow - skipping duplicate entry  with destAddress " << firstKey << " and values: ["
           << tft.addr << "," << tft.destPort << "," << tft.srcPort << "]" << endl;
        return false;
    }

    filterTable_[firstKey].push_back(tft);

    EV << "TrafficFlowFilter::addTrafficFlow - inserted entry: destAddr[" << firstKey << "] - TFT[" << tft.tftId << "]" << endl;
    return true;
}

void TrafficFlowFilter::loadFilterTable(const char * filterTableFile)
{
    // create default entries
    L3Address destAddr(Ipv4Address("0.0.0.0")), srcAddr(Ipv4Address("0.0.0.0"));
    unsigned int destPort = UNSPECIFIED_PORT;
    unsigned int srcPort = UNSPECIFIED_PORT;

    unsigned int tftId;
    L3Address primaryKey, secondaryKeyAddr;

    // tft attributes management
    const unsigned int numAttributes = 7;
    char const * attributes[numAttributes] = { "destAddr", "tftId", "destName", "srcAddr", "srcName", "srcPort",
        "destPort" };
    enum attributes
    {
        DEST_ADDR, TFT_ID, DEST_NAME, SRC_ADDR, SRC_NAME, SRC_PORT, DEST_PORT
    };
    char const * temp[numAttributes]; // this will keep the value of attributes as read from XML file

    // attribute iterator
    unsigned int attrId = 0;

    // open and check xml file
    EV << "TrafficFlowFilter::loadFilterTable - reading file " << filterTableFile << endl;
    cXMLElement* config = getEnvir()->getXMLDocument(filterTableFile);
    if (config == nullptr)
        error("TrafficFlowFilter::loadFilterTable: Cannot read configuration from file: %s", filterTableFile);

    // obtain reference to teidTable
    cXMLElement* filterNode = config->getElementByPath("filterTable");
    if (filterNode == nullptr)
        error("TrafficFlowFilter::loadFilterTable: No configuration for teidTable");

    // obtain a list of nodes contained in the filterTable Tag
    cXMLElementList tftList = filterNode->getChildren();

    // foreach tft element in the list, read the parameters and fill the tft table
    for (cXMLElementList::iterator tftIt = tftList.begin(); tftIt != tftList.end(); tftIt++)
    {
        std::string elementName = (*tftIt)->getTagName();
        if ((elementName == "filter"))
        {
            // clean attributes
            for (attrId = 0; attrId < numAttributes; ++attrId)
                temp[attrId] = nullptr;

            // read each attribute into the temp vector
            for (attrId = 0; attrId < numAttributes; ++attrId)
            {
                temp[attrId] = (*tftIt)->getAttribute(attributes[attrId]);
                if (temp[attrId] == nullptr && attributes[attrId])
                {
                    EV << "TrafficFlowFilter::loadFilterTable - attribute " << attributes[attrId] << " unspecified." << endl;
                }
            }

                    // process each attribute
                    // check and save tftID. This field is mandatory
            if (temp[TFT_ID] == nullptr)
            {
                error(
                    "TrafficFlowFilter::loadFilterTable - attribute tftId MUST be specified for every traffic filter.");
            }
            else
                tftId = atoi(temp[TFT_ID]);

            // read src and dest port values. These two fields are optional
            if (temp[DEST_PORT] != nullptr)
                destPort = atoi(temp[DEST_PORT]);
            if (temp[SRC_PORT] != nullptr)
                srcPort = atoi(temp[SRC_PORT]);

            //===================== Source and Destination addresses management =====================
            // NOTE that the behavior of this part depends on the node type of trafficFlowFilter owner:
            // - in case of ENB, the filterTable will be indexed by srcAddr at the first level. Thus srcAddress or srcName fields are mandatory
            // - in case of PGW, the filterTable will be indexed by destAddr at the first level. Thus destAddress or destName fields are mandatory

            // at least one between destAddr and destName MUST be specified in case of PGW
            // try to read the destination address for first
            if (temp[DEST_ADDR] != nullptr)
                destAddr.set(Ipv4Address(temp[DEST_ADDR]));
            else // if no dest address has been specified, try to resolve node name
            {
                if (temp[DEST_NAME] != nullptr)
                {
                    EV << "TrafficFlowFilter::loadFilterTable - resolving IP address for host name " << temp[DEST_NAME] << endl;
                    destAddr = L3AddressResolver().resolve(temp[DEST_NAME]);
                }
                else if(ownerType_==PGW)
                error("TrafficFlowFilter::loadFilterTable - unable to resolve any address for tftID[%i] in PGW.",tftId);
            }

                    // at least one between srcAddr and srcName MUST be specified in case of ENB
                    // try to read the source address for first
            if (temp[SRC_ADDR] != nullptr)
                srcAddr.set(Ipv4Address(temp[SRC_ADDR]));
            else // if no src address has been specified, try to resolve node name
            {
                if (temp[SRC_NAME] != nullptr)
                {
                    EV << "TrafficFlowFilter::loadFilterTable - resolving IP address for host name " << temp[SRC_NAME] << endl;
                    srcAddr = L3AddressResolver().resolve(temp[SRC_NAME]);
                }
                else if(ownerType_==ENB)
                error("TrafficFlowFilter::loadFilterTable - unable to resolve any address for tftID[%i] in ENB",tftId);
            }

                    // check the owner type, and choose the primary and secondary key values accordingly
            if (ownerType_ == ENB)
            {
                primaryKey = srcAddr;
                secondaryKeyAddr = destAddr;
            }
            else // (ownerType_==PGW)
            {
                primaryKey = destAddr;
                secondaryKeyAddr = srcAddr;
            }
            //=======================================================================================

            // create the new entry...finally
            TrafficFlowTemplate secondaryKey(secondaryKeyAddr, destPort, srcPort);
            secondaryKey.tftId = tftId;

            // TODO decide what to do in case of duplicate entries
            if (!addTrafficFlow(primaryKey, secondaryKey))
                ;
            else
                ;
        }
    }
}
