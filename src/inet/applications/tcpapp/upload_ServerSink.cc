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
#include "inet/applications/tcpapp/upload_ServerSink.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/common/packet/Message.h"
#include "inet/networklayer/common/L3AddressResolver.h"

#include "inet/applications/tcpapp/upload_ClientSession.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>

namespace inet {

Define_Module(upload_ServerSink);
Define_Module(upload_ServerSinkThread);

upload_ServerSink::upload_ServerSink()
{
}

upload_ServerSink::~upload_ServerSink()
{
}

void upload_ServerSink::initialize(int stage)
{
    TcpServerHostApp::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        bytesRcvd = 0;
        WATCH(bytesRcvd);

        for(int i=0;i<NUMCLIENT;i++)
        {
            isSelectedAsClient_flag[i] = false;
            completeUploadModel[i] = false;
        }
    }
}



void upload_ServerSink::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

    char buf[160];
    sprintf(buf, "threads: %d\nrcvd: %ld bytes", socketMap.size(), bytesRcvd);
    getDisplayString().setTagArg("t", 0, buf);
}

void upload_ServerSink::run_server()
{
    //std::string s_temp = "mkdir /home/narisu/src/TFF/Model/round" + std::to_string(par("round").intValue());
    std::string s_temp = "mkdir /home/narisu/src/TFF/toyota_distributedFL/pytorch/Model/round" + std::to_string(par("round").intValue());
    //std::cout << "kkkkkkkkkkkk " << s_temp << " " << par("round").intValue() << endl;
    int re = system(s_temp.c_str());

    //s_temp = "rm /home/narisu/src/TFF/Model/globalModel_cifar10.h5";
    s_temp = "rm /home/narisu/src/TFF/toyota_distributedFL/pytorch/Model/globalModel.pt";
    re = system(s_temp.c_str());

    // 3. run FLServer.py
    //s_temp = "/usr/bin/python3.8 /home/narisu/src/TFF/toyota_distributedFL/FLServer_cifar10.py";
    s_temp = "/usr/bin/python3.8 /home/narisu/src/TFF/toyota_distributedFL/pytorch/server.py";
    re = system(s_temp.c_str());
    //all of h5 file will be moved to the folder "roundX"
    //s_temp = "mv /home/narisu/src/TFF/Model/*.h5 /home/narisu/src/TFF/Model/round" + std::to_string(par("round").intValue()) + "/";
    s_temp = "mv /home/narisu/src/TFF/toyota_distributedFL/pytorch/Model/*.pt /home/narisu/src/TFF/toyota_distributedFL/pytorch/Model/round" + std::to_string(par("round").intValue()) + "/";
    //std::cout << "kkkkkkkkkkkk " << s_temp << endl;
    re = system(s_temp.c_str());
    //globalModel_cifar10.h5 renamed as roundX.h5
//    s_temp = "mv /home/narisu/src/TFF/Model/round" + std::to_string(par("round").intValue())
//            + "/globalModel_cifar10.h5 /home/narisu/src/TFF/Model/round" + std::to_string(par("round").intValue())
//            + "/round" + std::to_string(par("round").intValue());
//    std::string s2 = ".h5";
    s_temp = "mv /home/narisu/src/TFF/toyota_distributedFL/pytorch/Model/round" + std::to_string(par("round").intValue()) \
                + "/globalModel.pt /home/narisu/src/TFF/toyota_distributedFL/pytorch/Model/round" + std::to_string(par("round").intValue()) \
                + "/round" + std::to_string(par("round").intValue());
    std::string s2 = ".pt";
    //std::cout << "kkkkkkkkkkkk " << (s_temp + s2).c_str() << endl;
    re = system((s_temp + s2).c_str());
    //file "roundX.h5" is copied to parent folder and renamed globalModel_cifar10.h5
//    s_temp = "cp /home/narisu/src/TFF/Model/round" + std::to_string(par("round").intValue()) + "/round"
//            + std::to_string(par("round").intValue()) + ".h5 /home/narisu/src/TFF/Model/globalModel_cifar10.h5";
    s_temp = "cp /home/narisu/src/TFF/toyota_distributedFL/pytorch/Model/round" + std::to_string(par("round").intValue()) + "/round" \
                + std::to_string(par("round").intValue()) + ".pt /home/narisu/src/TFF/toyota_distributedFL/pytorch/Model/globalModel.pt";
    //std::cout << "kkkkkkkkkkkk " << s_temp.c_str() << endl;
    re = system(s_temp.c_str());
    std::cout << " federated learning complete!" << endl;
    //abort();
    exit(0);
}

void upload_ServerSink::finish()
{
    TcpServerHostApp::finish();
    std::ofstream outfile;
    const char * fname = NULL;
    std::string a = "/home/narisu/src/omnet/omnetpp-5.5.1/samples/new_toyota_FL/examples/federatedlearning/wholeCode/FL.txt";
    std::string d = a;
    fname = d.c_str();
    outfile.open(fname, std::ios::app);
    for(int i=0;i<NUMCLIENT;i++)
    {
        if(isSelectedAsClient_flag[i] == true && completeUploadModel[i] == false){
            std::string s_temp = "rm /home/narisu/src/TFF/toyota_distributedFL/pytorch/Model/" + std::to_string(i) + ".pt";
            int re = system(s_temp.c_str());
        }
        std::cout << i << " isSelectedAsClient_flag: " << isSelectedAsClient_flag[i] << " completeUploadModel: " << completeUploadModel[i] << endl;
        outfile << i << " isSelectedAsClient_flag: " << isSelectedAsClient_flag[i] << " completeUploadModel: " << completeUploadModel[i] << endl;

    }
    outfile.close();
    std::cout << " before finish function -------------------------------" << endl;
    run_server();
    std::cout << " after finish function  ===================================" << endl;
//    recordScalar("bytesRcvd", bytesRcvd);
}


void upload_ServerSinkThread::initialize(int stage)
{
    TcpServerThreadBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        bytesRcvd = 0;
        WATCH(bytesRcvd);
    }
}

void upload_ServerSinkThread::established()
{
    bytesRcvd = 0;
}



void upload_ServerSinkThread::dataArrived(Packet *pk, bool urgent)
{
    long packetLength = pk->getByteLength();
    bytesRcvd += packetLength;
    sinkAppModule->bytesRcvd += packetLength;


    std::cout << getFullPath() << " " << bytesRcvd << " " << simTime() << endl;

    // judge to receive model successfully if or not
    // std::cout << getFullPath() << " " << bytesRcvd << endl;
    std::string cname = getName();
    int client_id = std::atoi(cname.substr(7).c_str()) - 3;
    if(par("modelSize").intValue() == bytesRcvd)
    {
        //local uploaded successfully.
        // true: success
        // false: do not complete.
        sinkAppModule->completeUploadModel[client_id] = true;

        //std::cout << getFullPath() << pk->info() << " kkkkkkkkkkkkk " << endl;
        std::cout << "round" << par("round").intValue() << " Client " << client_id << " uploading model is finished, time " << simTime() << endl;

        std::ofstream outfile;
        const char * fname = NULL;
        std::string a = "/home/narisu/src/omnet/omnetpp-5.5.1/samples/new_toyota_FL/examples/federatedlearning/wholeCode/FL.txt";
        std::string d = a;
        fname = d.c_str();
        outfile.open(fname, std::ios::app);
        outfile <<  "round" << par("round").intValue() << " Client " << client_id << " uploading model is finished, time " << simTime() << endl;
        outfile.close();
    }

    //determine whether run FLServer.py
    //if total data size is equal to client * modelSize
    //start up FLServer.py
    // 1. which nodes are selected as clients
    // 2. delete model which are not selected as client (NOT CLIENT)
    // 3. run FLServer.py

    // 1. which nodes are selected as clients
    for(int i=0;i<NUMCLIENT;i++)
    {
        cModule * m = getParentModule()->getParentModule()->getParentModule()->getSubmodule("V", i)->getSubmodule("app", 3);
        upload_ClientSession * node = check_and_cast<upload_ClientSession *>(m);

        sinkAppModule->isSelectedAsClient_flag[i] = node->isSelectedAsClient_flag;

    }
//    for(int i=0;i<NUMCLIENT;i++)
//    {
//        std::cout << " kkkkkkkkkkkk " << i << " " << sinkAppModule->isSelectedAsClient_flag[i] << endl;
//    }


    // 2. delete model which are not selected as client (NOT CLIENT)
    for(int i=0;i<NUMCLIENT;i++)
    {
        std::stringstream ss;
        ss << "C" << std::setw(3) << std::setfill('0') << i << endl;
        std::string s1;
        ss >> s1;

//        std::string s3 = "rm /home/narisu/src/TFF/Model/" + s1 + ".h5";
        std::string s3 = "rm /home/narisu/src/TFF/toyota_distributedFL/pytorch/Model/" + std::to_string(i) + ".pt";
        const char * cmd = s3.c_str();
        if(sinkAppModule->isSelectedAsClient_flag[i] == false)
        {
            //int re = system(cmd);
        }
    }

    emit(packetReceivedSignal, pk);
    delete pk;
}

void upload_ServerSinkThread::refreshDisplay() const
{
    std::ostringstream os;
    os << (sock ? TcpSocket::stateName(sock->getState()) : "NULL_SOCKET") << "\nrcvd: " << bytesRcvd << " bytes";
    getDisplayString().setTagArg("t", 0, os.str().c_str());
}

} // namespace inet

