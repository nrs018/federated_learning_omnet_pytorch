//
//                           SimuLTE
//
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself,
// and cannot be removed from it.
//

#include <omnetpp.h>
#include <inet/networklayer/common/L3AddressResolver.h>
#include <inet/transportlayer/sctp/SctpAssociation.h>
#include "lte/x2/X2AppClient.h"

#include <inet/transportlayer/contract/sctp/SctpCommand_m.h>
#include "lte/corenetwork/binder/LteBinder.h"
#include "lte/stack/mac/layer/LteMacEnb.h"


Define_Module(X2AppClient);

using namespace omnetpp;
using namespace inet;


void X2AppClient::initialize(int stage)
{
    SctpClient::initialize(stage);
    if (stage==inet::INITSTAGE_LOCAL)
    {
        x2ManagerOut_ = gate("x2ManagerOut");
    }
    else if (stage==inet::INITSTAGE_APPLICATION_LAYER)
    {
        // TODO set the connect address
        // Automatic configuration not yet supported. Use the .ini file to set IP addresses

        // get the connectAddress and the corresponding X2 id
        L3Address addr = L3AddressResolver().resolve(par("connectAddress").stringValue());
        X2NodeId peerId = getBinder()->getX2NodeId(addr.toIpv4());

        X2NodeId nodeId = check_and_cast<LteMacEnb*>(getParentModule()->getParentModule()->getSubmodule("lteNic")->getSubmodule("mac"))->getMacCellId();
        getBinder()->setX2PeerAddress(nodeId, peerId, addr);

        // set the connect port
        int connectPort = getBinder()->getX2Port(peerId);
        par("connectPort").setIntValue(connectPort);
    }
}

void X2AppClient::socketEstablished(inet::SctpSocket *socket, unsigned long int buffer)
{
    EV << "X2AppClient: connected\n";
}

void X2AppClient::socketDataArrived(SctpSocket *, Packet *msg, bool)
{
    packetsRcvd++;

    EV << "X2AppClient::socketDataArrived - Client received packet Nr " << packetsRcvd << " from Sctp\n";
    emit(packetReceivedSignal, msg);
    bytesRcvd += msg->getByteLength();

    msg->removeTagIfPresent<SctpSendReq>();

    if (msg->getDataLength() > B(0))
    {
        EV << "X2AppClient::socketDataArrived - Forwarding packet to the X2 manager" << endl;

        // forward to x2manager
        send(msg, x2ManagerOut_);
    }
    else
    {
        EV << "X2AppClient::socketDataArrived - No encapsulated message. Discard." << endl;

        throw cRuntimeError("X2AppClient::socketDataArrived: No encapsulated message.");

        delete msg;
    }
}


