//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#ifndef _LTE_X2HANDOVERCONTROLMSG_H_
#define _LTE_X2HANDOVERCONTROLMSG_H_

#include "lte/x2/packet/LteX2Message.h"
#include "lte/common/LteCommon.h"

/**
 * @class X2HandoverControlMsg
 *
 * Class derived from LteX2Message
 * It defines the message exchanged between Handover managers
 */
class SIMULTE_API X2HandoverControlMsg : public LteX2Message
{

  public:

    X2HandoverControlMsg();

    X2HandoverControlMsg(const X2HandoverControlMsg& other);

    X2HandoverControlMsg& operator=(const X2HandoverControlMsg& other);

    virtual X2HandoverControlMsg* dup() const;

    virtual ~X2HandoverControlMsg();
};

#endif

