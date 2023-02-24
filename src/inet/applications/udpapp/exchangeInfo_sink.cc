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

#include "inet/applications/udpapp/exchangeInfo_sink.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/packet/Packet.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include "inet/applications/base/ApplicationPacket_m.h"
#include "inet/applications/udpapp/InfoFL_m.h"

#include "inet/applications/udpapp/exchangeInfo_broadcast.h"

namespace inet {

Define_Module(exchangeInfo_sink);

exchangeInfo_sink::~exchangeInfo_sink()
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    cancelAndDelete(selfMsg);
}

void exchangeInfo_sink::initialize(int stage)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        numReceived = 0;
        WATCH(numReceived);

        localPort = par("localPort");
        startTime = par("startTime");
        stopTime = par("stopTime");
        if (stopTime >= SIMTIME_ZERO && stopTime < startTime)
            throw cRuntimeError("Invalid startTime/stopTime parameters");
        selfMsg = new cMessage("UDPSinkTimer");

        for(int i=0;i<NUMCLIENT;i++)
        {
            globalINFO[i] = -3333;
            globalINFO_x[i] = -2222;
            globalINFO_y[i] = -2222;
        }


    }
}

void exchangeInfo_sink::handleMessageWhenUp(cMessage *msg)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    if (msg->isSelfMessage()) {
        ASSERT(msg == selfMsg);
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
    else if (msg->arrivedOn("socketIn"))
        socket.processMessage(msg);
    else
        throw cRuntimeError("Unknown incoming gate: '%s'", msg->getArrivalGate()->getFullName());
}

void exchangeInfo_sink::socketDataArrived(UdpSocket *socket, Packet *packet)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    // process incoming packet
    processPacket(packet);
}

void exchangeInfo_sink::socketErrorArrived(UdpSocket *socket, Indication *indication)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void exchangeInfo_sink::socketClosed(UdpSocket *socket)
{
    std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    if (operationalState == State::STOPPING_OPERATION)
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void exchangeInfo_sink::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

    char buf[50];
    sprintf(buf, "rcvd: %d pks", numReceived);
    getDisplayString().setTagArg("t", 0, buf);
}

void exchangeInfo_sink::finish()
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    ApplicationBase::finish();
    EV_INFO << getFullPath() << ": received " << numReceived << " packets\n";
}

void exchangeInfo_sink::setSocketOptions()
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
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

void exchangeInfo_sink::processStart()
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    socket.setOutputGate(gate("socketOut"));
    socket.bind(localPort);
    setSocketOptions();

    if (stopTime >= SIMTIME_ZERO) {
        selfMsg->setKind(STOP);
        scheduleAt(stopTime, selfMsg);
    }
}

void exchangeInfo_sink::processStop()
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    if (!multicastGroup.isUnspecified())
        socket.leaveMulticastGroup(multicastGroup); // FIXME should be done by socket.close()
    socket.close();
}

void exchangeInfo_sink::processPacket(Packet *pk)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;

    EV_INFO << "Received packet: " << UdpSocket::getReceivedPacketInfo(pk) << endl;
    //auto data = pk->peekData<ApplicationPacket>();

    auto data = pk->peekData<InfoFL>();
    globalINFO[data->getSrcId()] = data->getGlobalInfo();
    globalINFO_x[data->getSrcId()] = data->getX_pos();
    globalINFO_y[data->getSrcId()] = data->getY_pos();
    if(getParentModule()->getIndex() == 8)
    {
        //std::cout << " ===============================" << getParentModule()->getIndex() << endl;

        for(int i=0;i<NUMCLIENT;i++)
        {
            //std::cout << i << " : " << globalINFO[i] << endl;
        }
    }
    //std::cout << getFullPath() << " globalInfo arrived, time " << simTime() << " " << data->getSrcId() << " " << data->getGlobalInfo() << endl;
    emit(packetReceivedSignal, pk);
    delete pk;

    numReceived++;
}

void exchangeInfo_sink::handleStartOperation(LifecycleOperation *operation)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    simtime_t start = std::max(startTime, simTime());
    if ((stopTime < SIMTIME_ZERO) || (start < stopTime) || (start == stopTime && startTime == stopTime)) {
        selfMsg->setKind(START);
        scheduleAt(start, selfMsg);
    }
}

void exchangeInfo_sink::handleStopOperation(LifecycleOperation *operation)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    cancelEvent(selfMsg);
    if (!multicastGroup.isUnspecified())
        socket.leaveMulticastGroup(multicastGroup); // FIXME should be done by socket.close()
    socket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void exchangeInfo_sink::handleCrashOperation(LifecycleOperation *operation)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    cancelEvent(selfMsg);
    if (operation->getRootModule() != getContainingNode(this)) {     // closes socket when the application crashed only
        if (!multicastGroup.isUnspecified())
            socket.leaveMulticastGroup(multicastGroup); // FIXME should be done by socket.close()
        socket.destroy();    //TODO  in real operating systems, program crash detected by OS and OS closes sockets of crashed programs.
    }
}

} // namespace inet

