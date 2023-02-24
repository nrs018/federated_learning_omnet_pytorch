//
// Copyright (C) 2004 Andras Varga
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
#include "inet/applications/tcpapp/Broadcast.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/TagBase_m.h"
#include "inet/common/TimeTag_m.h"
#include "inet/common/packet/Packet.h"
#include "inet/common/packet/chunk/ByteCountChunk.h"
#include "inet/common/packet/chunk/BytesChunk.h"
#include "inet/networklayer/common/L3AddressResolver.h"

#include "inet/applications/udpapp/exchangeInfo_sink.h"
#include "inet/applications/udpapp/exchangeInfo_broadcast.h"
#include "inet/mobility/static/StationaryMobility.h"
#include "inet/applications/tcpapp/ClientSink.h"

#include "veins_inet/VeinsInetMobility.h"
#include "inet/mobility/single/SUMOMobility.h"
#include "inet/applications/tcpapp/upload_ServerSink.h"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace inet {

Define_Module(Broadcast);

#define MSGKIND_CONNECT    1
#define MSGKIND_SEND       2
#define MSGKIND_CLOSE      3


Broadcast::~Broadcast()
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    cancelAndDelete(timeoutMsg);
}

void Broadcast::initialize(int stage)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;

    TcpAppBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        activeOpen = par("active");
        tOpen = par("tOpen");
        tSend = par("tSend");
        tClose = par("tClose");
        sendBytes = par("sendBytes");
        commandIndex = 0;

        const char *script = par("sendScript");
        parseScript(script);

        if (sendBytes > 0 && commands.size() > 0)
            throw cRuntimeError("Cannot use both sendScript and tSend+sendBytes");
        if (sendBytes > 0)
            commands.push_back(Command(tSend, sendBytes));
        if (commands.size() == 0)
            throw cRuntimeError("sendScript is empty");
        timeoutMsg = new cMessage("timer");
    }

}

void Broadcast::handleStartOperation(LifecycleOperation *operation)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    if (simTime() <= tOpen) {
        timeoutMsg->setKind(MSGKIND_CONNECT);
        scheduleAt(tOpen, timeoutMsg);
    }
}

void Broadcast::handleStopOperation(LifecycleOperation *operation)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    cancelEvent(timeoutMsg);
    if (socket.isOpen())
        close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void Broadcast::handleCrashOperation(LifecycleOperation *operation)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    cancelEvent(timeoutMsg);
    if (operation->getRootModule() != getContainingNode(this))
        socket.destroy();
}

void Broadcast::handleTimer(cMessage *msg)
{
//    std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    switch (msg->getKind()) {
        case MSGKIND_CONNECT:
            if (activeOpen){

                connect(); // sending will be scheduled from socketEstablished()
            }
            else
                throw cRuntimeError("TODO");
            break;

        case MSGKIND_SEND:
            sendData();
            break;

        case MSGKIND_CLOSE:
            close();
            break;

        default:
            throw cRuntimeError("Invalid timer msg: kind=%d", msg->getKind());
    }
}

void Broadcast::sendData()
{
//    std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    long numBytes = commands[commandIndex].numBytes;
    EV_INFO << "sending data with " << numBytes << " bytes\n";
    sendPacket(createDataPacket(numBytes));

    if (++commandIndex < (int)commands.size()) {
        simtime_t tSend = commands[commandIndex].tSend;
        scheduleAt(std::max(tSend, simTime()), timeoutMsg);
    }
    else {
        timeoutMsg->setKind(MSGKIND_CLOSE);
        scheduleAt(std::max(tClose, simTime()), timeoutMsg);
    }
}

Packet *Broadcast::createDataPacket(long sendBytes)
{
//    std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;

    const char *dataTransferMode = par("dataTransferMode");
    Ptr<Chunk> payload;
    if (!strcmp(dataTransferMode, "bytecount")) {
        payload = makeShared<ByteCountChunk>(B(sendBytes));
    }
    else if (!strcmp(dataTransferMode, "object")) {
        const auto& applicationPacket = makeShared<ApplicationPacket>();
        applicationPacket->setChunkLength(B(sendBytes));
        payload = applicationPacket;
    }
    else if (!strcmp(dataTransferMode, "bytestream")) {
        const auto& bytesChunk = makeShared<BytesChunk>();
        std::vector<uint8_t> vec;
        vec.resize(sendBytes);
        for (int i = 0; i < sendBytes; i++)
            vec[i] = (bytesSent + i) & 0xFF;
        bytesChunk->setBytes(vec);
        payload = bytesChunk;
    }
    else
        throw cRuntimeError("Invalid data transfer mode: %d", dataTransferMode);
    payload->addTag<CreationTimeTag>()->setCreationTime(simTime());
    Packet *packet = new Packet("data1");
    packet->insertAtBack(payload);

    // store client information, include client loss, position (related to throughput calculation),
    // computational capability, sample quantity.
    // These information are stored in the file '/home/narisu/src/TFF/toyota_distributedFL/pytorch/*.txt

//    if(this->getIndex() == 0){
    cModule *mod = this->getParentModule()->getSubmodule("app", NUMCLIENT);
    upload_ServerSink * isrun_client_selection = check_and_cast<upload_ServerSink *>(mod);

    if(isrun_client_selection->isrun_client_selection == false){
        isrun_client_selection->isrun_client_selection = true;
        std::string s2 = "/usr/bin/python3.8 /home/narisu/src/TFF/toyota_distributedFL/pytorch/evaluate_clients.py";
        const char * cmd = s2.c_str();
        int re = system(cmd);

        std::ofstream outfile;
        const char * fname = NULL;
        std::string a = "/home/narisu/src/TFF/toyota_distributedFL/pytorch/client_information.txt";
        std::string d = a;
        fname = d.c_str();
        system("rm /home/narisu/src/TFF/toyota_distributedFL/pytorch/client_information.txt");
        outfile.open(fname, std::ios::app);
        outfile << "id x y CC SQ" << endl;
        for(int i=0;i<NUMCLIENT;i++){
            cModule *mobi = getParentModule()->getParentModule()->getSubmodule("V", i)->getSubmodule("mobility", 0);
//            StationaryMobility * SM = check_and_cast<StationaryMobility *>(mobi);
//            veins::VeinsInetMobility *SM = check_and_cast<veins::VeinsInetMobility *>(mobi);
            inet::SUMOMobility *SM = check_and_cast<inet::SUMOMobility *>(mobi);


            cModule *mod = getParentModule()->getParentModule()->getSubmodule("V", i)->getSubmodule("app", 0);
            ClientSink *CC = check_and_cast<ClientSink *>(mod);
            cModule *mod2 = getParentModule()->getParentModule()->getSubmodule("V", i)->getSubmodule("app", 1);
            exchangeInfo_broadcast *SQ = check_and_cast<exchangeInfo_broadcast *>(mod2);
            outfile << i << " " << SM->getCurrentPosition().x << " " << SM->getCurrentPosition().y << " ";
            outfile << CC->computationCapability << " " << SQ->sampleQuantity << endl;

            //std::cout << i << " " << SM->getCurrentPosition().x << " " << SM->getCurrentPosition().y << " ";
            //std::cout << CC->computationCapability << " " << SQ->sampleQuantity << endl;

        }
        outfile.close();

        // execute client selection.py to generate globalINFO.txt

        s2 = "/usr/bin/python3.8 /home/narisu/src/TFF/toyota_distributedFL/pytorch/client_selection.py";
        std::cout << "client selection.py  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
        cmd = s2.c_str();
        re = system(cmd);

    }

    return packet;
}

void Broadcast::socketEstablished(TcpSocket *socket)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    TcpAppBase::socketEstablished(socket);

    ASSERT(commandIndex == 0);
    timeoutMsg->setKind(MSGKIND_SEND);
    simtime_t tSend = commands[commandIndex].tSend;
    scheduleAt(std::max(tSend, simTime()), timeoutMsg);
}

void Broadcast::socketDataArrived(TcpSocket *socket, Packet *msg, bool urgent)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    TcpAppBase::socketDataArrived(socket, msg, urgent);
}

void Broadcast::socketClosed(TcpSocket *socket)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    TcpAppBase::socketClosed(socket);
    cancelEvent(timeoutMsg);
    if (operationalState == State::STOPPING_OPERATION && !this->socket.isOpen())
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void Broadcast::socketFailure(TcpSocket *socket, int code)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    TcpAppBase::socketFailure(socket, code);
    cancelEvent(timeoutMsg);
}

void Broadcast::parseScript(const char *script)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    const char *s = script;

    EV_DEBUG << "parse script \"" << script << "\"\n";
    while (*s) {
        // parse time
        while (isspace(*s))
            s++;

        if (!*s || *s == ';')
            break;

        const char *s0 = s;
        simtime_t tSend = strtod(s, &const_cast<char *&>(s));

        if (s == s0)
            throw cRuntimeError("Syntax error in script: simulation time expected");

        // parse number of bytes
        while (isspace(*s))
            s++;

        if (!isdigit(*s))
            throw cRuntimeError("Syntax error in script: number of bytes expected");

        long numBytes = strtol(s, nullptr, 10);

        while (isdigit(*s))
            s++;

        // add command
        EV_DEBUG << " add command (" << tSend << "s, " << numBytes << "B)\n";
        commands.push_back(Command(tSend, numBytes));

        // skip delimiter
        while (isspace(*s))
            s++;

        if (!*s)
            break;

        if (*s != ';')
            throw cRuntimeError("Syntax error in script: separator ';' missing");

        s++;

        while (isspace(*s))
            s++;
    }
    EV_DEBUG << "parser finished\n";
}

void Broadcast::finish()
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    EV << getFullPath() << ": received " << bytesRcvd << " bytes in " << packetsRcvd << " packets\n";
    recordScalar("bytesRcvd", bytesRcvd);
    recordScalar("bytesSent", bytesSent);
}

void Broadcast::refreshDisplay() const
{
    ////std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    TcpAppBase::refreshDisplay();

    std::ostringstream os;
    os << TcpSocket::stateName(socket.getState()) << "\nsent: " << bytesSent << " bytes\nrcvd: " << bytesRcvd << " bytes";
    getDisplayString().setTagArg("t", 0, os.str().c_str());
}

} // namespace inet

