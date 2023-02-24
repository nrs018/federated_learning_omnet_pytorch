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

#include "inet/applications/common/SocketTag_m.h"
#include "inet/applications/tcpapp/ClientSink.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/common/packet/Message.h"
#include "inet/networklayer/common/L3AddressResolver.h"

#include "inet/applications/tcpapp/upload_ClientSession.h"
#include "inet/applications/udpapp/exchangeInfo_broadcast.h"
#include "inet/applications/udpapp/exchangeInfo_sink.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>

namespace inet {

Define_Module(ClientSink);
Define_Module(ClientSinkThread);

ClientSink::ClientSink()
{
}

ClientSink::~ClientSink()
{
}

void ClientSink::initialize(int stage)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    TcpServerHostApp::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        bytesRcvd = 0;
        WATCH(bytesRcvd);
        computationCapability = par("computationCapability").doubleValue();

    }
}

void ClientSink::refreshDisplay() const
{
    ////std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    ApplicationBase::refreshDisplay();

    char buf[160];
    sprintf(buf, "threads: %d\nrcvd: %ld bytes", socketMap.size(), bytesRcvd);
    getDisplayString().setTagArg("t", 0, buf);
}


void ClientSink::finish()
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    TcpServerHostApp::finish();

    recordScalar("bytesRcvd", bytesRcvd);
}


void ClientSinkThread::initialize(int stage)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    TcpServerThreadBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        bytesRcvd = 0;
        WATCH(bytesRcvd);
        startUpload_exchange = new cMessage("startUpload_exchange");
    }
}

void ClientSinkThread::established()
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    bytesRcvd = 0;
}

void ClientSinkThread::dataArrived(Packet *pk, bool urgent)
{
    //std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    long packetLength = pk->getByteLength();
    bytesRcvd += packetLength;
    sinkAppModule->bytesRcvd += packetLength;

    if(bytesRcvd == par("modelSize").intValue())
    {
        sinkAppModule->ModelReceivedTime = simTime().dbl();

        std::cout << "round" << par("round").intValue() << " C[" << getParentModule()->getParentModule()->getIndex() << "]" << " model received, time : " << simTime() << endl;

        std::ofstream outfile;
        const char * fname = NULL;
        std::string a = "/home/narisu/src/omnet/omnetpp-5.5.1/samples/new_toyota_FL/examples/federatedlearning/wholeCode/FL.txt";
        fname = a.c_str();

        outfile.open(fname, std::ios::app);
        if(!outfile.is_open()){
            std::cout << "/new_toyota_FL/examples/federatedlearning/wholeCode/FL.txt file is not opened!!!!!!!!!!!!!!!!!!!!!!" << endl;
            exit(0);
        }
        //outfile << "round" << par("round").intValue() << " C[" << getParentModule()->getParentModule()->getIndex() << "]" << " model received, time : " << simTime() << endl;
        outfile.close();


        ///////////  calculate training time ///////


        ///////////  start upload and exchange info ///////
        // 1. define a msg named "startUpload_exchange"
        // 2. find the gate named "radioIn_uploadCMD" in this module "upload_ClientSession"

        // const omnetpp::cModule *receiver
        //int gate = receiver->findGate("lteRadioIn");
        //sendDirect(frame->dup(), 0, frame->getDuration(), receiver, getReceiverGateIndex(receiver));

        /////////// start 丿tensorflow to train client ///////
        // 1. calculate epoch
        // 2. obtain client name
        // 3. run .FLClient.py
        //// 1. calculate epoch //
//        cModule *m = getParentModule()->getParentModule()->getSubmodule("app", 1);
//        exchangeInfo_broadcast * ex = check_and_cast<exchangeInfo_broadcast *>(m);
//        double trainingTime = (ex->TrainingDeadline - sinkAppModule->ModelReceivedTime) / sinkAppModule->computationCapability;
//        int epoch = 1;
//        if(ex->sampleQuantity >= 600)
//        {
//            epoch = int(trainingTime / 0.881) + 1;
//        }
//        else  // smaller than 600 sample
//        {
//            epoch = int(trainingTime / 0.03) + 1;
//        }
//        // 2. obtain client name
//        std::stringstream ss;
//        ss << "C" << std::setw(3) << std::setfill('0') << getParentModule()->getParentModule()->getIndex() << " " << epoch << endl;
//        std::string s1;
//        ss >> s1;
//        std::string s2 = "/usr/bin/python3.8 /home/narisu/src/TFF/toyota_distributedFL/FLClient_cifar10.py ";
//        std::string s3 = s2 + " " + s1 + " " + std::to_string(epoch);
//        std::cout << " kkkkkkkkkkkkkkkkkkkkkkkkkkkkk " << s3 << " jjjjjjjjjjjjjj " << epoch << endl;
//        // 3. run FLClient.py
//        const char * cmd = s3.c_str();
//        int re = system(cmd);
//
//        // read delta loss from file
//        std::stringstream ss1 ;
//        ss1 << "C" << std::setw(3) << std::setfill('0') << getParentModule()->getParentModule()->getIndex() << endl;
//        ss1 >> s1;
//        s2 = "/home/narisu/src/TFF/toyota_distributedFL/objectiveFunction/" + s1 + ".txt";
//
//        //std::cout << s2 << endl;
//        std::ifstream infile(s2);
//        if (!infile.is_open()) {
//                std::cout << "Could not open the file - '" << endl;
//                exit(0);
//        }
//        double deltaloss, accuracy;
//        std::string l;
//        getline(infile, l);
//        deltaloss = std::stod(l);
//        getline(infile, l);
//        accuracy = std::stod(l);


        // 1.5 = 30/20 , epoch:30,  batch size : 20
        // extcution time foe one batch size: 0.06s
        //sinkAppModule->trainingTime = (broad->sampleQuantity * 1.5 * 0.06 * sinkAppModule->computationCapability);

        cModule * receiver = getParentModule()->getParentModule()->getSubmodule("app", 3);
        upload_ClientSession *clientsession = check_and_cast<upload_ClientSession *>(receiver);
        int gate = clientsession->findGate("radioIn_uploadCMD");

        /// update globalInfo variable

        cModule * mod = getParentModule()->getParentModule()->getSubmodule("app", 1);
        exchangeInfo_broadcast * info = check_and_cast<exchangeInfo_broadcast * >(mod);
//
//        /////////////////////////////////////////////////////
        //update variable "globalInfo"
        cModule *m2 = getParentModule()->getParentModule()->getSubmodule("app", 0);
        ClientSink *cs = check_and_cast<ClientSink * >(m2);
//        info->deltaLoss = (5 + deltaloss) / 7;
//        info->globalInfo = par("alpha0").doubleValue() * info->sampleQuantity / 1000.0
//                         + par("alpha1").doubleValue() * (65 - cs->ModelReceivedTime) / 50
//                         + par("alpha2").doubleValue() * info->deltaLoss
//                         + par("alpha3").doubleValue() * (20 - cs->computationCapability)/20;

//        std::cout << info->sampleQuantity / 1000.0 << endl;
//        std::cout << (65 - cs->ModelReceivedTime) / 50 << endl;
//        std::cout << info->deltaLoss << endl;
//        std::cout << (20 - cs->computationCapability)/20 << endl;

        std::string a_clientINFO = "/home/narisu/src/TFF/toyota_distributedFL/pytorch/globalINFO.txt";
        const char * fname_clientINFO = NULL;
        fname_clientINFO = a_clientINFO.c_str();

        std::ifstream in;
        in.open(fname_clientINFO, std::ios::in);
        if(!in.is_open()){
            std::cout << "globalINFO.txt is NOT opened !!!!!!" << endl;
            exit(0);
        }
        double SQ[NUMCLIENT], CC[NUMCLIENT], TA[NUMCLIENT], Loss[NUMCLIENT], score[NUMCLIENT];
        for(int i=0;i<NUMCLIENT;i++){
            in >> SQ[i] >> CC[i] >> TA[i] >> Loss[i] >> score[i] ;
//            std::cout << i << " " << SQ[i] << " " << CC[i] << " " << TA[i] << " " << Loss[i] << " " << score[i] << endl;
        }
        in.close();
        cModule *index = getParentModule()->getParentModule();
        info->globalInfo = score[index->getIndex()];
        double transmitDelay = std::max(info->TrainingDeadline - sinkAppModule->ModelReceivedTime, simTime().dbl());

        // training time = transmitDelay
        //double transmitDelay = SQ[index->getIndex()] * 5 / 16 * 0.001 * CC[index->getIndex()];
        outfile.open(fname, std::ios::app);
        if(!outfile.is_open()){
            std::cout << "/new_toyota_FL/examples/federatedlearning/wholeCode/FL.txt file is not opened!!" << endl;
            exit(0);
        }
        outfile << "round" << par("round").intValue() \
                << " V" << getParentModule()->getParentModule()->getIndex() \
                //<< ", model received time:" << cs->ModelReceivedTime
                << "\t CC " << CC[index->getIndex()];
        outfile << "\t SQ " << SQ[index->getIndex()]\
                << "\t TA " << TA[index->getIndex()] << " KB "\
                << "\t Loss " << Loss[index->getIndex()];
                //<< ", training time: " << transmitDelay;
        outfile << "\t Score " << info->globalInfo << endl;
        outfile.close();

//        double transmitDelay = info->TrainingDeadline - sinkAppModule->ModelReceivedTime - 3;
//        outfile.open(fname, std::ios::app);
//        outfile << "round" << par("round").intValue()
//                << " C[" << getParentModule()->getParentModule()->getIndex() << "]"
//                << ", model received time:" << cs->ModelReceivedTime
//                << ", computation Capablity: " << sinkAppModule->computationCapability;
//        outfile << ", sample quantity : " << info->sampleQuantity
//                << ", training time: " << transmitDelay;
//        outfile << ", deltaLoss: " << info->deltaLoss;
//        outfile << " , globalInfo : " << info->globalInfo << endl;
//        outfile.close();


        //sendDirect(startUpload_exchange, sinkAppModule->trainingTime, 0, clientsession, gate);
        sendDirect(startUpload_exchange, transmitDelay, 0, clientsession, gate);

    }

    emit(packetReceivedSignal, pk);
    delete pk;
}

void ClientSinkThread::refreshDisplay() const
{
    ////std::cout << getFullPath() << " " << __FILE__ << " " << __FUNCTION__ << " " << simTime() << endl;
    std::ostringstream os;
    os << (sock ? TcpSocket::stateName(sock->getState()) : "NULL_SOCKET") << "\nrcvd: " << bytesRcvd << " bytes";
    getDisplayString().setTagArg("t", 0, os.str().c_str());
}

} // namespace inet

