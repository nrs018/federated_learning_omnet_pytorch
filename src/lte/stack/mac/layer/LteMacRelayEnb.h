//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#ifndef _LTE_LTEMACRELAYENB_H_
#define _LTE_LTEMACRELAYENB_H_

#include "lte/stack/mac/layer/LteMacEnb.h"

class LteAmc;

class SIMULTE_API LteMacRelayEnb : public LteMacEnb
{
  protected:
    virtual LteCellInfo* getCellInfo();
    virtual int getNumAntennas();

  public:
    LteMacRelayEnb();
    virtual ~LteMacRelayEnb();
};

#endif
