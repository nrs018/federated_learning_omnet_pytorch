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

#include "inet/common/INETMath.h"
#include "inet/mobility/single/SUMOMobility.h"
#include "libsumo/libsumo.h"

namespace inet {

Define_Module(SUMOMobility);

SUMOMobility::SUMOMobility()
{
    x = 0;
    y = 0;
    z = 0;
    speed = 0;
}

void SUMOMobility::initialize(int stage)
{
    MovingMobilityBase::initialize(stage);

    EV_TRACE << "initializing SUMOMobility stage " << stage << endl;
    if (stage == INITSTAGE_LOCAL) {
        x = par("x");
        y = par("y");
        z = par("z");
        speed = par("speed");
    }
}

void SUMOMobility::setInitialPosition()
{
    move();
}

void SUMOMobility::move()
{

    std::string vehID = this->getParentModule()->getName() + std::to_string(this->getParentModule()->getIndex());
    try{
        libsumo::TraCIPosition pos = libsumo::Vehicle::getPosition3D(vehID);

        if(std::abs(pos.x) > 10000){
            lastPosition.x = rand() % 1000;
            lastPosition.y = rand() % 1000;
            lastPosition.z = 0;
            lastVelocity.x = speed;
            lastVelocity.y = speed;
            lastVelocity.z = 0;
        }
        lastPosition.x = pos.x;
        lastPosition.y = pos.y;
        lastPosition.z = 0;
        lastVelocity.x = speed;
        lastVelocity.y = speed;
        lastVelocity.z = 0;
//        std::cout << vehID << " " << pos.x << " " << pos.y << " " << pos.z << endl;
    }

    catch(libsumo::TraCIException & e){
//        std::cout << e.what() << ",xx " << this->getFullName() << endl;
    }
}

} // namespace inet

