/*
 * LteSummaryFeedback.cc
 *
 *  Created on: Oct 13, 2019
 *      Author: q
 */
#include "lte/common/LteCommon.h"

#include "lte/stack/phy/feedback/LteSummaryFeedback.h"

using namespace omnetpp;

double LteSummaryFeedback::confidence(simtime_t creationTime) const {
    simtime_t delta = simTime() - creationTime;

    if (delta < confidenceLowerBound_)
        return 1.0;
    if (delta > confidenceUpperBound_)
        return 0.0;
    return (1.0
            - (delta - confidenceLowerBound_)
                    / (confidenceUpperBound_ - confidenceLowerBound_));
}

void LteSummaryFeedback::reset() {
    ri_ = NORANK;
    tRi_ = simTime();

    cqi_ = std::vector<CqiVector>(totCodewords_,
            CqiVector(logicalBandsTot_, NOSIGNALCQI));
    tCqi_ = std::vector<std::vector<simtime_t> >(totCodewords_,
            std::vector<simtime_t>(logicalBandsTot_, simTime()));

    pmi_ = PmiVector(logicalBandsTot_, NOPMI);
    tPmi_ = std::vector<simtime_t>(logicalBandsTot_, simTime());
    valid_ = false;
}

void LteSummaryFeedback::print(MacCellId cellId, MacNodeId nodeId,
        const Direction dir, TxMode txm, const char* s) const {
    bool debug = false;
    if (debug) {
        EV << NOW << " " << s << "     LteSummaryFeedback\n";
        EV << NOW << " " << s << " CellId: " << cellId << "\n";
        EV << NOW << " " << s << " NodeId: " << nodeId << "\n";
        EV << NOW << " " << s << " Direction: " << dirToA(dir) << "\n";
        EV << NOW << " " << s << " TxMode: " << txModeToA(txm) << "\n";
        EV << NOW << " " << s << " -------------------------\n";

        Rank ri = getRi();
        double c = getRiConfidence();
        EV << NOW << " " << s << " RI = " << ri << " [" << c << "]\n";

        unsigned char codewords = getTotCodewords();
        unsigned char bands = getTotLogicalBands();
        for (Codeword cw = 0; cw < codewords; ++cw) {
            EV << NOW << " " << s << " CQI[" << cw << "] = {";
            if (bands > 0) {
                EV << getCqi(cw, 0);
                for (Band b = 1; b < bands; ++b)
                    EV << ", " << getCqi(cw, b);
            }
            EV << "} [{";
            if (bands > 0) {
                c = getCqiConfidence(cw, 0);
                EV << c;
                for (Band b = 1; b < bands; ++b) {
                    c = getCqiConfidence(cw, b);
                    EV << ", " << c;
                }
            }
            EV << "}]\n";
        }

        EV << NOW << " " << s << " PMI = {";
        if (bands > 0) {
            EV << getPmi(0);
            for (Band b = 1; b < bands; ++b)
                EV << ", " << getPmi(b);
        }
        EV << "} [{";
        if (bands > 0) {
            c = getPmiConfidence(0);
            EV << c;
            for (Band b = 1; b < bands; ++b) {
                c = getPmiConfidence(b);
                EV << ", " << c;
            }
        }
        EV << "}]\n";
    }
}



