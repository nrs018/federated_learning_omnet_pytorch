//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#ifndef _LTE_X2COMPREPLYIE_H_
#define _LTE_X2COMPREPLYIE_H_

#include "lte/x2/packet/X2InformationElement.h"


//
// X2CompReplyIE
// Base class for CoMP reply messages
//
class SIMULTE_API X2CompReplyIE : public X2InformationElement
{
  protected:

  public:
    X2CompReplyIE()
    {
        type_ = COMP_REPLY_IE;
        length_ = 0;
    }
    X2CompReplyIE(const X2CompReplyIE& other) :
        X2InformationElement()
    {
        operator=(other);
    }

    X2CompReplyIE& operator=(const X2CompReplyIE& other)
    {
        if (&other == this)
            return *this;
        X2InformationElement::operator=(other);
        return *this;
    }
    virtual X2CompReplyIE *dup() const
    {
        return new X2CompReplyIE(*this);
    }
    virtual ~X2CompReplyIE() {}
};

#endif
