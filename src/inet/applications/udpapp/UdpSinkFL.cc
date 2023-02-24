//
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
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

#include "inet/applications/udpapp/UdpSinkFL.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/Packet.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include "inet/networklayer/common/HopLimitTag_m.h"
#include "inet/applications/base/ApplicationPacket_m.h"
#include "inet/applications/udpapp/InfoFL_m.h"
#include <fstream>
#include <iostream>
namespace inet {

Define_Module(UdpSinkFL);

UdpSinkFL::~UdpSinkFL()
{
    cancelAndDelete(selfMsg);
}

void UdpSinkFL::initialize(int stage)
{
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        numReceived = 0;
        WATCH(numReceived);

        localPort = par("localPort");
        startTime = par("startTime");
        stopTime = par("stopTime");
        checkTime = startTime.dbl() + 5;
        //std::cout << checkInterval << endl;
        if (stopTime >= SIMTIME_ZERO && stopTime < startTime)
            throw cRuntimeError("Invalid startTime/stopTime parameters");
        selfMsg = new cMessage("UDPSinkTimer");
        checkTimeMsg = new cMessage("checkTimeMsg");

    }
    globalInfo = par("globalInfo");

    for(int i=0;i<NUM_UEs;i++){
        //clientIDArray[i] = -1;
        globalInfoArray[i] = -200;
    }

}

void UdpSinkFL::checkGlobalInfo(){

}

void UdpSinkFL::handleMessageWhenUp(cMessage *msg)
{
    std::ofstream outfile;
    //std::cout << getFullPath() << simTime() << endl;
    if (msg->isSelfMessage()) {
        //ASSERT(msg == selfMsg);
        if(msg == selfMsg){
            switch (selfMsg->getKind()) {
                case START:
                    processStart();
                    break;

                case STOP:
                    processStop();
                    break;

                default:
                    throw cRuntimeError("Invalid kind %d in self message", (int)selfMsg->getKind());
            }
        }
        if(msg == checkTimeMsg)
        {
            //std::cout << getParentModule()->getIndex() << "  " << maxArray(globalInfoArray) << " " << (getParentModule()->getIndex() == maxArray(globalInfoArray)) << " " ;
            //std::cout << globalInfoArray[maxArray(globalInfoArray)] << endl;
            //if(getParentModule()->getIndex() == maxArray(globalInfoArray) && flag == false)
            std::ofstream outfile;
            const char * fname = NULL;
            std::string a = "/home/narisu/src/omnet/omnetpp-5.5.1/samples/new_toyota_FL/examples/federatedlearning/exchangeInfo/exchangeInfo.txt";
            std::string d = a;
            fname = d.c_str();

            if(getParentModule()->getIndex() == maxArray(globalInfoArray) && flag == false )
            {

                flag = true;
                std::cout << simTime() << getFullPath() << " tcp close " << endl;
                outfile.open(fname, std::ios::app);
                outfile << " start uploading model at time " << simTime() << " " << getFullPath() << endl;
                outfile.close();
            }

            std::cout << " start uploading model at time " << simTime() << " " << getFullPath() << endl;
            std::cout << "=======================  " << getFullPath() << " time " << simTime() << " ========================" << endl;
            for(int i=0;i<NUM_UEs;i++){
                if(globalInfoArray[i] > -200){
                    std::cout << "src:" << i << " , globalInfo:" << globalInfoArray[i] << endl;
                }
            }
            std::cout << endl;
            //}
            std::cout << par("checkInterval").doubleValue() << endl;
            scheduleAt(simTime() + par("checkInterval").doubleValue(), checkTimeMsg);

        }
    }
    else if (msg->arrivedOn("socketIn"))
        socket.processMessage(msg);
    else
        throw cRuntimeError("Unknown incoming gate: '%s'", msg->getArrivalGate()->getFullName());
}

void UdpSinkFL::socketDataArrived(UdpSocket *socket, Packet *packet)
{
    // process incoming packet
    processPacket(packet);
}

void UdpSinkFL::socketErrorArrived(UdpSocket *socket, Indication *indication)
{
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void UdpSinkFL::socketClosed(UdpSocket *socket)
{
    if (operationalState == State::STOPPING_OPERATION)
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void UdpSinkFL::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

    char buf[50];
    sprintf(buf, "rcvd: %d pks", numReceived);
    getDisplayString().setTagArg("t", 0, buf);
}

void UdpSinkFL::finish()
{
    ApplicationBase::finish();
    EV_INFO << getFullPath() << ": received " << numReceived << " packets\n";
}

void UdpSinkFL::setSocketOptions()
{
    bool receiveBroadcast = par("receiveBroadcast");
    if (receiveBroadcast)
        socket.setBroadcast(true);

    MulticastGroupList mgl = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this)->collectMulticastGroups();
    socket.joinLocalMulticastGroups(mgl);

    // join multicastGroup
    const char *groupAddr = par("multicastGroup");
    multicastGroup = L3AddressResolver().resolve(groupAddr);
    if (!multicastGroup.isUnspecified()) {
        if (!multicastGroup.isMulticast())
            throw cRuntimeError("Wrong multicastGroup setting: not a multicast address: %s", groupAddr);
        socket.joinMulticastGroup(multicastGroup);
    }
    socket.setCallback(this);
}

void UdpSinkFL::processStart()
{
    socket.setOutputGate(gate("socketOut"));
    socket.bind(localPort);
    setSocketOptions();
    globalInfoArray[getParentModule()->getIndex()] = globalInfo;
    if (stopTime >= SIMTIME_ZERO) {
        selfMsg->setKind(STOP);
        scheduleAt(stopTime, selfMsg);
    }
}

void UdpSinkFL::processStop()
{
    if (!multicastGroup.isUnspecified())
        socket.leaveMulticastGroup(multicastGroup); // FIXME should be done by socket.close()
    socket.close();
}


int UdpSinkFL::maxArray(double a[]){
    double m = -1000;
    int pos = -1;
    for(int i=0;i<NUM_UEs;i++)
    {
        if(a[i] >= m)
        {
            m = a[i];
            pos = i;
        }
    }
    return pos;
}


void UdpSinkFL::processPacket(Packet *pk)
{
    EV_INFO << "Received packet: " << UdpSocket::getReceivedPacketInfo(pk) << endl;
    packetCount = packetCount + 1;
    //int ttl = pk->getTag<HopLimitInd>()->getHopLimit();


    ///////////////////  distributed federated learning  ////////////////

    auto ap = pk->popAtFront<InfoFL>();
    //std::cout << "---------  " << ap->getClientID() << " == " << ap->getGlobalInfo() << " time " << simTime() << endl;
    //std::cout << "\n ==============  " << getParentModule()->getIndex() << " time :" << simTime() << " ===========" << endl;
    //globalInfoArray[ap->getClientID()] = ap->getGlobalInfo();


    //emit(packetReceivedSignal, pk);

    delete pk;

    numReceived++;
}

void UdpSinkFL::handleStartOperation(LifecycleOperation *operation)
{
    simtime_t start = std::max(startTime, simTime());
    if ((stopTime < SIMTIME_ZERO) || (start < stopTime) || (start == stopTime && startTime == stopTime)) {
        selfMsg->setKind(START);
        scheduleAt(start, checkTimeMsg);
        scheduleAt(start, selfMsg);
    }
}

void UdpSinkFL::handleStopOperation(LifecycleOperation *operation)
{
    cancelEvent(selfMsg);
    if (!multicastGroup.isUnspecified())
        socket.leaveMulticastGroup(multicastGroup); // FIXME should be done by socket.close()
    socket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void UdpSinkFL::handleCrashOperation(LifecycleOperation *operation)
{
    cancelEvent(selfMsg);
    if (operation->getRootModule() != getContainingNode(this)) {     // closes socket when the application crashed only
        if (!multicastGroup.isUnspecified())
            socket.leaveMulticastGroup(multicastGroup); // FIXME should be done by socket.close()
        socket.destroy();    //TODO  in real operating systems, program crash detected by OS and OS closes sockets of crashed programs.
    }
}

} // namespace inet

