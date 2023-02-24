// 
//                           SimuLTE
// 
// This file is part of a software released under the license included in file
// "license.pdf". This license can be also found at http://www.ltesimulator.com/
// The above file and the present reference are part of the software itself, 
// and cannot be removed from it.
// 
package inet.examples.federatedlearning.wholeCode;

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
import lte.corenetwork.nodes.*;
import inet.physicallayer*.ieee80211.packetlevel.Ieee80211DimensionalRadioMedium;
import inet.node.wireless.AccessPoint;
import inet.node.inet.WirelessHost;
import inet.node.aodv.AodvRouter;
import inet.physicallayer.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;

//import veins.nodes.Scenario;
//import veins_inet.VeinsInetCar;
import veins_inet.VeinsInetManager;
import inet.visualizer.integrated.IntegratedVisualizer;
import inet.environment.common.PhysicalEnvironment;
import veins.visualizer.roads.RoadsCanvasVisualizer;
import veins.visualizer.roads.RoadsOsgVisualizer;

import veins.modules.mobility.traci.TraCIScenarioManager;
import inet.common.geometry.common.SimpleGeographicCoordinateSystem;
import inet.visualizer.integrated.IntegratedCanvasVisualizer;
import inet.visualizer.roads.SUMORoadsCanvasVisualizer;
import inet.mobility.single.SUMOMap;

network SingleCell
{
    parameters:
        int numClient = default(100);

        @display("i=block/network2;bgb=2000,2000");
    submodules:
        sumomap: SUMOMap;
        SUMORoad: SUMORoadsCanvasVisualizer;
        visualizer: IntegratedVisualizer {
            @display("p=76.05,518.83");
        }

        radioMedium: Ieee80211DimensionalRadioMedium {
            //radioMedium: Ieee80211ScalarRadioMedium {
            @display("p=76.05,59.150005");
        }

        channelControl: LteChannelControl {
            @display("p=74.36001,407.29004;is=s");
        }
        routingRecorder: RoutingTableRecorder {
            @display("p=76.05,312.65002;is=s");
        }
        configurator: LteNetworkConfigurator {
            @display("p=76.05,147.03001;is=s");
        }
        binder: LteBinder {
            @display("p=76.05,226.46002;is=s");
        }
        server: StandardHost {
            @display("p=459.83206,197.07089;is=n;i=device/server");
        }
        router: Router {
            @display("p=654.0469,385.5735;i=device/smallrouter");
        }
//        router1: Router {
//            @display("p=2814.2705,995.19135;i=device/smallrouter");
//        }
//        router2: Router {
//            @display("p=3205.8213,1256.2251;i=device/smallrouter");
//        }
//        router3: Router {
//            @display("p=3523.9563,1386.7421;i=device/smallrouter");
//        }

        pgw: PgwStandardSimplified {
            nodeType = "PGW";
            @display("p=871.1105,117.10009;is=l");
        }

        eNB: eNodeB {
            @display("p=1000,500;is=vl");
        }
//        eNB1: eNodeB {
//            @display("p=1835.3939,2096.4277;is=vl");
//        }
//        eNB2: eNodeB {
//            @display("p=3205.8213,2610.338;is=vl");
//        }
//        eNB3: eNodeB {
//            @display("p=2691.911,3638.1584;is=vl");
//        }

        s: lte_11p {
            @display("p=500,500;i=device/server");
            wlan[*].mgmt.typename = "Ieee80211MgmtAdhoc";
            //wlan[*].mgmt.typename = "Ieee80211MgmtStaSimplified";
            wlan[*].agent.typename = "";
        }

        //        C[numClient]: lte_11p {
        V[numClient]: lte_11p {
            @display("p=251.33679,456.97598;i=device/car");
            wlan[*].mgmt.typename = "Ieee80211MgmtAdhoc";
            //wlan[*].mgmt.typename = "Ieee80211MgmtStaSimplified";
            wlan[*].agent.typename = "";
        }
    connections:
        server.pppg++ <--> Eth10G <--> pgw.filterGate;
        pgw.pppg++ <--> Eth10G <--> router.pppg++;
        //        pgw.pppg++ <--> Eth10G <--> router1.pppg++;
        //        pgw.pppg++ <--> Eth10G <--> router2.pppg++;
        //        pgw.pppg++ <--> Eth10G <--> router3.pppg++;
        //        router0.pppg++ <--> Eth10G <--> eNB0.ppp;
        //        router1.pppg++ <--> Eth10G <--> eNB1.ppp;
        //        router2.pppg++ <--> Eth10G <--> eNB2.ppp;
        //        router3.pppg++ <--> Eth10G <--> eNB3.ppp;
        router.pppg++ <--> Eth10G <--> eNB.ppp;
//        router1.pppg++ <--> Eth10G <--> eNB1.ppp;
//        router2.pppg++ <--> Eth10G <--> eNB2.ppp;
//        router3.pppg++ <--> Eth10G <--> eNB3.ppp;


        //# X2 connections
//        eNB0.x2++ <--> Eth10G <--> eNB1.x2++;
//        eNB0.x2++ <--> Eth10G <--> eNB3.x2++;
//
//        eNB1.x2++ <--> Eth10G <--> eNB0.x2++;
//        eNB1.x2++ <--> Eth10G <--> eNB2.x2++;
//
//        eNB2.x2++ <--> Eth10G <--> eNB1.x2++;
//        eNB2.x2++ <--> Eth10G <--> eNB3.x2++;
//
//        eNB3.x2++ <--> Eth10G <--> eNB0.x2++;
//        eNB3.x2++ <--> Eth10G <--> eNB2.x2++;
//        eNB0.x2++ <--> Eth10G <--> routerX2.pppg++;
//        eNB1.x2++ <--> Eth10G <--> routerX2.pppg++;
//        eNB2.x2++ <--> Eth10G <--> routerX2.pppg++;
//        eNB3.x2++ <--> Eth10G <--> routerX2.pppg++;


}
