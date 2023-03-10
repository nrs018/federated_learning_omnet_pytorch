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
import lte.world.radio.ChannelControl;
import lte.corenetwork.binder.LteBinder;
import lte.corenetwork.nodes.*;
import lte.corenetwork.nodes.eNodeB;
import lte.world.radio.LteChannelControl;
import lte.epc.PgwStandardSimplified;
import lte.apps.d2dMultihop.eventGenerator.EventGenerator;
import lte.apps.d2dMultihop.statistics.MultihopD2DStatistics;
import lte.common.LteNetworkConfigurator;
import inet.physicallayer*.ieee80211.packetlevel.Ieee80211DimensionalRadioMedium;

network MultiCell_D2DMultihop
{
    parameters:
        int numUe1 = default(1);
        int numUe2 = default(1);
        int numUe3 = default(1);
        int numUe4 = default(1);
        int numUe5 = default(1);
        @display("i=block/network2;bgb=2000,500;");
    submodules:
        radioMedium: Ieee80211DimensionalRadioMedium {
            //radioMedium: Ieee80211ScalarRadioMedium {
            @display("p=60.94375,24.875");
        }
        channelControl: LteChannelControl {
            @display("p=89.55,24.875;is=s");
        }
        routingRecorder: RoutingTableRecorder {
            @display("p=90.79375,70.89375;is=s");
        }
        configurator: LteNetworkConfigurator {
            @display("p=90.79375,121.8875");
        }
        binder: LteBinder {
            @display("p=90.79375,171.6375;is=s");
        }
        server: StandardHost {
            @display("p=500,50;is=n;i=device/server");
        }
        router: Router {
            @display("p=750,50;i=device/smallrouter");
        }
        router1: Router {
            @display("p=199,194.025;i=device/smallrouter");
        }
        router2: Router {
            @display("p=599.4875,194.025;i=device/smallrouter");
        }
        router3: Router {
            @display("p=999.975,194.025;i=device/smallrouter");
        }
        router4: Router {
            @display("p=1399.2188,194.025;i=device/smallrouter");
        }
        router5: Router {
            @display("p=1799.7062,194.025;i=device/smallrouter");
        }
        pgw: PgwStandardSimplified {
            nodeType = "PGW";
            @display("p=1000,50;is=l");
        }
        eNodeB1: eNodeB {
            @display("p=200,400;is=vl");
        }
        eNodeB2: eNodeB {
            @display("p=600,400;is=vl");
        }
        eNodeB3: eNodeB {
            @display("p=1000,400;is=vl");
        }
        eNodeB4: eNodeB {
            @display("p=1400,400;is=vl");
        }
        eNodeB5: eNodeB {
            @display("p=1800,400;is=vl");
        }
        ue1[numUe1]: lte_11p {
            @display("p=300,450;is=s");
        }
        ue2[numUe2]: lte_11p {
            @display("p=700,450;is=s");
        }
        ue3[numUe3]: lte_11p {
            @display("p=1100,450;is=s");
        }
        ue4[numUe4]: lte_11p {
            @display("p=1500,450;is=s");
        }
        ue5[numUe5]: lte_11p {
            @display("p=1900,450;is=s");
        }
        eventGenerator: EventGenerator {
            @display("p=90.79375,222.63124;is=s");
        }
        d2dMultihopStatistics: MultihopD2DStatistics {
            @display("p=90.79375,272.38126;is=s");
        }
    connections:
        router1.pppg++ <--> Eth10G <--> eNodeB1.ppp;
        router2.pppg++ <--> Eth10G <--> eNodeB2.ppp;
        router3.pppg++ <--> Eth10G <--> eNodeB3.ppp;
        router4.pppg++ <--> Eth10G <--> eNodeB4.ppp;
        router5.pppg++ <--> Eth10G <--> eNodeB5.ppp;
        router1.pppg++ <--> Eth10G <--> pgw.pppg++;
        router2.pppg++ <--> Eth10G <--> pgw.pppg++;
        router3.pppg++ <--> Eth10G <--> pgw.pppg++;
        router4.pppg++ <--> Eth10G <--> pgw.pppg++;
        router5.pppg++ <--> Eth10G <--> pgw.pppg++;
        router.pppg++ <--> Eth10G <--> pgw.filterGate;
        server.pppg++ <--> Eth10G <--> router.pppg++;
}
