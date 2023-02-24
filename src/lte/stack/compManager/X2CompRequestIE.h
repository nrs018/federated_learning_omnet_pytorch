//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#ifndef _LTE_X2COMPREQUESTIE_H_
#define _LTE_X2COMPREQUESTIE_H_

#include "lte/x2/packet/X2InformationElement.h"

//
// X2CompRequestIE
// Base class for CoMP request messages
//
class SIMULTE_API X2CompRequestIE : public X2InformationElement
{
  protected:

  public:
    X2CompRequestIE()
    {
        type_ = COMP_REQUEST_IE;
        length_ = 0;
    }
    X2CompRequestIE(const X2CompRequestIE& other) :
        X2InformationElement()
    {
        operator=(other);
    }

    X2CompRequestIE& operator=(const X2CompRequestIE& other)
    {
        if (&other == this)
            return *this;
        X2InformationElement::operator=(other);
        return *this;
    }
    virtual X2CompRequestIE *dup() const
    {
        return new X2CompRequestIE(*this);
    }
    virtual ~X2CompRequestIE() {}
};

#endif
