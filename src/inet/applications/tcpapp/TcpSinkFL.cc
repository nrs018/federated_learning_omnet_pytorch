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
#include "inet/applications/tcpapp/TcpSinkFL.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/common/packet/Message.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/mobility/static/StationaryMobility.h"

#include "veins_inet/VeinsInetMobility.h"
#include "inet/mobility/single/SUMOMobility.h"

#include <fstream>
#include <iostream>


namespace inet {

Define_Module(TcpSinkFL);
Define_Module(TcpSinkFLThread);

TcpSinkFL::TcpSinkFL()
{
}

TcpSinkFL::~TcpSinkFL()
{
}

void TcpSinkFL::initialize(int stage)
{

    TcpServerHostApp::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        bytesRcvd = 0;
        WATCH(bytesRcvd);


    }
}

void TcpSinkFL::refreshDisplay() const
{
    ApplicationBase::refreshDisplay();

    char buf[160];
    sprintf(buf, "threads: %d\nrcvd: %ld bytes", socketMap.size(), bytesRcvd);
    getDisplayString().setTagArg("t", 0, buf);
}


void TcpSinkFL::finish()
{
    TcpServerHostApp::finish();

    recordScalar("bytesRcvd", bytesRcvd);
}


void TcpSinkFLThread::initialize(int stage)
{
    TcpServerThreadBase::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        bytesRcvd = 0;
        WATCH(bytesRcvd);
    }
}

void TcpSinkFLThread::established()
{
    bytesRcvd = 0;
    //std::cout << getFullPath() << " " << simTime() << endl;
}

void TcpSinkFLThread::dataArrived(Packet *pk, bool urgent)
{
    std::ofstream outfile;
    int repeat = sinkAppModule->par("re");
    const char * fname = NULL;
    std::string a = "/home/narisu/src/omnet/omnetpp-5.5.1/samples/new_toyota_FL/examples/federatedlearning/broadcastmodel/pos/pos";
    std::string b = std::to_string(repeat);
    std::string c = ".txt";
    std::string d = a + b + c;
    fname = d.c_str();
    if(flagpos == true){
        outfile.open(fname, std::ios::app);
        cModule *cmod = sinkAppModule->getParentModule()->getSubmodule("mobility");
//        StationaryMobility *sm = check_and_cast<StationaryMobility *>(cmod);
//        veins::VeinsInetMobility *sm = check_and_cast<veins::VeinsInetMobility *>(cmod);
        inet::SUMOMobility *sm = check_and_cast<inet::SUMOMobility *>(cmod);

        outfile << "*." << getParentModule()->getParentModule()->getFullName() << ".mobility.InitialX = " << sm->getCurrentPosition().x << "m" << endl;
        outfile.close();
        flagpos = false;
    }
    long packetLength = pk->getByteLength();
    bytesRcvd += packetLength;
    std::cout << getFullPath() << " " << bytesRcvd << endl;


    a = "/home/narisu/src/omnet/omnetpp-5.5.1/samples/new_toyota_FL/examples/federatedlearning/broadcastmodel/re/re";
    b = std::to_string(repeat);
    c = ".txt";
    d = a + b + c;
    fname = d.c_str();
    if(bytesRcvd == par("modelSize").intValue())
    {
        std::cout << simTime() << getFullPath() << " tcp close " << endl;
        outfile.open(fname, std::ios::app);
        outfile << sinkAppModule->getParentModule()->getFullName() << " " << simTime() << endl;
        outfile.close();
    }
    //std::cout << simTime() << " arrived data " << bytesRcvd << endl;
    sinkAppModule->bytesRcvd += packetLength;

    //std::cout << getFullPath() << " received " << sinkAppModule->bytesRcvd << " at time " << simTime() << endl;

    emit(packetReceivedSignal, pk);
    delete pk;
}

void TcpSinkFLThread::refreshDisplay() const
{
    std::ostringstream os;
    os << (sock ? TcpSocket::stateName(sock->getState()) : "NULL_SOCKET") << "\nrcvd: " << bytesRcvd << " bytes";

    getDisplayString().setTagArg("t", 0, os.str().c_str());
}

} // namespace inet

