//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#ifndef _LTE_LTEFEEDBACKCOMPUTATION_H_
#define _LTE_LTEFEEDBACKCOMPUTATION_H_

#include "lte/stack/phy/feedback/LteFeedback.h"

class SIMULTE_API LteFeedbackComputation
{
  public:
    LteFeedbackComputation();
    virtual ~LteFeedbackComputation();
    /**
     * Interface for Feedback computation
     *
     * @param Feedback type (Wideband, allbands ecc)
     * @param RbAllocationType Allocation type (distributed or localized)
     * @param Txmode current txmode
     * @param number of codeword for each antenna
     * @param Number of preferred bands
     * @return Vector of Vector of LteFeedback indexes: Ru and Txmode
     */
    virtual LteFeedbackDoubleVector computeFeedback(FeedbackType fbType, RbAllocationType rbAllocationType,
        TxMode currentTxMode,
        std::map<Remote, int> antennaCws, int numPreferredBands, FeedbackGeneratorType feedbackGeneratortype,
        int numRus, std::vector<double> snr, MacNodeId id = 0)=0;
    /**
     * Interface for Feedback computation
     *
     * @param Remote antenna remote
     * @param Feedback type (Wideband, allbands ecc)
     * @param RbAllocationType Allocation type (distributed or localized)
     * @param Txmode current txmode
     * @param number of codeword for the selected antenna
     * @param Number of preferred bands
     * @return Vector of LteFeedback indexes: Txmode
     */
    virtual LteFeedbackVector computeFeedback(const Remote remote, FeedbackType fbType,
        RbAllocationType rbAllocationType, TxMode currentTxMode,
        int antennaCws, int numPreferredBands, FeedbackGeneratorType feedbackGeneratortype, int numRus,
        std::vector<double> snr, MacNodeId id = 0)=0;
    /**
     * Interface for Feedback computation
     *
     * @param Remote antenna remote
     * @param Selected Txmode txmode
     * @param Remote antenna remote
     * @param Feedback type (Wideband, allbands ecc)
     * @param RbAllocationType Allocation type (distributed or localized)
     * @param number of codeword for the selected antenna
     * @param Number of preferred bands
     * @return  LteFeedback
     */
    virtual LteFeedback computeFeedback(const Remote remote, TxMode txmode, FeedbackType fbType,
        RbAllocationType rbAllocationType,
        int antennaCws, int numPreferredBands, FeedbackGeneratorType feedbackGeneratortype, int numRus,
        std::vector<double> snr, MacNodeId id = 0)=0;
};

#endif
