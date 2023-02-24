
#pragma once

#include <map>
#include <memory>
#include <list>
#include <queue>

#include "inet/common/INETDefs.h"

#ifndef __INET_SUMOMOBILITY_H
#define __INET_SUMOMOBILITY_H
namespace inet {

class INET_API SUMOMap : public cSimpleModule {
public:
    SUMOMap();
    ~SUMOMap();

    bool isloadMap = false;

    int numVehicle ; // the number of vehicle
    int numTaxi ;  //the number of taxi
    int numTruck; // the number of truck
    int numBus ; // the number of bus
    int numCoach; //the number of coach
    int numPassenger ; // the number of passenger
    int numDelivery ; // the number of delivery
    int numTrailer ; // the number of trailer

    int randomSeed;
    std::vector<std::vector<std::string>> routeVector;

    cMessage *updateInterval ;


    virtual void generateVehicle(std::vector<std::string > allowedVehicle, std::string vehicleName, std::string vehBase, int num);
//    virtual void generateBus();
//    virtual void generateCoach();
//    virtual void generateTaxi();
//    virtual void generateTruck();
//    virtual void generatePassenger();
//    virtual void generateDelivery();
//    virtual void generateTrailer();

    virtual void initialize(int stage) override;
    virtual void finish() override;
    virtual void handleMessage(cMessage* msg) override;
};

}
#endif // ifndef __INET_SUMOMOBILITY_H
