//
// Copyright (C) 2000 Institut fuer Telematik, Universitaet Karlsruhe
// Copyright (C) 2004,2011 Andras Varga
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

#include "inet/applications/base/ApplicationPacket_m.h"
#include "inet/applications/udpapp/exchangeInfo_broadcast.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/packet/Packet.h"
#include "inet/networklayer/common/FragmentationTag_m.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/transportlayer/contract/udp/UdpControlInfo_m.h"
#include "inet/applications/udpapp/InfoFL_m.h"

#include "inet/applications/tcpapp/ClientSink.h"
#include "inet/mobility/static/StationaryMobility.h"

#include "veins_inet/VeinsInetMobility.h"
#include "inet/mobility/single/SUMOMobility.h"
#include "inet/applications/udpapp/exchangeInfo_sink.h"

namespace inet {

Define_Module(exchangeInfo_broadcast);

exchangeInfo_broadcast::~exchangeInfo_broadcast()
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    cancelAndDelete(selfMsg);
}

void exchangeInfo_broadcast::initialize(int stage)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    ApplicationBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        numSent = 0;
        numReceived = 0;
        WATCH(numSent);
        WATCH(numReceived);

        localPort = par("localPort");
        destPort = par("destPort");
        startTime = par("startTime");
        stopTime = par("stopTime");
        packetName = par("packetName");
        dontFragment = par("dontFragment");
        if (stopTime >= SIMTIME_ZERO && stopTime < startTime)
            throw cRuntimeError("Invalid startTime/stopTime parameters");
        selfMsg = new cMessage("sendTimer");

        globalInfo = -3333;  //par("globalInfo").doubleValue();
//        sampleQuantity = par("sampleQuantity").intValue();

        if(this->getParentModule()->getIndex() < NUMCLIENT * 0.4){
            sampleQuantity = 4500;
        }
        else{
            sampleQuantity = 45;
        }

        TrainingDeadline = par("TrainingDeadline");

        //deltaLoss = par("deltaLoss").doubleValue();
        //std::cout << "tttttttttttttttt " << getFullPath() << " globalinfo " << globalInfo << endl;
    }
}

void exchangeInfo_broadcast::finish()
{
    std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    recordScalar("packets sent", numSent);
    recordScalar("packets received", numReceived);
    ApplicationBase::finish();
}

void exchangeInfo_broadcast::setSocketOptions()
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    int timeToLive = par("timeToLive");
    if (timeToLive != -1)
        socket.setTimeToLive(timeToLive);

    int dscp = par("dscp");
    if (dscp != -1)
        socket.setDscp(dscp);

    int tos = par("tos");
    if (tos != -1)
        socket.setTos(tos);

    const char *multicastInterface = par("multicastInterface");
    if (multicastInterface[0]) {
        IInterfaceTable *ift = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);
        InterfaceEntry *ie = ift->findInterfaceByName(multicastInterface);
        if (!ie)
            throw cRuntimeError("Wrong multicastInterface setting: no interface named \"%s\"", multicastInterface);
        socket.setMulticastOutputInterface(ie->getInterfaceId());
    }

    bool receiveBroadcast = par("receiveBroadcast");
    if (receiveBroadcast)
        socket.setBroadcast(true);

    bool joinLocalMulticastGroups = par("joinLocalMulticastGroups");
    if (joinLocalMulticastGroups) {
        MulticastGroupList mgl = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this)->collectMulticastGroups();
        socket.joinLocalMulticastGroups(mgl);
    }
    socket.setCallback(this);
}

L3Address exchangeInfo_broadcast::chooseDestAddr()
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    int k = intrand(destAddresses.size());
    if (destAddresses[k].isUnspecified() || destAddresses[k].isLinkLocal()) {
        L3AddressResolver().tryResolve(destAddressStr[k].c_str(), destAddresses[k]);
    }
    return destAddresses[k];
}

void exchangeInfo_broadcast::sendPacket()
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    std::ostringstream str;
    str << packetName << "-" << numSent;
    Packet *packet = new Packet(str.str().c_str());
    if(dontFragment)
        packet->addTag<FragmentationReq>()->setDontFragment(true);
    //const auto& payload = makeShared<ApplicationPacket>();
    const auto& payload = makeShared<InfoFL>();
    payload->setChunkLength(B(par("messageLength")));
    payload->setSequenceNumber(numSent);

    ///  calculate global info /////
//    cModule *m = getParentModule()->getSubmodule("app", 0);
//    ClientSink *cs = check_and_cast<ClientSink * >(m);
    //globalInfo = sampleQuantity / 1000 + (65 - cs->ModelReceivedTime) / 50;
    //globalInfo = -3333;  ///sampleQuantity / 1000 + (65 - cs->ModelReceivedTime) / 50;

    //std::cout << getFullPath() << " " << sampleQuantity << " " << cs->ModelReceivedTime << " " << globalInfo << endl;


    payload->setGlobalInfo(globalInfo);
    payload->setSrcId(getParentModule()->getIndex());
    /////setting position /////
    cModule * m = getParentModule()->getSubmodule("mobility", 0);
//    StationaryMobility *sm = check_and_cast<StationaryMobility *>(m);
//    veins::VeinsInetMobility *sm = check_and_cast<veins::VeinsInetMobility *>(m);
    inet::SUMOMobility *sm = check_and_cast<inet::SUMOMobility *>(m);
    payload->setX_pos(sm->getCurrentPosition().x);
    payload->setY_pos(sm->getCurrentPosition().y);

    payload->addTag<CreationTimeTag>()->setCreationTime(simTime());

    packet->insertAtBack(payload);
    L3Address destAddr = chooseDestAddr();
    emit(packetSentSignal, packet);
    socket.sendTo(packet, destAddr, destPort);
    numSent++;
}

void exchangeInfo_broadcast::processStart()
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    socket.setOutputGate(gate("socketOut"));
    const char *localAddress = par("localAddress");
    socket.bind(*localAddress ? L3AddressResolver().resolve(localAddress) : L3Address(), localPort);
    setSocketOptions();

    const char *destAddrs = par("destAddresses");
    cStringTokenizer tokenizer(destAddrs);
    const char *token;

    while ((token = tokenizer.nextToken()) != nullptr) {
        destAddressStr.push_back(token);
        L3Address result;
        L3AddressResolver().tryResolve(token, result);
        if (result.isUnspecified())
            EV_ERROR << "cannot resolve destination address: " << token << endl;
        destAddresses.push_back(result);
    }

    if (!destAddresses.empty()) {
        selfMsg->setKind(SEND);
        processSend();
    }
    else {
        if (stopTime >= SIMTIME_ZERO) {
            selfMsg->setKind(STOP);
            scheduleAt(stopTime, selfMsg);
        }
    }
}

void exchangeInfo_broadcast::processSend()
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    sendPacket();
    simtime_t d = simTime() + par("sendInterval");
    if (stopTime < SIMTIME_ZERO || d < stopTime) {
        selfMsg->setKind(SEND);
        scheduleAt(d, selfMsg);
    }
    else {
        selfMsg->setKind(STOP);
        scheduleAt(stopTime, selfMsg);
    }
}

void exchangeInfo_broadcast::processStop()
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    socket.close();
}

void exchangeInfo_broadcast::handleMessageWhenUp(cMessage *msg)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    if (msg->isSelfMessage()) {
        ASSERT(msg == selfMsg);
        switch (selfMsg->getKind()) {
            case START:
                processStart();
                break;

            case SEND:
                processSend();
                break;

            case STOP:
                processStop();
                break;

            default:
                throw cRuntimeError("Invalid kind %d in self message", (int)selfMsg->getKind());
        }
    }
    else
        socket.processMessage(msg);
}

void exchangeInfo_broadcast::socketDataArrived(UdpSocket *socket, Packet *packet)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    // process incoming packet
    processPacket(packet);
}

void exchangeInfo_broadcast::socketErrorArrived(UdpSocket *socket, Indication *indication)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    EV_WARN << "Ignoring UDP error report " << indication->getName() << endl;
    delete indication;
}

void exchangeInfo_broadcast::socketClosed(UdpSocket *socket)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    if (operationalState == State::STOPPING_OPERATION)
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void exchangeInfo_broadcast::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

    char buf[100];
    sprintf(buf, "rcvd: %d pks\nsent: %d pks", numReceived, numSent);
    getDisplayString().setTagArg("t", 0, buf);
}

void exchangeInfo_broadcast::processPacket(Packet *pk)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    emit(packetReceivedSignal, pk);
    EV_INFO << "Received packet: " << UdpSocket::getReceivedPacketInfo(pk) << endl;
    delete pk;
    numReceived++;
}

void exchangeInfo_broadcast::handleStartOperation(LifecycleOperation *operation)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    simtime_t start = std::max(startTime, simTime());
    if ((stopTime < SIMTIME_ZERO) || (start < stopTime) || (start == stopTime && startTime == stopTime)) {
        selfMsg->setKind(START);
        scheduleAt(start, selfMsg);
    }
}

void exchangeInfo_broadcast::handleStopOperation(LifecycleOperation *operation)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    cancelEvent(selfMsg);
    socket.close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void exchangeInfo_broadcast::handleCrashOperation(LifecycleOperation *operation)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    cancelEvent(selfMsg);
    socket.destroy();         //TODO  in real operating systems, program crash detected by OS and OS closes sockets of crashed programs.
}

} // namespace inet

