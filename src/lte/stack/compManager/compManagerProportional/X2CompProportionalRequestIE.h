//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#ifndef _LTE_X2COMPPROPORTIONALREQUESTIE_H_
#define _LTE_X2COMPPROPORTIONALREQUESTIE_H_

#include "lte/stack/compManager/X2CompRequestIE.h"

//
// X2CompProportionalRequestIE
//
class SIMULTE_API X2CompProportionalRequestIE : public X2CompRequestIE
{
  protected:

    // number of "ideally" required blocks to satisfy the queue of all UEs
    uint32_t numBlocks_;

  public:
    X2CompProportionalRequestIE()
    {
        type_ = COMP_PROP_REQUEST_IE;
        length_ = sizeof(uint32_t);
    }
    X2CompProportionalRequestIE(const X2CompProportionalRequestIE& other) :
        X2CompRequestIE()
    {
        operator=(other);
    }

    X2CompProportionalRequestIE& operator=(const X2CompProportionalRequestIE& other)
    {
        if (&other == this)
            return *this;
        numBlocks_ = other.numBlocks_;
        X2CompRequestIE::operator=(other);
        return *this;
    }
    virtual X2CompProportionalRequestIE *dup() const
    {
        return new X2CompProportionalRequestIE(*this);
    }
    virtual ~X2CompProportionalRequestIE() {}

    // getter/setter methods
    void setNumBlocks(unsigned int numBlocks) { numBlocks_ = numBlocks; }
    unsigned int getNumBlocks() { return numBlocks_; }

};

#endif
