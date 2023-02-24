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

package inet.applications.tcpapp;

import inet.applications.contract.IApp;

//
// Accepts any number of incoming TCP connections, and discards whatever
// arrives on them. Compatible with both ~Ipv4 and ~Ipv6.
//
module ClientSink extends TcpServerHostApp
{
    parameters:
        int modelSize @unit(B) = default(1B);
        double computationCapability = default(1);
        int round = default(1);
        
        serverThreadModuleType = default("inet.applications.tcpapp.ClientSinkThread");
        @class(ClientSink);
        @display("i=block/sink");
        @statistic[packetReceived](title="packets received"; source=packetReceived; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none; checkSignals=false);
        @statistic[endToEndDelay](title="end-to-end delay"; source="dataAge(packetReceived)"; unit=s; record=histogram,weightedHistogram,vector; interpolationmode=none; checkSignals=false);
}

simple ClientSinkThread
{
    parameters:
        int modelSize @unit(B) = default(1B);
        int round = default(1);
        double alpha0 = default(1); // sample quantity
        double alpha1 = default(1); // time for received model
        double alpha2 = default(1); // delta Loss
        double alpha3 = default(1); // computational capality
        
        @display("i=block/sink");
        @signal[packetReceived](type=inet::Packet);
        @statistic[packetReceived](title="packets received"; source=packetReceived; record=count,"sum(packetBytes)","vector(packetBytes)"; interpolationmode=none);
        @statistic[endToEndDelay](title="end-to-end delay"; source="dataAge(packetReceived)"; unit=s; record=histogram,weightedHistogram,vector; interpolationmode=none);
}

