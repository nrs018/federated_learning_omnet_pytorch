//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#ifndef _LTE_LTEFEEDBACKPKT_H_
#define _LTE_LTEFEEDBACKPKT_H_

#include "lte/stack/phy/packet/LteFeedbackPkt_m.h"
#include "lte/stack/phy/feedback/LteFeedback.h"

class SIMULTE_API LteFeedbackPkt : public LteFeedbackPkt_Base
{
private:
    void copy(const LteFeedbackPkt& other) {
        lteFeedbackDoubleVectorDl_ = other.lteFeedbackDoubleVectorDl_;
        lteFeedbackDoubleVectorUl_ = other.lteFeedbackDoubleVectorUl_;
        lteFeedbackMapDoubleVectorD2D_ = other.lteFeedbackMapDoubleVectorD2D_;
        sourceNodeId_ = other.sourceNodeId_;
        lteFeedbackDoubleVectorDl_ = other.lteFeedbackDoubleVectorDl_;
        lteFeedbackDoubleVectorUl_ = other.lteFeedbackDoubleVectorUl_;
        sourceNodeId_ = other.sourceNodeId_;
    }
  protected:
    // vector of vector with RU and TxMode as indexes
    LteFeedbackDoubleVector lteFeedbackDoubleVectorDl_;
    // vector of vector with RU and TxMode as indexes
    LteFeedbackDoubleVector lteFeedbackDoubleVectorUl_;
    // map of vector of vector with peering UE, RU and TxMode as indexes
    std::map<MacNodeId, LteFeedbackDoubleVector> lteFeedbackMapDoubleVectorD2D_;
    //MacNodeId of the source
    MacNodeId sourceNodeId_;
    public:
    LteFeedbackPkt() :
        LteFeedbackPkt_Base()
    {
    }
    LteFeedbackPkt(const LteFeedbackPkt& other) :
        LteFeedbackPkt_Base(other)
    {
        copy(other);
    }
    LteFeedbackPkt& operator=(const LteFeedbackPkt& other)
    {
        if (this == &other) return *this;
        LteFeedbackPkt_Base::operator=(other);
        copy(other);
        return *this;
    }
    virtual LteFeedbackPkt *dup() const
    {
        return new LteFeedbackPkt(*this);
    }
    LteFeedbackDoubleVector getLteFeedbackDoubleVectorDl() const;
    void setLteFeedbackDoubleVectorDl(LteFeedbackDoubleVector lteFeedbackDoubleVector_);
    LteFeedbackDoubleVector getLteFeedbackDoubleVectorUl() const;
    void setLteFeedbackDoubleVectorUl(LteFeedbackDoubleVector lteFeedbackDoubleVector_);
    std::map<MacNodeId, LteFeedbackDoubleVector> getLteFeedbackDoubleVectorD2D() const;
    void setLteFeedbackDoubleVectorD2D(MacNodeId peerId, LteFeedbackDoubleVector lteFeedbackDoubleVector_);
    void setSourceNodeId(MacNodeId id);
    MacNodeId getSourceNodeId() const;
};

#endif
