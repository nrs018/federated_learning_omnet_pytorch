//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#include "lte/stack/pdcp_rrc/layer/entity/LtePdcpEntity.h"

LtePdcpEntity::LtePdcpEntity()
{
    sequenceNumber_ = 0;
}

LtePdcpEntity::~LtePdcpEntity()
{
}

unsigned int LtePdcpEntity::nextSequenceNumber()
{
    return sequenceNumber_++;
}
