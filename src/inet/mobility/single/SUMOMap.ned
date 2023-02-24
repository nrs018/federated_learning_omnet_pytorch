
package inet.mobility.single;

simple SUMOMap
{
    parameters:
        @display("i=block/network2");
        string map;
        int randomSeed = default(0);

        int numVehicle = default(100);
        int numBus = default(0);
        int numCoach = default(0);
        int numTruck = default(0);
        int numTaxi = default(0);
        int numTrailer = default(0);
        int numPassenger = default(0);
        int numDelivery = default(0);
        
        
}

