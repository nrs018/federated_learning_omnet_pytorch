//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#include "lte/stack/mac/scheduler/LteSchedulerEnbDl.h"
#include "lte/stack/mac/layer/LteMacEnb.h"
#include "lte/stack/mac/scheduler/LteScheduler.h"
#include "lte/stack/mac/allocator/LteAllocationModule.h"
#include "lte/stack/mac/buffer/LteMacBuffer.h"

using namespace omnetpp;

bool
LteSchedulerEnbDl::checkEligibility(MacNodeId id, Codeword& cw)
{
    // check if harq buffer have already been created for this node
    if (mac_->getHarqTxBuffers()->find(id) != mac_->getHarqTxBuffers()->end())
    {
        LteHarqBufferTx* dlHarq = mac_->getHarqTxBuffers()->at(id);
        UnitList freeUnits = dlHarq->firstAvailable();

        if (freeUnits.first != HARQ_NONE)
        {
            if (freeUnits.second.empty())
                // there is a process currently selected for user <id> , but all of its cws have been already used.
                return false;
            // retrieving the cw index
            cw = freeUnits.second.front();
            // DEBUG check
            if (cw > MAX_CODEWORDS)
                throw cRuntimeError("LteSchedulerEnbDl::checkEligibility(): abnormal codeword id %d", (int) cw);
            return true;
        }
    }
    return true;
}

unsigned int
LteSchedulerEnbDl::schedulePerAcidRtx(MacNodeId nodeId, Codeword cw, unsigned char acid,
    std::vector<BandLimit>* bandLim, Remote antenna, bool limitBl)
{
    // Get user transmission parameters
    const UserTxParams& txParams = mac_->getAmc()->computeTxParams(nodeId, direction_);    // get the user info
    // TODO SK Get the number of codewords - FIX with correct mapping
    unsigned int codewords = txParams.getLayers().size();                // get the number of available codewords

    std::string bands_msg = "BAND_LIMIT_SPECIFIED";

    std::vector<BandLimit> tempBandLim;

    Codeword remappedCw = (codewords == 1) ? 0 : cw;

    if (bandLim == nullptr)
    {
        bands_msg = "NO_BAND_SPECIFIED";
        // Create a vector of band limit using all bands
        bandLim = &tempBandLim;

        unsigned int numBands = mac_->getCellInfo()->getNumBands();
        // for each band of the band vector provided
        for (unsigned int i = 0; i < numBands; i++)
        {
            BandLimit elem;
            // copy the band
            elem.band_ = Band(i);
            EV << "Putting band " << i << endl;
            // mark as unlimited
            for (Codeword i = 0; i < MAX_CODEWORDS; ++i)
            {
                elem.limit_.push_back(-1);
            }
            bandLim->push_back(elem);
        }
    }

    EV << NOW << "LteSchedulerEnbDl::rtxAcid - Node [" << mac_->getMacNodeId() << "], User[" << nodeId << "],  Codeword [" << cw << "]  of [" << codewords << "] , ACID [" << (int)acid << "] " << endl;
    //! \test REALISTIC!!!  Multi User MIMO support
    if (mac_->muMimo() && (txParams.readTxMode() == MULTI_USER))
    {
        // request amc for MU_MIMO pairing
        MacNodeId peer = mac_->getAmc()->computeMuMimoPairing(nodeId);
        if (peer != nodeId)
        {
            // this user has a valid pairing
            //1) register pairing  - if pairing is already registered false is returned
            if (allocator_->configureMuMimoPeering(nodeId, peer))
            {
                EV << "LteSchedulerEnb::grant MU-MIMO pairing established: main user [" << nodeId << "], paired user [" << peer << "]" << endl;
            }
            else
            {
                EV << "LteSchedulerEnb::grant MU-MIMO pairing already exists between users [" << nodeId << "] and [" << peer << "]" << endl;
            }
        }
        else
        {
            EV << "LteSchedulerEnb::grant no MU-MIMO pairing available for user [" << nodeId << "]" << endl;
        }
    }
                //!\test experimental DAS support
                // registering DAS spaces to the allocator
    Plane plane = allocator_->getOFDMPlane(nodeId);
    allocator_->setRemoteAntenna(plane, antenna);

    // blocks to allocate for each band
    std::vector<unsigned int> assignedBlocks;
    // bytes which blocks from the preceding vector are supposed to satisfy
    std::vector<unsigned int> assignedBytes;
    LteHarqBufferTx* currHarq = mac_->getHarqTxBuffers()->at(nodeId);

    // bytes to serve
    unsigned int bytes = currHarq->pduLength(acid, cw);

    // check selected process status.
    std::vector<UnitStatus> pStatus = currHarq->getProcess(acid)->getProcessStatus();

    Codeword allocatedCw = 0;
    // search for already allocated codeword
    // std::vector<UnitStatus>::iterator vit = pStatus.begin(), vet = pStatus.end();
    // for (;vit!=vet;++vit)
    // {
    //     // skip current codeword
    //     if (vit->first==cw) continue;
    //
    //     if (vit->second == TXHARQ_PDU_SELECTED)
    //     {
    //         allocatedCw=vit->first;
    //         break;
    //     }
    // }
    if (allocatedCws_.find(nodeId) != allocatedCws_.end())
    {
        allocatedCw = allocatedCws_.at(nodeId);
    }
    // for each band
    unsigned int size = bandLim->size();

    for (unsigned int i = 0; i < size; ++i)
    {
        // save the band and the relative limit
        Band b = bandLim->at(i).band_;
        int limit = bandLim->at(i).limit_.at(remappedCw);

        EV << "LteSchedulerEnbDl::schedulePerAcidRtx --- BAND " << b << " LIMIT " << limit << "---" << endl;
        // if the limit flag is set to skip, jump off
        if (limit == -2)
        {
            EV << "LteSchedulerEnbDl::schedulePerAcidRtx - skipping logical band according to limit value" << endl;
            continue;
        }

        unsigned int available = 0;
        // if a codeword has been already scheduled for retransmission, limit available blocks to what's been  allocated on that codeword
        if ((allocatedCw != 0))
        {
            // get band allocated blocks
            int b1 = allocator_->getBlocks(antenna, b, nodeId);

            // limit eventually allocated blocks on other codeword to limit for current cw
            //b1 = (limitBl ? (b1>limit?limit:b1) : b1);
            available = mac_->getAmc()->computeBytesOnNRbs(nodeId, b, remappedCw, b1, direction_);
        }
        else
            available = availableBytes(nodeId, antenna, b, remappedCw, direction_, (limitBl) ? limit : -1);    // available space

        // use the provided limit as cap for available bytes, if it is not set to unlimited
        if (limit >= 0 && !limitBl)
            available = limit < (int) available ? limit : available;

        EV << NOW << "LteSchedulerEnbDl::rtxAcid ----- BAND " << b << "-----" << endl;
        EV << NOW << "LteSchedulerEnbDl::rtxAcid To serve: " << bytes << " bytes" << endl;
        EV << NOW << "LteSchedulerEnbDl::rtxAcid Available: " << available << " bytes" << endl;

        unsigned int allocation = 0;
        if (available < bytes)
        {
            allocation = available;
            bytes -= available;
        }
        else
        {
            allocation = bytes;
            bytes = 0;
        }

        if (allocatedCw == 0)
        {
            unsigned int blocks = mac_->getAmc()->computeReqRbs(nodeId, b, remappedCw, allocation, direction_);

            EV << NOW << "LteSchedulerEnbDl::rtxAcid Assigned blocks: " << blocks << "  blocks" << endl;

            // assign only on the first codeword
            assignedBlocks.push_back(blocks);
            assignedBytes.push_back(allocation);
        }

        if (bytes == 0)
            break;
    }

    if (bytes > 0)
    {
        // process couldn't be served
        EV << NOW << "LteSchedulerEnbDl::rtxAcid Cannot serve HARQ Process" << acid << endl;
        return 0;
    }

        // record the allocation if performed
    size = assignedBlocks.size();
    // For each LB with assigned blocks
    for (unsigned int i = 0; i < size; ++i)
    {
        if (allocatedCw == 0)
        {
            // allocate the blocks
            allocator_->addBlocks(antenna, bandLim->at(i).band_, nodeId, assignedBlocks.at(i), assignedBytes.at(i));
        }
        // store the amount
        bandLim->at(i).limit_.at(remappedCw) = assignedBytes.at(i);
    }

    UnitList signal;
    signal.first = acid;
    signal.second.push_back(cw);

    EV << NOW << " LteSchedulerEnbDl::rtxAcid HARQ Process " << (int)acid << "  codeword  " << cw << " marking for retransmission " << endl;

    // if allocated codewords is not MAX_CODEWORDS, then there's another allocated codeword , update the codewords variable :

    if (allocatedCw != 0)
    {
        // TODO fixme this only works if MAX_CODEWORDS ==2
        --codewords;
        if (codewords <= 0)
            throw cRuntimeError("LteSchedulerEnbDl::rtxAcid(): erroneus codeword count %d", codewords);
    }

    // signal a retransmission
    currHarq->markSelected(signal, codewords);

    // mark codeword as used
    if (allocatedCws_.find(nodeId) != allocatedCws_.end())
    {
        allocatedCws_.at(nodeId)++;
        }
    else
    {
        allocatedCws_[nodeId] = 1;
    }

    bytes = currHarq->pduLength(acid, cw);

    EV << NOW << " LteSchedulerEnbDl::rtxAcid HARQ Process " << (int)acid << "  codeword  " << cw << ", " << bytes << " bytes served!" << endl;

    return bytes;
}

bool
LteSchedulerEnbDl::rtxschedule()
{
    EV << NOW << " LteSchedulerEnbDl::rtxschedule --------------------::[ START RTX-SCHEDULE ]::--------------------" << endl;
    EV << NOW << " LteSchedulerEnbDl::rtxschedule Cell:  " << mac_->getMacCellId() << endl;
    EV << NOW << " LteSchedulerEnbDl::rtxschedule Direction: " << (direction_ == DL ? "DL" : "UL") << endl;

    // retrieving reference to HARQ entities
    HarqTxBuffers* harqQueues = mac_->getHarqTxBuffers();

    HarqTxBuffers::iterator it = harqQueues->begin();
    HarqTxBuffers::iterator et = harqQueues->end();

    std::vector<BandLimit> usableBands;

    // examination of HARQ process in rtx status, adding them to scheduling list
    for(; it != et; ++it)
    {
        // For each UE
        MacNodeId nodeId = it->first;

        OmnetId id = binder_->getOmnetId(nodeId);
        if(id == 0){
            // UE has left the simulation, erase HARQ-queue
            it = harqQueues->erase(it);
            if(it == et)
                break;
            else
                continue;
        }
        LteHarqBufferTx* currHarq = it->second;
        std::vector<LteHarqProcessTx *> * processes = currHarq->getHarqProcesses();

        // Get user transmission parameters
        const UserTxParams& txParams = mac_->getAmc()->computeTxParams(nodeId, direction_);// get the user info
        // TODO SK Get the number of codewords - FIX with correct mapping
        unsigned int codewords = txParams.getLayers().size();// get the number of available codewords

        EV << NOW << " LteSchedulerEnbDl::rtxschedule  UE: " << nodeId << endl;
        EV << NOW << " LteSchedulerEnbDl::rtxschedule Number of codewords: " << codewords << endl;


        // get the number of HARQ processes
        unsigned int process=0;
        unsigned int maxProcesses = currHarq->getNumProcesses();
        for(process = 0; process < maxProcesses; ++process )
        {
            // for each HARQ process
            LteHarqProcessTx * currProc = (*processes)[process];

            if (allocatedCws_[nodeId] == codewords)
                break;
            for (Codeword cw = 0; cw < codewords; ++cw)
            {

                if (allocatedCws_[nodeId]==codewords)
                    break;
                EV << NOW << " LteSchedulerEnbDl::rtxschedule process " << process << endl;
                EV << NOW << " LteSchedulerEnbDl::rtxschedule ------- CODEWORD " << cw << endl;

                // skip processes which are not in rtx status
                if (currProc->getUnitStatus(cw) != TXHARQ_PDU_BUFFERED)
                {
                    EV << NOW << " LteSchedulerEnbDl::rtxschedule detected Acid: " << process << " in status " << currProc->getUnitStatus(cw) << endl;
                    continue;
                }

                EV << NOW << " LteSchedulerEnbDl::rtxschedule " << endl;
                EV << NOW << " LteSchedulerEnbDl::rtxschedule detected RTX Acid: " << process << endl;

                // Get the bandLimit for the current user
                std::vector<BandLimit>* bandLim;
                bool ret = getBandLimit(&usableBands, nodeId);
                if (!ret)
                    bandLim = nullptr;
                else
                    bandLim = &usableBands;

                // perform the retransmission
                unsigned int bytes = schedulePerAcidRtx(nodeId,cw,process,bandLim);

                // if a value different from zero is returned, there was a service
                if(bytes > 0)
                {
                    EV << NOW << " LteSchedulerEnbDl::rtxschedule CODEWORD IS NOW BUSY!!!" << endl;
                    // do not process this HARQ process anymore
                    // go to next codeword
                    break;
                }
            }
        }
    }

    unsigned int availableBlocks = allocator_->computeTotalRbs();
    EV << " LteSchedulerEnbDl::rtxschedule OFDM Space: " << availableBlocks << endl;
    EV << "    LteSchedulerEnbDl::rtxschedule --------------------::[  END RTX-SCHEDULE  ]::-------------------- " << endl;

    return (availableBlocks == 0);
}

bool LteSchedulerEnbDl::getBandLimit(std::vector<BandLimit>* bandLimit, MacNodeId ueId)
{
    bandLimit->clear();

    // get usable bands for this user
    UsableBands* usableBands = nullptr;
    bool ret = mac_->getAmc()->getPilotUsableBands(ueId, usableBands);
    if (!ret)
    {
        // leave the bandLimit empty
        return false;
    }

    // check the number of codewords
    unsigned int numCodewords = 1;
    unsigned int numBands = mac_->getCellInfo()->getNumBands();
    // for each band of the band vector provided
    for (unsigned int i = 0; i < numBands; i++)
    {
        BandLimit elem;
        elem.band_ = Band(i);

        int limit = -2;

        // check whether band i is in the set of usable bands
        UsableBands::iterator it = usableBands->begin();
        for (; it != usableBands->end(); ++it)
        {
            if (*it == i)
            {
                // band i must be marked as unlimited
                limit = -1;
                break;
            }
        }

        elem.limit_.clear();
        for (unsigned int j = 0; j < numCodewords; j++)
            elem.limit_.push_back(limit);

        bandLimit->push_back(elem);
    }

    return true;
}
