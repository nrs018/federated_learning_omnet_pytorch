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
#include "inet/applications/tcpapp/upload_ClientSession.h"
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
#include "inet/applications/tcpapp/ClientSink.h"
#include "inet/mobility/static/StationaryMobility.h"

#include "veins_inet/VeinsInetMobility.h"
#include "inet/mobility/single/SUMOMobility.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>

namespace inet {

Define_Module(upload_ClientSession);

#define MSGKIND_CONNECT    1
#define MSGKIND_SEND       2
#define MSGKIND_CLOSE      3
#define CHECK_GLOBAL_INFO  4


upload_ClientSession::~upload_ClientSession()
{
    cancelAndDelete(timeoutMsg);
}

void upload_ClientSession::initialize(int stage)
{
    TcpAppBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        activeOpen = par("active");
        //tOpen = par("tOpen");
        //tSend = par("tSend");
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
        check_global_info = new cMessage("check_global_info");

        SelectClientNumPerCoverage = par("SelectClientNumPerCoverage").intValue();
    }
}

void upload_ClientSession::handleStartOperation(LifecycleOperation *operation)
{
//    if (simTime() <= tOpen) {
//        timeoutMsg->setKind(MSGKIND_CONNECT);
//        scheduleAt(tOpen, timeoutMsg);
//    }
}

void upload_ClientSession::handleStopOperation(LifecycleOperation *operation)
{
    cancelEvent(timeoutMsg);
    if (socket.isOpen())
        close();
    delayActiveOperationFinish(par("stopOperationTimeout"));
}

void upload_ClientSession::handleCrashOperation(LifecycleOperation *operation)
{
    cancelEvent(timeoutMsg);
    if (operation->getRootModule() != getContainingNode(this))
        socket.destroy();
}
// true represents this node can upload model.
// false represent this node do not upload model.
bool upload_ClientSession::selectClient()
{
    double tmp_GlobalINFO_value[NUMCLIENT];
    int tmp_GlobalINFO_id[NUMCLIENT];
    double tmp_GlobalINFO_x[NUMCLIENT];
    double tmp_GlobalINFO_y[NUMCLIENT];

    double tmp_top_GlobalINFO_value[SelectClientNumPerCoverage];
    double tmp_top_GlobalINFO_x[SelectClientNumPerCoverage];
    double tmp_top_GlobalINFO_y[SelectClientNumPerCoverage];
    int tmp_top_GlobalINFO_id[SelectClientNumPerCoverage];


    cModule *m = getParentModule()->getSubmodule("app", 2);
    exchangeInfo_sink * sinkGlobalInfo = check_and_cast<exchangeInfo_sink * >(m);

    /////////////////////////////////////////////////////
    //update variable "globalInfo"

    // assign self value to array globalINFO
    cModule * mod = getParentModule()->getSubmodule("app", 1);
    exchangeInfo_broadcast * info = check_and_cast<exchangeInfo_broadcast * >(mod);

    cModule *m2 = getParentModule()->getSubmodule("app", 0);
    ClientSink *cs = check_and_cast<ClientSink * >(m2);

    // obtain "deltaLoss"
    std::stringstream ss;
    ss << "/home/narisu/src/TFF/toyota_distributedFL/objectiveFunction/C" << std::setw(3) << std::setfill('0') << getParentModule()->getIndex() << endl;
    std::string s1;
    ss >> s1;
    std::string s2 = s1 + ".txt";

    std::string line;
    std::ifstream infile(s2.c_str());
    double deltaLoss = 0;
    double deltaAcc = 0;
    if(infile.is_open())
    {
        infile >> deltaLoss >> deltaAcc;
    }

    //info->globalInfo = info->sampleQuantity / 1000 + (65 - cs->ModelReceivedTime) / 50 + info->deltaLoss + (20 - cs->computationCapability)/20;
    //info->globalInfo = info->sampleQuantity / 1000 + (65 - cs->ModelReceivedTime) / 50 + (5 - deltaLoss) / 5 + (20 - cs->computationCapability)/20;

    m2 = getParentModule()->getSubmodule("mobility", 0);
//    StationaryMobility *sm = check_and_cast<StationaryMobility *>(m2);
//    veins::VeinsInetMobility *sm = check_and_cast<veins::VeinsInetMobility *>(m2);
    inet::SUMOMobility *sm = check_and_cast<inet::SUMOMobility *>(m2);

    inet::Coord t_pos;

    for(int i=0;i<NUMCLIENT;i++)
    {
        tmp_GlobalINFO_value[i] = sinkGlobalInfo->globalINFO[i];
        tmp_GlobalINFO_x[i] = sinkGlobalInfo->globalINFO_x[i];
        tmp_GlobalINFO_y[i] = sinkGlobalInfo->globalINFO_y[i];
        tmp_GlobalINFO_id[i] = i;
    }

    ////////////////////////////////////////////////
    //std::cout << "pppppppppppppppp " << getParentModule()->getIndex() << " " << info->globalInfo << endl;
    //exit(0);
    tmp_GlobalINFO_value[getParentModule()->getIndex()] = info->globalInfo;
    tmp_GlobalINFO_x[getParentModule()->getIndex()] = sm->getCurrentPosition().x;
    tmp_GlobalINFO_y[getParentModule()->getIndex()] = sm->getCurrentPosition().y;
    tmp_GlobalINFO_id[getParentModule()->getIndex()] = getParentModule()->getIndex();


    for(int i=0;i<NUMCLIENT;i++)
    {
        t_pos.x = tmp_GlobalINFO_x[i];
        t_pos.y = tmp_GlobalINFO_y[i];
        t_pos.z = sm->getCurrentPosition().z;

        double l = sm->getCurrentPosition().distance(t_pos);

        if(l > par("selectionRange").doubleValue())
        {
            tmp_GlobalINFO_value[i] = -1111;
        }
    }

    /////   sorting global info ////
    double max = -10000;
    int pos = 0;
    double tmp;
    int tmp_pos;
    for(int i=0;i<NUMCLIENT;i++)
    {
        max = -10000;
        pos = i;
        for(int j=i;j<NUMCLIENT;j++)
        {
            if(max < tmp_GlobalINFO_value[j])
            {
                max = tmp_GlobalINFO_value[j];
                pos = j;
            }
        }
        tmp = tmp_GlobalINFO_value[i];
        tmp_pos = tmp_GlobalINFO_id[i];

        tmp_GlobalINFO_value[i] = tmp_GlobalINFO_value[pos];
        tmp_GlobalINFO_id[i] = tmp_GlobalINFO_id[pos];

        tmp_GlobalINFO_value[pos] = tmp;
        tmp_GlobalINFO_id[pos] = tmp_pos;

        //// exchange x positon ///
        tmp = tmp_GlobalINFO_x[i];
        tmp_GlobalINFO_x[i] = tmp_GlobalINFO_x[pos];
        tmp_GlobalINFO_x[pos] = tmp;
        //// exchange y postion ///
        tmp = tmp_GlobalINFO_y[i];
        tmp_GlobalINFO_y[i] = tmp_GlobalINFO_y[pos];
        tmp_GlobalINFO_y[pos] = tmp;

    }

    ///  assign top m value to tmp_top_GlobalINFO
    for(int i=0;i<SelectClientNumPerCoverage;i++)
    {
        tmp_top_GlobalINFO_value[i] = tmp_GlobalINFO_value[i];
        tmp_top_GlobalINFO_id[i] = tmp_GlobalINFO_id[i];
        tmp_top_GlobalINFO_x[i] = tmp_GlobalINFO_x[i];
        tmp_top_GlobalINFO_y[i] = tmp_GlobalINFO_y[i];
    }

    ///// whether this node contains in top_globalINFO
//    for(int i=0;i<SelectClientNumPerCoverage;i++)
//    {
//        std::cout << "round" << par("round").intValue() << " top m " << getFullPath() << " " << tmp_top_GlobalINFO_id[i] << " " << tmp_top_GlobalINFO_value[i] << " ";
//        std::cout << tmp_top_GlobalINFO_x[i] << " " << tmp_top_GlobalINFO_y[i] << endl;
//        std::ofstream outfile;
//        const char * fname = NULL;
//        std::string a = "/home/narisu/src/omnet/omnetpp-5.5.1/samples/new_toyota_FL/examples/federatedlearning/wholeCode/FL.txt";
//        std::string d = a;
//        fname = d.c_str();
//        outfile.open(fname, std::ios::app);
//        outfile <<  "round" << par("round").intValue() << " top m " << getFullPath() << " " << tmp_top_GlobalINFO_id[i] << " " << tmp_top_GlobalINFO_value[i] << " ";
//        std::cout << tmp_top_GlobalINFO_x[i] << " " << tmp_top_GlobalINFO_y[i] << endl;
//        outfile.close();
//    }
//
    for(int i=0;i<NUMCLIENT;i++)
    {
//        std::cout << "round" << par("round").intValue() << " --globalINFO-- " << getFullPath() << " " << tmp_GlobalINFO_id[i] << " " << tmp_GlobalINFO_value[i] << " " ;
//        std::cout << tmp_GlobalINFO_x[i] << " " << tmp_GlobalINFO_y[i] << endl;
//        std::ofstream outfile;
//        const char * fname = NULL;
//        std::string a = "/home/narisu/src/omnet/omnetpp-5.5.1/samples/new_toyota_FL/examples/federatedlearning/wholeCode/FL.txt";
//        std::string d = a;
//        fname = d.c_str();
//        outfile.open(fname, std::ios::app);
//        outfile <<  "round" << par("round").intValue() << " --globalINFO-- " << getFullPath() << " " << tmp_GlobalINFO_id[i] << " " << tmp_GlobalINFO_value[i] << " " ;
//        std::cout << tmp_GlobalINFO_x[i] << " " << tmp_GlobalINFO_y[i] << endl;
//        outfile.close();
    }

    for(int i=0;i<SelectClientNumPerCoverage;i++)
    {
        if(getParentModule()->getIndex() == tmp_top_GlobalINFO_id[i])
        {
            for(int i=0;i<SelectClientNumPerCoverage;i++)
            {
                std::cout << "round" << par("round").intValue() << " top m " << getFullPath() << " " << tmp_top_GlobalINFO_id[i] << " " << tmp_top_GlobalINFO_value[i];
                std::cout << " " << tmp_top_GlobalINFO_x[i] << " " << tmp_top_GlobalINFO_y[i] << endl;

                std::ofstream outfile;
                const char * fname = NULL;
                std::string a = "/home/narisu/src/omnet/omnetpp-5.5.1/samples/new_toyota_FL/examples/federatedlearning/wholeCode/FL.txt";
                std::string d = a;
                fname = d.c_str();
                outfile.open(fname, std::ios::app);
                outfile <<  "round" << par("round").intValue() << " top m " << getFullPath() << " " << tmp_top_GlobalINFO_id[i] << " " << tmp_top_GlobalINFO_value[i] << " ";
                outfile << tmp_top_GlobalINFO_x[i] << " " << tmp_top_GlobalINFO_y[i] << endl;
                outfile.close();
            }

            for(int i=0;i<NUMCLIENT;i++)
            {
                std::cout << "round" << par("round").intValue() << " --globalINFO-- " << getFullPath() << " " << tmp_GlobalINFO_id[i] << " " << tmp_GlobalINFO_value[i] << " ";
                std::cout << tmp_GlobalINFO_x[i] << " " << tmp_GlobalINFO_y[i] << endl;
                std::ofstream outfile;
                const char * fname = NULL;
                std::string a = "/home/narisu/src/omnet/omnetpp-5.5.1/samples/new_toyota_FL/examples/federatedlearning/wholeCode/FL.txt";
                std::string d = a;
                fname = d.c_str();
                outfile.open(fname, std::ios::app);
                outfile <<  "round" << par("round").intValue() << " --globalINFO-- " << getFullPath() << " " \
                        << tmp_GlobalINFO_id[i] << " " << tmp_GlobalINFO_value[i] << " ";
                outfile << tmp_GlobalINFO_x[i] << " " << tmp_GlobalINFO_y[i] << endl;
                outfile.close();
            }
            return true;
        }
    }
    return false;
}


void upload_ClientSession::handleTimer(cMessage *msg)
{
    //std::cout << "qqqqqqqqqqqqqqqqqqqqqqqq " << endl;
    if(std::strcmp(msg->getName(), "startUpload_exchange") == 0){
        //std::cout << getFullPath() << " received msg xxxxxxxxxxxxxxxxxxxxxxxxxx " << msg->getName() << " time " << simTime() << endl;
        check_global_info->setKind(CHECK_GLOBAL_INFO);
        scheduleAt(simTime() + par("checkInterval").doubleValue(), check_global_info);
    }
    else{
        switch (msg->getKind()) {
            case MSGKIND_CONNECT:
                if (activeOpen)
                    connect(); // sending will be scheduled from socketEstablished()
                else
                    throw cRuntimeError("TODO");
                break;

            case MSGKIND_SEND:
                sendData();
                break;

            case MSGKIND_CLOSE:
                close();
                break;

            case CHECK_GLOBAL_INFO:
            {
                bool flag = selectClient();
                /// true represent that node is selected as client.
                if(flag == true )//&& begin_upload == false)
                {
                    isSelectedAsClient_flag = flag;
                    //begin_upload = true;
                    std::cout << getFullPath() << " selected as client , time " << simTime() << endl;

                    std::ofstream outfile;
                    const char * fname = NULL;
                    std::string a = "/home/narisu/src/omnet/omnetpp-5.5.1/samples/new_toyota_FL/examples/federatedlearning/wholeCode/FL.txt";
                    std::string d = a;
                    fname = d.c_str();
                    outfile.open(fname, std::ios::app);
                    outfile <<  "round" << par("round").intValue() << " " << getFullPath() << " selected as client , time " << simTime() << endl;;

                    // training pytorch/client.py
                    std::string s2 = "/usr/bin/python3.8 /home/narisu/src/TFF/toyota_distributedFL/pytorch/client.py " ;
                    int client_id = getParentModule()->getIndex();
                    std::string ss = s2 + std::to_string(client_id);
                    const char * cmd = ss.c_str();
                    int re = system(cmd);

                    ///////// calculate EPOCHS /////////
                    cModule *m = getParentModule()->getSubmodule("app", 1);
                    exchangeInfo_broadcast * ex = check_and_cast<exchangeInfo_broadcast *>(m);
//                    cModule * m1 = getParentModule()->getSubmodule("app", 0);
//                    ClientSink * cs = check_and_cast<ClientSink *>(m1);
//                    double trainingTime = (ex->TrainingDeadline - cs->ModelReceivedTime) / cs->computationCapability;
//                    int epoch = 1;
//                    if(ex->sampleQuantity >= 600)
//                    {
//                        epoch = int(trainingTime / 0.881) + 1;
//                    }
//                    else  // smaller than 600 sample
//                    {
//                        epoch = int(trainingTime / 0.03) + 1;
//                    }
//                    std::cout << " , EPOCHS: " << epoch << endl;
//                    outfile << " , EPOCHS: " << epoch << endl;
//                    outfile.close();


                    tOpen = std::max(double(ex->TrainingDeadline), simTime().dbl()); //simTime();
                    tSend = std::max(double(ex->TrainingDeadline), simTime().dbl()); //simTime();
                    //std::cout << tOpen << " " << simTime() << endl;
                    timeoutMsg->setKind(MSGKIND_CONNECT);
                    scheduleAt(tOpen, timeoutMsg);
                    //std::cout << " start upload dddddddddddddddddddddddddddddd" << getFullPath() << endl;
                }
                else /// false represent that the node is not selected as client, continue waiting
                {
                    //std::cout << "continue waiting ggggggggggggggggggggg " << getFullPath() << endl;
                    check_global_info->setKind(CHECK_GLOBAL_INFO);
                    scheduleAt(simTime() + par("checkInterval").doubleValue(), check_global_info);
                }
                break;
            }
            default:
                throw cRuntimeError("Invalid timer msg: kind=%d", msg->getKind());
        }
    }
}

void upload_ClientSession::sendData()
{
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

Packet *upload_ClientSession::createDataPacket(long sendBytes)
{
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
    return packet;
}

void upload_ClientSession::socketEstablished(TcpSocket *socket)
{
    TcpAppBase::socketEstablished(socket);

    ASSERT(commandIndex == 0);
    timeoutMsg->setKind(MSGKIND_SEND);
    simtime_t tSend = commands[commandIndex].tSend;
    scheduleAt(std::max(tSend, simTime()), timeoutMsg);
}

void upload_ClientSession::socketDataArrived(TcpSocket *socket, Packet *msg, bool urgent)
{
    TcpAppBase::socketDataArrived(socket, msg, urgent);
}

void upload_ClientSession::socketClosed(TcpSocket *socket)
{
    TcpAppBase::socketClosed(socket);
    cancelEvent(timeoutMsg);
    if (operationalState == State::STOPPING_OPERATION && !this->socket.isOpen())
        startActiveOperationExtraTimeOrFinish(par("stopOperationExtraTime"));
}

void upload_ClientSession::socketFailure(TcpSocket *socket, int code)
{
    TcpAppBase::socketFailure(socket, code);
    cancelEvent(timeoutMsg);
}

void upload_ClientSession::parseScript(const char *script)
{
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

void upload_ClientSession::finish()
{
    EV << getFullPath() << ": received " << bytesRcvd << " bytes in " << packetsRcvd << " packets\n";
    std::cout << getFullPath() << ": received " << bytesRcvd << " bytes in " << packetsRcvd << " packets\n";
    recordScalar("bytesRcvd", bytesRcvd);
    recordScalar("bytesSent", bytesSent);
}

void upload_ClientSession::refreshDisplay() const
{
    TcpAppBase::refreshDisplay();

    std::ostringstream os;
    os << TcpSocket::stateName(socket.getState()) << "\nsent: " << bytesSent << " bytes\nrcvd: " << bytesRcvd << " bytes";
    getDisplayString().setTagArg("t", 0, os.str().c_str());
}

} // namespace inet

