//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package inet.examples.sctp.sctpwifi;


import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import inet.node.inet.WirelessHost;
import ned.DatarateChannel;
import inet.physicallayer.common.packetlevel.RadioMedium;
import inet.node.wireless.AccessPoint;
import inet.visualizer.contract.IIntegratedVisualizer;
import inet.node.ethernet.Eth1G;

network X1
{
    parameters:
        double testTimeout @unit(s) = default(0s);
        bool testing = default(false);

    submodules:
        sctp_client: StandardHost {
            parameters:
                forwarding = false;
                @display("p=172,186;i=device/laptop");
            gates:
                ethg[2];
        }
        configurator: Ipv4NetworkConfigurator {
            addStaticRoutes = false;
            @display("p=100,100;is=s");
        }
        accessPoint: AccessPoint {
            @display("p=460,99");
        }
        radioMedium: RadioMedium {
            @display("p=100,175");
        }
        sctp_server: WirelessHost {
            @display("p=567,176");
           numWlanInterfaces = 2;
        }
        router: Router {
            @display("p=293,186");
            multicastForwarding = true;
            gates:
                ethg[4];
        }
        visualizer: <default("IntegratedCanvasVisualizer")> like IIntegratedVisualizer if hasVisualizer() {
            parameters:
                @display("p=100,260;is=s");
        }
        accessPoint1: AccessPoint {
            @display("p=460,255");
        }
    connections:


        sctp_client.ethg[0] <--> Eth1G <--> router.ethg[0];
        sctp_client.ethg[1] <--> Eth1G <--> router.ethg[1];
        router.ethg[2] <--> Eth1G <--> accessPoint.ethg++;
        router.ethg[3] <--> Eth1G <--> accessPoint1.ethg++;
}



