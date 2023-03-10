// 
//                           SimuLTE
// 
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself, 
// and cannot be removed from it.
// 

#include "lte/stack/phy/packet/LteFeedbackPkt.h"

LteFeedbackDoubleVector LteFeedbackPkt::getLteFeedbackDoubleVectorDl() const
{
    return lteFeedbackDoubleVectorDl_;
}
LteFeedbackDoubleVector LteFeedbackPkt::getLteFeedbackDoubleVectorUl() const
{
    return lteFeedbackDoubleVectorUl_;
}
std::map<MacNodeId, LteFeedbackDoubleVector> LteFeedbackPkt::getLteFeedbackDoubleVectorD2D() const
{
    return lteFeedbackMapDoubleVectorD2D_;
}
void LteFeedbackPkt::setLteFeedbackDoubleVectorDl(LteFeedbackDoubleVector lteFeedbackDoubleVector)
{
    lteFeedbackDoubleVectorDl_ = lteFeedbackDoubleVector;
}
void LteFeedbackPkt::setLteFeedbackDoubleVectorUl(LteFeedbackDoubleVector lteFeedbackDoubleVector)
{
    lteFeedbackDoubleVectorUl_ = lteFeedbackDoubleVector;
}
void LteFeedbackPkt::setLteFeedbackDoubleVectorD2D(MacNodeId peerId, LteFeedbackDoubleVector lteFeedbackDoubleVector)
{
    lteFeedbackMapDoubleVectorD2D_[peerId] = lteFeedbackDoubleVector;
}
void LteFeedbackPkt::setSourceNodeId(MacNodeId id)
{
    sourceNodeId_ = id;
}
MacNodeId LteFeedbackPkt::getSourceNodeId() const
{
    return sourceNodeId_;
}
