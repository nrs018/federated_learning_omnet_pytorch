//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#ifndef _LTE_X2COMPMSG_H_
#define _LTE_X2COMPMSG_H_

#include "lte/x2/packet/LteX2Message.h"
#include "lte/x2/packet/LteX2MsgSerializer.h"
#include "lte/common/LteCommon.h"

/**
 * @class X2CompMsg
 *
 * Class derived from LteX2Message
 * It defines the message exchanged between CoMP managers
 */
class SIMULTE_API X2CompMsg : public LteX2Message
{

  public:

    X2CompMsg();

    X2CompMsg(const X2CompMsg& other);

    X2CompMsg& operator=(const X2CompMsg& other);

    virtual X2CompMsg* dup() const;

    virtual ~X2CompMsg();
};

#endif

