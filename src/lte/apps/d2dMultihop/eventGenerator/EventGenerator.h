//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#ifndef _LTE_EVENTGENERATOR_H_
#define _LTE_EVENTGENERATOR_H_

#include <string.h>
#include <omnetpp.h>
#include "lte/common/LteCommon.h"
#include "lte/apps/d2dMultihop/MultihopD2D.h"
#include "lte/corenetwork/binder/LteBinder.h"
#include "lte/stack/phy/layer/LtePhyBase.h"

class MultihopD2D;

class SIMULTE_API EventGenerator : public omnetpp::cSimpleModule
{
    omnetpp::cMessage *selfMessage_;

    uint32_t eventId_;
    LteBinder* binder_;

    bool singleEventSource_;

    // store references to the app modules
    std::vector<MultihopD2D*> appVector_;

    // store LTE IDs of the nodes
    std::set<MacNodeId> lteNodeIdSet_;

    // store references to the PHY modules
    // (to speed up position retrieval)
    std::map<MacNodeId, LtePhyBase*> lteNodePhy_;

    // notify a node to start an event dissemination
    void notifyEvent();

protected:

    virtual void initialize() override;
    virtual void handleMessage(omnetpp::cMessage *msg) override;

  public:
    EventGenerator();
    ~EventGenerator();

    void computeTargetNodeSet(std::set<MacNodeId>& targetSet, MacNodeId sourceId, double maxBroadcastRadius = -1.0);
    void registerNode(MultihopD2D* app, MacNodeId lteNodeId);
    void unregisterNode(MultihopD2D* app, MacNodeId lteNodeId);
};

#endif

