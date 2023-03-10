//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#include "lte/stack/pdcp_rrc/layer/LtePdcpRrcUeD2D.h"
#include <inet/networklayer/common/L3AddressResolver.h>
#include "lte/stack/d2dModeSelection/D2DModeSwitchNotification_m.h"

Define_Module(LtePdcpRrcUeD2D);

using namespace inet;
using namespace omnetpp;

MacNodeId LtePdcpRrcUeD2D::getDestId(FlowControlInfo* lteInfo)
{
    Ipv4Address destAddr = Ipv4Address(lteInfo->getDstAddr());
    MacNodeId destId = binder_->getMacNodeId(destAddr);

    // check if the destination is inside the LTE network
    if (destId == 0 || getDirection(destId) == UL)  // if not, the packet is destined to the eNB
    {
        // UE is subject to handovers: master may change
        return binder_->getNextHop(nodeId_);
    }

    return destId;
}

/*
 * Upper Layer handlers
 */
void LtePdcpRrcUeD2D::fromDataPort(cPacket *pktAux)
{
    emit(receivedPacketFromUpperLayer, pktAux);

    // Control Informations
    auto pkt = check_and_cast<Packet *>(pktAux);
    auto lteInfo = pkt->getTag<FlowControlInfo>();
    setTrafficInformation(pkt, lteInfo);
    headerCompress(pkt);

    // get destination info
    Ipv4Address destAddr = Ipv4Address(lteInfo->getDstAddr());
    MacNodeId destId;

    // the direction of the incoming connection is a D2D_MULTI one if the application is of the same type,
    // else the direction will be selected according to the current status of the UE, i.e. D2D or UL
    if (destAddr.isMulticast())
    {
        binder_->addD2DMulticastTransmitter(nodeId_);

        lteInfo->setDirection(D2D_MULTI);

        // assign a multicast group id
        // multicast IP addresses are 224.0.0.0/4.
        // We consider the host part of the IP address (the remaining 28 bits) as identifier of the group,
        // so as it is univocally determined for the whole network
        uint32 address = Ipv4Address(lteInfo->getDstAddr()).getInt();
        uint32 mask = ~((uint32)255 << 28);      // 0000 1111 1111 1111
        uint32 groupId = address & mask;
        lteInfo->setMulticastGroupId((int32)groupId);
        lteInfo->setDestId(nodeId_);             // destId is meaningless for multicast D2D (we use the id of the source for statistic purposes at lower levels)
    }
    else
    {
        destId = binder_->getMacNodeId(destAddr);
        if (destId != 0)  // the destination is a UE within the LTE network
        {
            if (binder_->checkD2DCapability(nodeId_, destId))
            {
                // this way, we record the ID of the endpoints even if the connection is currently in IM
                // this is useful for mode switching
                lteInfo->setD2dTxPeerId(nodeId_);
                lteInfo->setD2dRxPeerId(destId);
            }
            else
            {
                lteInfo->setD2dTxPeerId(0);
                lteInfo->setD2dRxPeerId(0);
            }

            // set actual flow direction based (D2D/UL) based on the current mode (DM/IM) of this peering
            lteInfo->setDirection(getDirection(destId));
        }
        else  // the destination is outside the LTE network
        {
            lteInfo->setDirection(UL);
            lteInfo->setD2dTxPeerId(0);
            lteInfo->setD2dRxPeerId(0);
        }

        destId = getDestId(lteInfo);
        lteInfo->setDestId(destId);
    }

    // Cid Request
    EV << NOW << " LtePdcpRrcUeD2D : Received CID request for Traffic [ " << "Source: "
       << Ipv4Address(lteInfo->getSrcAddr()) << "@" << lteInfo->getSrcPort()
       << " Destination: " << destAddr << "@" << lteInfo->getDstPort()
       << " , Direction: " << dirToA((Direction)lteInfo->getDirection()) << " ]\n";

    /*
     * Different lcid for different directions of the same flow are assigned.
     * RLC layer will create different RLC entities for different LCIDs
     */

    LogicalCid mylcid;
    if ((mylcid = ht_->find_entry(lteInfo->getSrcAddr(), lteInfo->getDstAddr(),
        lteInfo->getSrcPort(), lteInfo->getDstPort(), lteInfo->getDirection())) == 0xFFFF)
    {
        // LCID not found

        // assign a new LCID to the connection
        mylcid = lcid_++;

        EV << "LtePdcpRrcUeD2D : Connection not found, new CID created with LCID " << mylcid << "\n";

        ht_->create_entry(lteInfo->getSrcAddr(), lteInfo->getDstAddr(),
            lteInfo->getSrcPort(), lteInfo->getDstPort(), lteInfo->getDirection(), mylcid);
    }

    EV << "LtePdcpRrcUeD2D : Assigned Lcid: " << mylcid << "\n";
    EV << "LtePdcpRrcUeD2D : Assigned Node ID: " << nodeId_ << "\n";

    // get the PDCP entity for this LCID
    LtePdcpEntity* entity = getEntity(mylcid);

    // get the sequence number for this PDCP SDU.
    // Note that the numbering depends on the entity the packet is associated to.
    unsigned int sno = entity->nextSequenceNumber();

    // set sequence number
    lteInfo->setSequenceNumber(sno);
    // set some flow-related info
    lteInfo->setLcid(mylcid);
    lteInfo->setSourceId(nodeId_);

    unsigned int headerLength;
    std::string portName;
    omnetpp::cGate* gate;

    switch(lteInfo->getRlcType()){
    case UM:
        headerLength = PDCP_HEADER_UM;
        portName = "UM_Sap$o";
        gate = umSap_[OUT_GATE];
        break;
    case AM:
        headerLength = PDCP_HEADER_AM;
        portName = "AM_Sap$o";
        gate = amSap_[OUT_GATE];
        break;
    case TM:
        portName = "TM_Sap$o";
        gate = tmSap_[OUT_GATE];
        headerLength = 1;
        break;
    default:
        throw cRuntimeError("LtePdcpRrcUeD2D::fromDataport(): invalid RlcType %d", lteInfo->getRlcType());
        portName = "undefined";
        gate = nullptr;
        headerLength = 1;
    }

    // PDCP Packet creation
    auto pdcpPkt = makeShared<LtePdcpPdu>();
    pdcpPkt->setChunkLength(B(headerLength));
    pkt->trim();
    pkt->insertAtFront(pdcpPkt);

    EV << "LtePdcp : Preparing to send "
       << lteTrafficClassToA((LteTrafficClass) lteInfo->getTraffic())
       << " traffic\n";
    EV << "LtePdcp : Packet size " << pkt->getByteLength() << " Bytes\n";
    EV << "LtePdcp : Sending packet " << pkt->getName() << " on port "
       << portName << std::endl;

    pkt->addTagIfAbsent<PacketProtocolTag>()->setProtocol(&LteProtocol::pdcp);

    // Send message
    send(pkt, gate);
    emit(sentPacketToLowerLayer, pkt);
}

void LtePdcpRrcUeD2D::handleMessage(cMessage* msg)
{
    cPacket* pktAux = check_and_cast<cPacket *>(msg);

    // check whether the message is a notification for mode switch
    if (strcmp(pktAux->getName(),"D2DModeSwitchNotification") == 0)
    {
        EV << "LtePdcpRrcUeD2D::handleMessage - Received packet " << pktAux->getName() << " from port " << pktAux->getArrivalGate()->getName() << endl;

        auto pkt = check_and_cast<inet::Packet *>(pktAux);
        auto switchPkt = pkt->peekAtFront<D2DModeSwitchNotification>();

        // call handler
        pdcpHandleD2DModeSwitch(switchPkt->getPeerId(), switchPkt->getNewMode());

        delete pktAux;
    }
    else
    {
        LtePdcpRrcBase::handleMessage(msg);
    }
}

void LtePdcpRrcUeD2D::pdcpHandleD2DModeSwitch(MacNodeId peerId, LteD2DMode newMode)
{
    EV << NOW << " LtePdcpRrcUeD2D::pdcpHandleD2DModeSwitch - peering with UE " << peerId << " set to " << d2dModeToA(newMode) << endl;

    // add here specific behavior for handling mode switch at the PDCP layer
}

