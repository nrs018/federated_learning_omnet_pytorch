// 
//                           SimuLTE
// 
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself, 
// and cannot be removed from it.
// 
package inet.examples.federatedlearning.uploadingmodel;

import inet.networklayer.ipv4.RoutingTableRecorder;
import inet.node.ethernet.Eth10G;
import inet.node.ethernet.Eth10M;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import lte.corenetwork.binder.LteBinder;
import lte.corenetwork.nodes.Ue;
import lte.corenetwork.nodes.eNodeB;
import lte.world.radio.LteChannelControl;
import lte.epc.PgwStandardSimplified;
import lte.common.LteNetworkConfigurator;

import lte.corenetwork.nodes.lte_11p;
import inet.physicallayer*.ieee80211.packetlevel.Ieee80211DimensionalRadioMedium;
import inet.node.wireless.AccessPoint;
import inet.node.inet.WirelessHost;
import inet.node.aodv.AodvRouter;
import inet.physicallayer.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;

network SingleCell
{
    parameters:
        int numUe = default(215);

        @display("i=block/network2;bgb=4990,100;");
    submodules:
        channelControl: LteChannelControl {
            @display("p=75.86875,33.58125;is=s");
        }
        routingRecorder: RoutingTableRecorder {
            @display("p=145.51875,33.58125;is=s");
        }
        configurator: LteNetworkConfigurator {
            @display("p=217.65625,33.58125;is=s");
        }
        binder: LteBinder {
            @display("p=300.9875,33.58125;is=s");
        }
        server: StandardHost {
            @display("p=698.9875,22.3875;is=n;i=device/server");
        }
        router: Router {
            @display("p=963.90625,21.14375;i=device/smallrouter");
        }
        pgw: PgwStandardSimplified {
            nodeType = "PGW";
            @display("p=1126.8375,22.3875;is=l");
        }

        //radioMedium: Ieee80211DimensionalRadioMedium {
        radioMedium: Ieee80211ScalarRadioMedium {
            @display("p=400.4875,32.3375");
        }


        eNB: eNodeB {
            @display("p=1315.8875,0;is=vl");
        }
        s: Ue{//lte_11p {
            @display("p=1074.6,90.79375");
            wlan[*].mgmt.typename = "Ieee80211MgmtAdhoc";
            //wlan[*].mgmt.typename = "Ieee80211MgmtStaSimplified";
            wlan[*].agent.typename = "";
        }

        C[numUe]: Ue {
            @display("p=1216.3875,42.2875;i=veins/node/car;is=vs");
        }
    connections:
        server.pppg++ <--> Eth10G <--> router.pppg++;
        router.pppg++ <--> Eth10G <--> pgw.filterGate;
        pgw.pppg++ <--> Eth10G <--> eNB.ppp;
}
