#ifndef _BURSTRECEIVER_H_
#define _BURSTRECEIVER_H_

#include <string.h>
#include <omnetpp.h>

#include <inet/common/INETDefs.h>
#include <inet/transportlayer/contract/udp/UdpSocket.h>
#include <inet/networklayer/common/L3AddressResolver.h>

#include "lte/common/LteCommon.h"
#include "lte/apps/burst/BurstPacket_m.h"

using namespace inet;

class SIMULTE_API BurstReceiver : public cSimpleModule
{
    UdpSocket socket;

    int numReceived_;
    int recvBytes_;

    bool mInit_;

    simsignal_t burstRcvdPkt_;
    simsignal_t burstPktDelay_;

  protected:

    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    void initialize(int stage) override;
    void handleMessage(cMessage *msg) override;
};

#endif

