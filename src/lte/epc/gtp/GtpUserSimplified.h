//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#ifndef _LTE_GTP_USER_SIMPLIFIED_H_
#define _LTE_GTP_USER_SIMPLIFIED_H_

#include <omnetpp.h>
#include "inet/transportlayer/contract/udp/UdpSocket.h"
#include <inet/networklayer/common/InterfaceEntry.h>
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/ipv4/Ipv4Header_m.h"
#include "lte/epc/gtp/TftControlInfo_m.h"
#include "lte/epc/gtp/GtpUserMsg_m.h"
#include "lte/corenetwork/binder/LteBinder.h"
#include <map>
#include "lte/epc/gtp_common.h"

/**
 * GtpUserSimplified is used for building data tunnels between GTP peers.
 * GtpUserSimplified can receive two kind of packets:
 * a) IP datagram from a trafficFilter. Those packets are labeled with a tftId
 * b) GtpUserSimplifiedMsg from UDP-IP layers.
 *
 */
class SIMULTE_API GtpUserSimplified : public omnetpp::cSimpleModule
{
    inet::UdpSocket socket_;
    int localPort_;

    // reference to the LTE Binder module
    LteBinder* binder_;
    /*
     * This table contains mapping between TrafficFlowTemplate (TFT) identifiers and the IP address
     * of the destination eNodeB. This table is populated by the eNodeBs at the beginning of the simulation
     */
    std::map<TrafficFlowTemplateId, inet::Ipv4Address> tftTable_;

    // the GTP protocol Port
    unsigned int tunnelPeerPort_;

    // IP address of the PGW
    inet::L3Address pgwAddress_;

    // specifies the type of the node that contains this filter (it can be ENB or PGW)
    EpcNodeType ownerType_;

    // determine gtpuser runs on PGW oder eNB
    EpcNodeType selectOwnerType(const char * type);

    // detect LTE interface
    inet::InterfaceEntry* detectInterface();
    inet::InterfaceEntry* ie_;

  protected:

    virtual int numInitStages() const { return inet::NUM_INIT_STAGES; }
    virtual void initialize(int stage);
    virtual void handleMessage(inet::cMessage *msg);

    // receive and IP Datagram from the traffic filter, encapsulates it in a GTP-U packet than forwards it to the proper next hop
    void handleFromTrafficFlowFilter(inet::Packet * datagram);

    // receive a GTP-U packet from UDP, reads the TEID and decides whether performing label switching or removal
    void handleFromUdp(inet::Packet * gtpMsg);
};

#endif
