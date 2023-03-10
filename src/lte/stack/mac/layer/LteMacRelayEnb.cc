//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#include "lte/stack/mac/layer/LteMacRelayEnb.h"

Define_Module(LteMacRelayEnb);

using namespace inet;

LteMacRelayEnb::LteMacRelayEnb()
{
    nodeType_ = RELAY;
}
LteMacRelayEnb::~LteMacRelayEnb()
{

}

LteCellInfo* LteMacRelayEnb::getCellInfo()
{
    MacNodeId masterId = getAncestorPar("masterId");
    OmnetId masterOmnetId = binder_->getOmnetId(masterId);
    return check_and_cast<LteCellInfo *>(getSimulation()->getModule(masterOmnetId)->getSubmodule("cellInfo"));
}

int LteMacRelayEnb::getNumAntennas()
{
    return 1;
}
