//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#include "lte/corenetwork/nodes/ExtCell.h"

Define_Module(ExtCell);
using namespace omnetpp;

void ExtCell::initialize()
{
    // get coord
    position_.x = par("position_x");
    position_.y = par("position_y");
    if (getEnvir()->isGUI())
    {
        getDisplayString().setTagArg("p", 0, (long)position_.x);
        getDisplayString().setTagArg("p", 1, (long)position_.y);
    }

    txPower_ = par("txPower");

    // set TX direction
    std::string txDir = par("txDirection");
    if (txDir.compare(txDirections[OMNI].txDirectionName)==0)
    {
        txDirection_ = OMNI;
    }
    else   // ANISOTROPIC
    {
        txDirection_ = ANISOTROPIC;

        // set TX angle
        txAngle_ = par("txAngle");
    }

    binder_ = getBinder();
    numBands_ = binder_->getNumBands();

    // initialize band status structures
    bandStatus_.resize(numBands_, 0);
    prevBandStatus_.resize(numBands_, 0);

    // get allocation type
    std::string allocationType = par("bandAllocationType").stdstringValue();
    if (allocationType.compare("CONTIGUOUS_ALLOC") == 0)
    {
        allocationType_ = CONTIGUOUS_ALLOC;
    }
    else if (allocationType.compare("RANDOM_ALLOC") == 0)
    {
        allocationType_ = RANDOM_ALLOC;
    }
    else
    {
        allocationType_ = FULL_ALLOC;
    }

    // get the allocation parameters
    if (allocationType_ == FULL_ALLOC)
    {
        bandStatus_.clear();
        prevBandStatus_.clear();

        // mark all RBs as occupied
        bandStatus_.resize(numBands_, 1);
        prevBandStatus_.resize(numBands_, 1);
    }
    else
    {
        // get the band utilization
        double bandUtilization = par("bandUtilization");
        setBandUtilization(bandUtilization);

        if (allocationType_ == CONTIGUOUS_ALLOC)
        {
            // get the starting offset
            startingOffset_ = par("startingOffset");
        }

        // TODO: if extCell-interference is disabled, do not send selfMessages
        /* Start TTI tick */
        ttiTick_ = new cMessage("ttiTick_");
        ttiTick_->setSchedulingPriority(1);        // TTI TICK after other messages
        scheduleAt(NOW + TTI, ttiTick_);
    }

    // add this cell to the binder
    id_ = binder_->addExtCell(this);
}

void ExtCell::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        updateBandStatus();

        scheduleAt(NOW + TTI, msg);
        return;
    }
}

void ExtCell::updateBandStatus()
{
    EV << "----- EXT CELL ALLOCATION UPDATE -----" << endl;

    resetBandStatus();

    if (allocationType_ == RANDOM_ALLOC)
    {
        EV << " ExtCell::updateBandStatus() - generating new random allocation for extCell " << id_ << endl;

        // allocates each band with probability equal to bandUtilization_
        for (int band = 0; band < numBands_; ++band)
        {
            int occ = bernoulli(bandUtilization_);
            bandStatus_[band] = occ;
        }
    }
    else    // CONTIGUOUS ALLOC
    {
        EV << " ExtCell::updateBandStatus() - generating new contiguous allocation for extCell " << id_ << endl;

        // get the number of bands to be allocated
        int toAlloc = ceil( (double)numBands_ * bandUtilization_);
        int band = startingOffset_;
        int prev = band;
        for (; (band != startingOffset_ || band == prev) && toAlloc > 0; prev = band, band = (band+1)%numBands_)
        {
            bandStatus_[band] = 1;
            toAlloc--;
        }
    }

    EV << "----- END EXT CELL ALLOCATION UPDATE -----" << endl;
}

void ExtCell::resetBandStatus()
{
    prevBandStatus_.clear();
    prevBandStatus_ = bandStatus_;

    bandStatus_.clear();
    bandStatus_.resize(numBands_, 0);
}

void ExtCell::setBandUtilization(double bandUtilization)
{
    if (bandUtilization < 0)
        bandUtilization = 0;
    else if (bandUtilization > 1)
        bandUtilization = 1;

    bandUtilization_ = bandUtilization;
}
