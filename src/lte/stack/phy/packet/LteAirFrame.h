//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#ifndef _LTE_LTEAIRFRAME_H_
#define _LTE_LTEAIRFRAME_H_

#include <omnetpp.h>

#include "lte/common/LteCommon.h"
#include "lte/common/LteControlInfo.h"
#include "lte/stack/phy/packet/LteAirFrame_m.h"

class SIMULTE_API LteAirFrame : public LteAirFrame_Base
{
  protected:
    RemoteUnitPhyDataVector remoteUnitPhyDataVector;
    public:
    LteAirFrame(const char *name = nullptr, int kind = 0) :
        LteAirFrame_Base(name, kind)
    {
    }

    LteAirFrame(const LteAirFrame& other) :
        LteAirFrame_Base(other)
    {
        operator=(other);
    }

    LteAirFrame& operator=(const LteAirFrame& other)
    {
        LteAirFrame_Base::operator=(other);
        this->remoteUnitPhyDataVector = other.remoteUnitPhyDataVector;

        // copy the attached control info, if any
        if (other.getControlInfo() != nullptr)
        {
            UserControlInfo* info = omnetpp::check_and_cast<UserControlInfo*>(other.getControlInfo());
            UserControlInfo* info_dup = info->dup();
            this->setControlInfo(info_dup);
        }
        return *this;
    }

    virtual LteAirFrame *dup() const
    {
        return new LteAirFrame(*this);
    }

    void addRemoteUnitPhyDataVector(RemoteUnitPhyData data);
    RemoteUnitPhyDataVector getRemoteUnitPhyDataVector();
};

Register_Class(LteAirFrame);

#endif
