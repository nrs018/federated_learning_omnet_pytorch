//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#ifndef _LTE_LTEPDCPRRCENBD2D_H_
#define _LTE_LTEPDCPRRCENBD2D_H_

#include <omnetpp.h>
#include "lte/stack/pdcp_rrc/layer/LtePdcpRrc.h"

/**
 * @class LtePdcp
 * @brief PDCP Layer
 *
 * This is the PDCP/RRC layer of LTE Stack (with D2D support).
 *
 */
class SIMULTE_API LtePdcpRrcEnbD2D : public LtePdcpRrcEnb
{

  protected:

    virtual void initialize(int stage) override;
    virtual void handleMessage(omnetpp::cMessage* msg) override;

    void handleControlInfo(omnetpp::cPacket* upPkt, FlowControlInfo* lteInfo) override
    {
        delete lteInfo;
    }

    /**
     * handler for data port
     * @param pkt incoming packet
     */
    virtual void fromDataPort(omnetpp::cPacket *pkt) override;

    void pdcpHandleD2DModeSwitch(MacNodeId peerId, LteD2DMode newMode);

  public:

};

#endif
