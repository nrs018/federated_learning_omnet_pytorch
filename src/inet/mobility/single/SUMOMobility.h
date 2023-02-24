//
// Copyright (C) 2005 Andras Varga
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#ifndef __INET_SUMOMOBILITY_H
#define __INET_SUMOMOBILITY_H

#include "inet/common/INETDefs.h"
#include "inet/mobility/base/MovingMobilityBase.h"

namespace inet {

/**
 * @brief SUMO movement model. See NED file for more info.
 *
 * @ingroup mobility
 * @author Andras Varga
 */
class INET_API SUMOMobility : public MovingMobilityBase
{
  protected:
    double x;
    double y;
    double z;
    double speed;


  protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }

    /** @brief Initializes mobility model parameters.*/
    virtual void initialize(int stage) override;

    /** @brief Initializes the position according to the mobility model. */
    virtual void setInitialPosition() override;

    /** @brief Move the host according to the current simulation time. */
    virtual void move() override;

  public:
    virtual double getMaxSpeed() const override { return speed; }
    SUMOMobility();

};

} // namespace inet

#endif // ifndef __INET_SUMOMOBILITY_H

