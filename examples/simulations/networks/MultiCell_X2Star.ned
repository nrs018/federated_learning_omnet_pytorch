// 
//                           SimuLTE
// 
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself, 
// and cannot be removed from it.
// 
package inet.examples.simulations.networks;

import inet.networklayer.ipv4.RoutingTableRecorder;
import inet.node.ethernet.Eth10G;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import lte.corenetwork.binder.LteBinder;
import lte.corenetwork.nodes.eNodeB;
import lte.corenetwork.nodes.Ue;
import lte.corenetwork.nodes.ExtCell;
import lte.epc.PgwStandardSimplified;
import lte.world.radio.LteChannelControl;
import lte.common.LteNetworkConfigurator;


network MultiCell_X2Star
{
    parameters:
        int numUe1 = default(0);
        int numUe2 = default(0);
        int numUe3 = default(0);
        int numExtCells = default(0);
        @display("i=block/network2;bgb=710,558;bgi=background/budapest");
    submodules:
        channelControl: LteChannelControl {
            @display("p=50,25;is=s");
        }
        routingRecorder: RoutingTableRecorder {
            @display("p=50,75;is=s");
        }
        configurator: LteNetworkConfigurator {
            @display("p=50,125");
        }
        binder: LteBinder {
            @display("p=50,175;is=s");
        }
        server: StandardHost {
            @display("p=173,48;is=n;i=device/server");
        }
        pgw: PgwStandardSimplified {
            nodeType = "PGW";
            @display("p=172,287;is=l");
        }
        router1: Router {
            @display("p=251,286;i=device/smallrouter");
        }
        router2: Router {
            @display("p=276,123;i=device/smallrouter");
        }
        router3: Router {
            @display("p=276,469;i=device/smallrouter");
        }
        routerX2: Router {
            @display("p=513,286;i=device/smallrouter");
        }
        eNodeB1: eNodeB {
            @display("p=356,287;is=vl");
        }
        eNodeB2: eNodeB {
            @display("p=578,136;is=vl");
        }
        eNodeB3: eNodeB {
            @display("p=578,454;is=vl");
        }
        ue1[numUe1]: Ue {
            @display("p=425,300");
        }
        ue2[numUe2]: Ue {
            @display("p=571,225");
        }
        ue3[numUe3]: Ue {
            @display("p=513,385");
        }
        extCell[numExtCells]: ExtCell {
            @display("p=100,480;is=vl");
        }
    connections:

        server.pppg++ <--> Eth10G <--> pgw.filterGate;
        pgw.pppg++ <--> Eth10G <--> router1.pppg++;
        pgw.pppg++ <--> Eth10G <--> router2.pppg++;
        pgw.pppg++ <--> Eth10G <--> router3.pppg++;
        router1.pppg++ <--> Eth10G <--> eNodeB1.ppp;
        router2.pppg++ <--> Eth10G <--> eNodeB2.ppp;
        router3.pppg++ <--> Eth10G <--> eNodeB3.ppp;

        //# X2 connections
        eNodeB1.x2++ <--> Eth10G <--> routerX2.pppg++;
        eNodeB2.x2++ <--> Eth10G <--> routerX2.pppg++;
        eNodeB3.x2++ <--> Eth10G <--> routerX2.pppg++;
}
