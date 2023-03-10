//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#ifndef _LTE_LTEHARQPROCESSTXD2D_H_
#define _LTE_LTEHARQPROCESSTXD2D_H_

#include "lte/stack/mac/buffer/harq/LteHarqProcessTx.h"
#include "lte/stack/mac/buffer/harq_d2d/LteHarqUnitTxD2D.h"

/**
 * Container of H-ARQ units.
 * An H-ARQ process contains the units with id (acid + totalNumberOfProcesses * cw[i]), for each i.
 *
 * An H-ARQ buffer is made of H-ARQ processes.
 * An H-ARQ process is atomic for transmission, while H-ARQ units are atomic for
 * H-ARQ feedback.
 */
class SIMULTE_API LteHarqProcessTxD2D : public LteHarqProcessTx
{
  public:

    /**
     * Crates a new H-ARQ process, which is a container of H-ARQ units.
     *
     * @param acid H-ARQ process identifier
     * @param numUnits number of units contained in this process (MAX_CODEWORDS)
     * @param numProcesses number of processes contained in the H-ARQ buffer.
     * @return
     */
    LteHarqProcessTxD2D(unsigned char acid, unsigned int numUnits, unsigned int numProcesses, LteMacBase *macOwner,  LteMacBase *dstMac);
    virtual Packet *extractPdu(Codeword cw);
    virtual ~LteHarqProcessTxD2D();
};

#endif
