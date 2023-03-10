//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#ifndef _LTE_ALERTSENDER_H_
#define _LTE_ALERTSENDER_H_

#include <string.h>
#include <omnetpp.h>
#include "lte/common/LteCommon.h"
#include <inet/transportlayer/contract/udp/UdpSocket.h>
#include <inet/networklayer/common/L3Address.h>
#include <inet/networklayer/common/L3AddressResolver.h>
#include "lte/apps/alert/AlertPacket_m.h"

class SIMULTE_API AlertSender : public omnetpp::cSimpleModule
{
    inet::UdpSocket socket;

    //sender
    int nextSno_;
    int size_;

    omnetpp::simtime_t stopTime_;

    omnetpp::simsignal_t alertSentMsg_;
    // ----------------------------

    omnetpp::cMessage *selfSender_;

    int localPort_;
    int destPort_;
    inet::L3Address destAddress_;

    void sendAlertPacket();

  public:
    ~AlertSender();
    AlertSender();

  protected:

    virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }
    void initialize(int stage) override;
    void handleMessage(omnetpp::cMessage *msg) override;

    // utility: show current statistics above the icon
    virtual void refreshDisplay() const override;
};

#endif

