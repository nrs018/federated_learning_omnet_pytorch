//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#ifndef _LTE_LTEMACUED2D_H_
#define _LTE_LTEMACUED2D_H_

#include "lte/stack/mac/layer/LteMacUe.h"
#include "lte/stack/mac/layer/LteMacEnbD2D.h"
#include "lte/stack/mac/buffer/harq_d2d/LteHarqBufferTxD2D.h"

class LteSchedulingGrant;
class LteSchedulerUeUl;
class LteBinder;

class SIMULTE_API LteMacUeD2D : public LteMacUe
{
    // reference to the eNB
    LteMacEnbD2D* enb_;

    // RAC Handling variables
    bool racD2DMulticastRequested_;
    // Multicast D2D BSR handling
    bool bsrD2DMulticastTriggered_;

    omnetpp::simsignal_t rcvdD2DModeSwitchNotification_;

    // if true, use the preconfigured TX params for transmission, else use that signaled by the eNB
    bool usePreconfiguredTxParams_;
    UserTxParams* preconfiguredTxParams_;
    UserTxParams* getPreconfiguredTxParams();  // build and return new user tx params

  protected:

    /**
     * Reads MAC parameters for ue and performs initialization.
     */
    virtual void initialize(int stage) override;

    /**
     * Analyze gate of incoming packet
     * and call proper handler
     */
    virtual void handleMessage(omnetpp::cMessage *msg) override;

    /**
     * Main loop
     */
    virtual void handleSelfMessage() override;

    virtual void macHandleGrant(omnetpp::cPacket* pkt) override;

    /*
     * Checks RAC status
     */
    virtual void checkRAC() override;

    /*
     * Receives and handles RAC responses
     */
    virtual void macHandleRac(omnetpp::cPacket* pkt) override;

    void macHandleD2DModeSwitch(omnetpp::cPacket* pkt);

    virtual Packet* makeBsr(int size);

    /**
     * macPduMake() creates MAC PDUs (one for each CID)
     * by extracting SDUs from Real Mac Buffers according
     * to the Schedule List.
     * It sends them to H-ARQ (at the moment lower layer)
     *
     * On UE it also adds a BSR control element to the MAC PDU
     * containing the size of its buffer (for that CID)
     */
    virtual void macPduMake(MacCid cid=0) override;

  public:
    LteMacUeD2D();
    virtual ~LteMacUeD2D();

    virtual bool isD2DCapable() override
    {
        return true;
    }

    virtual void triggerBsr(MacCid cid)
    {
        if (connDesc_[cid].getDirection() == D2D_MULTI)
            bsrD2DMulticastTriggered_ = true;
        else
            bsrTriggered_ = true;
    }
    virtual void doHandover(MacNodeId targetEnb) override;
};

#endif
