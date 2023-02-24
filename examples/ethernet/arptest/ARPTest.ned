//
// Copyright (C) 2006 Andras Varga
//
// This library is free software, you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation;
// either version 2 of the License, or any later version.
// The library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//


package inet.examples.ethernet.arptest;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.ethernet.EtherSwitch;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import ned.DatarateChannel;
import inet.node.wireless.AccessPoint;
import inet.physicallayer.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
network ARPTest
{
    types:
        channel fiberline extends DatarateChannel
        {
            delay = 1us;
            datarate = 512Mbps;
        }
        channel ethline extends DatarateChannel
        {
            delay = 50ns;
            datarate = 100Mbps;
        }
    submodules:
        radioMedium: Ieee80211ScalarRadioMedium {
            parameters:
                @display("p=100,200;is=s");
        }
        ap: AccessPoint {
            @display("p=469,292");
        }
        client: StandardHost {
            @display("p=250,100;i=device/laptop");
        }
        host1: StandardHost {
            @display("p=250,200;i=device/pc");
        }
        host2: StandardHost {
            @display("p=250,300;i=device/pc");
        }
        switch: EtherSwitch {
            @display("p=400,200");
        }
        net: Router {
            @display("p=700,200");
        }
        router: Router {
            @display("p=550,200");
        }
        server: StandardHost {
            @display("p=850,200;i=device/server");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=100,100;is=s");
        }
    connections:
        client.ethg++ <--> ethline <--> switch.ethg++;
        switch.ethg++ <--> ethline <--> host1.ethg++;
        switch.ethg++ <--> ethline <--> host2.ethg++;
        router.ethg++ <--> ethline <--> switch.ethg++;
        switch.ethg++ <--> ethline <--> ap.ethg++;
        router.pppg++ <--> fiberline <--> net.pppg++;
        server.pppg++ <--> fiberline <--> net.pppg++;
}

