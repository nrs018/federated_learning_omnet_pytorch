//
// Copyright (C) 2006-2017 Christoph Sommer <sommer@ccs-labs.org>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include <fstream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <cstdlib>

#include "inet/mobility/single/SUMOMap.h"
#define HAVE_LIBSUMOGUI
#include "libsumo/libsumo.h"
#include "microsim/MSEdge.h"
#include "microsim/MSLane.h"

namespace inet{

Define_Module(SUMOMap);
SUMOMap::SUMOMap(){}
SUMOMap::~SUMOMap(){}


void SUMOMap::generateVehicle(std::vector<std::string > allowedVehicle, std::string vehicleName, std::string vehBase, int num){

    std::vector<std::string > allLane = libsumo::Lane::getIDList();
    std::vector<std::string > allowedVehicleLane;
    for(unsigned int i=0;i<allLane.size();i++){
        std::vector<std::string> v = libsumo::Lane::getAllowed(allLane[i]);
        bool ALLOWED = false;
        for(unsigned int k=0;k<v.size();k++){
            for(unsigned int j=0;j<allowedVehicle.size();j++){
                if(std::strcmp(v[k].c_str(), allowedVehicle[j].c_str()) == 0) {
                    allowedVehicleLane.push_back(allLane[i]);
                    ALLOWED = true;
                    break;
                }
            }
            if(ALLOWED == true)
                break;
        }
    }

//    std::string vehBase = "V";
    std::string vehID;
    std::string routeBase = "R";
    std::string routeID;
    int i=0;
    while(i<num){
        std::string src = libsumo::Lane::getEdgeID(allowedVehicleLane[rand() % allowedVehicleLane.size()]);
        std::string dest = libsumo::Lane::getEdgeID(allowedVehicleLane[rand() % allowedVehicleLane.size()]);

        try{
            libsumo::TraCIStage trace = libsumo::Simulation::findRoute(src, dest);
            vehID = vehBase + std::to_string(i);
            routeID = routeBase + std::to_string(i);
            libsumo::Route::add(routeID, trace.edges);
            libsumo::Vehicle::add(vehID, routeID);

            i++;
            std::cout << "Add " << vehicleName << " " << vehID << endl;
        }
        catch(libsumo::TraCIException & e){
            //std::cout << e.what() << " " << this->getFullName() << endl;
        }
    }
}

void SUMOMap::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if(!isloadMap){
        updateInterval = new cMessage("updateInterval");
        scheduleAt(simTime(), updateInterval);

        numVehicle = par("numVehicle").intValue(); // the number of vehicle
        numTaxi = par("numTaxi").intValue();  //the number of taxi
        numTruck = par("numTruck").intValue(); // the number of truck
        numBus = par("numBus").intValue(); // the number of bus
        numCoach = par("numCoach").intValue(); //the number of coach
        numPassenger = par("numPassenger").intValue(); // the number of passenger
        numDelivery = par("numDelivery").intValue(); // the number of delivery
        numTrailer = par("numTrailer").intValue(); // the number of trailer


        srand(par("randomSeed").intValue()); // initialize the random seed by the number of the round
        srand((unsigned)time(NULL));
        std::pair<int, std::string> a = libsumo::Simulation::start({"sumo", "-c", par("map").stringValue()});
        std::vector<std::string > allowedVehicle;

        if(numVehicle > 0) {
            allowedVehicle = {"taxi", "bus", "coach",  "truck", "trailer", "evehicle"};
            generateVehicle(allowedVehicle, "vehicle", "V", numVehicle);
        }

//        if(numTaxi > 0) {
//            allowedVehicle = {"taxi"};
//            generateVehicle(allowedVehicle, "taxi", "Taxi", numTaxi);
//        }
//        exit(0);
//        if(numTruck > 0) {
//            allowedVehicle = {"truck"};
//            generateVehicle(allowedVehicle, "truck", "T", numTruck);
//        }
//        exit(0);
//        if(numBus > 0) {
//            allowedVehicle = {"bus"};
//            generateVehicle(allowedVehicle, "bus", "B", numBus);
//        }
//        exit(0);
//        if(numCoach > 0) {
//            allowedVehicle = {"coach"};
//            generateVehicle(allowedVehicle, "coach", "C", numCoach);
//        }
//        if(numPassenger > 0) {
//            allowedVehicle = {"passenger", "pedestrian"};
//            generateVehicle(allowedVehicle, "passenger", "P", numPassenger);
//        }
//        if(numDelivery > 0) {
//            allowedVehicle = {"delivery"};
//            generateVehicle(allowedVehicle, "delivery", "D", numDelivery);
//        }
//        if(numTrailer > 0) {
//            allowedVehicle = {"trailer"};
//            generateVehicle(allowedVehicle, "trailer", "Tr", numTrailer);
//        }

        isloadMap = true;
        libsumo::Simulation::step(simTime().dbl());
    }
}

void SUMOMap::finish(){

}

void SUMOMap::handleMessage(cMessage* msg)
{
    if (msg->isSelfMessage()) {
        libsumo::Simulation::step(simTime().dbl());
        scheduleAt(simTime() + 0.1, updateInterval);
    }

}
}//namespace


