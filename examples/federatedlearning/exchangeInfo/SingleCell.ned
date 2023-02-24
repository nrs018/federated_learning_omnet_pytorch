// 
//                           SimuLTE
// 
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself, 
// and cannot be removed from it.
// 
package inet.examples.federatedlearning.exchangeInfo;

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
        int numUe = default(1);
        @display("i=block/network2;bgb=4990,100;");
    submodules:
        channelControl: LteChannelControl {
            @display("p=148.00626,26.11875;is=s");
        }
        routingRecorder: RoutingTableRecorder {
            @display("p=271.1375,26.11875;is=s");
        }
        configurator: LteNetworkConfigurator {
            @display("p=361.93124,26.11875;is=s");
        }


        radioMedium: Ieee80211DimensionalRadioMedium {
            //radioMedium: Ieee80211ScalarRadioMedium {
            @display("p=60.94375,24.875");
        }

        C[numUe]: WirelessHost {
            @display("p=621.875,73.38125;i=veins/node/car;is=vs");
            wlan[*].mgmt.typename = "Ieee80211MgmtAdhoc";
         	//wlan[*].mgmt.typename = "Ieee80211MgmtStaSimplified";
            wlan[*].agent.typename = "";
        }

    connections:
}
