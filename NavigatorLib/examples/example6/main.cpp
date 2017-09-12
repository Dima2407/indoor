//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>

// This includes everything you need
#include "Navigator.h"
#include "Navigator/Beacons/KalmanXYNavigator.h"

// There are a few namespaces in the librrary
using namespace std;
using namespace Navigator::Beacons;
using namespace Navigator::Beacons::Factory;
using namespace Navigator::Math::Trilat;
using namespace Navigator::Math::Kalman;
using namespace Navigator::Mesh;
using Navigator::Math::Position3D;


int main() {
    cout << "EXAMPLE 6 \n";

    // ------------------------------------------------------------------------------

    auto mesh1 = make_shared<RectanMesh>("in/mesh.in", "in/masktable.out");
    KalmanBeaconNavigatorConfig config;
    KalmanConfig filterConfig;

    shared_ptr<KalmanBeaconNavigator> nav = make_shared<KalmanBeaconNavigator>(mesh1, config, filterConfig);

    // ------------------------------------------------------------------------------

    KalmanXYBeaconNavigator beaconNavigator(nav, mesh1);
    beaconNavigator.setUseMapEdges(true);
    beaconNavigator.setUseMeshMask(true);


    // ------------------------------------------------------------------------------

    const Beacon beacons[] = {
        Beacon(BeaconUID("Guinea Pig", 1, 0), -30.0, 2.0, Position3D(0.6, 0.2, 0.0), ""),
        Beacon(BeaconUID("Guinea Pig", 1, 1), -35.0, 2.5, Position3D(9.8, 0.3, 0.0), ""),
        Beacon(BeaconUID("Guinea Pig", 1, 2), -40.0, 3.0, Position3D(-0.1, 10.4, 0.0), ""),
        Beacon(BeaconUID("Guinea Pig", 1, 3), -45.0, 2.4, Position3D(9.9, 10.1, 0.0), "")
    };

    vector<Beacon> vec(beacons, beacons + 4);

    /* Add beacons: to the navigator
     *
     * You can add them one by one, or as an array/container
     * /
     *
    /*for (const Beacon &b : beacons)
        navigator.addBeacon(b);*/
//    navigator.addBeacons(beacons);

    /* 3) Create and process events
     * For the example, I generate fake events for a point inPos
     * In real life, you receive events (timestamp, beacon uid, rssi) from you device
     * And send them to the navigator
     */
//    Position3D inPos(2.31, 6.95, 0.0); // Some given position


    // Create a vector of packets which share the same timestamp
//    vector<BeaconReceivedData> brds;

//    double timeStamp = 1.7;

//    for (int i = 0; i < 4; i++) {

        /* For the example, I create a fake RSSI for each beacon
         * In real life you get rssi from your mobile device
         */
//        const Beacon &b = beacons[i];
//        double rssi = fakeRSSI(inPos, b.getPos(), b.getTxPower(), b.getDamp());

        /* Create UID for the data packet
         * It must correctly identify one of the beacons addded to the navigator before
         */
//        BeaconUID uid = BeaconUID("Guinea Pig", 1, i);

        // Create a data packet for our data
//        brds.push_back(BeaconReceivedData(timeStamp, uid, rssi));
//    }

    // Process the whole bunch of data in a single process() call
//    Position3D outPos = navigator.process(brds);

//    // Write it to stdout
//    cout << "  x  \t  y  \t  z  " << endl;

//    cout << outPos.x << "\t" << outPos.y << "\t" << outPos.z << endl;

//    // Try findProcessorByUid, useful for debugging
//    auto processor = navigator.findProcessorByUid(BeaconUID("Guinea Pig", 1, 2));
//    if (processor == nullptr) {
//        cout << "Beacon Processor not found !!! " << endl;
//    } else {
//        cout << "Last distance = " << processor -> getLastDistance() << endl;
//        cout << "Last timestamp = " << processor -> getLastTimeStamp() << endl;
//    }

//    // If you want to remove a beacon
//    // navigator.deleteBeacon(BeaconUID("Guinea Pig", 1, 2));

//    // Or remove all beacons
//    // navigator.clear();

//    // Process another packet
//    brds.clear();
//    timeStamp = 6.69; // < 5 seconds
////    timeStamp = 6.71; // > 5 seconds
//    inPos = Position3D(3.1415, 0.1234, 0.0);
//    for (int i = 0; i < 4; i++) {
//        const Beacon &b = beacons[i];
//        double rssi = fakeRSSI(inPos, b.getPos(), b.getTxPower(), b.getDamp());
//        BeaconUID uid = BeaconUID("Guinea Pig", 1, i);
//        // Skip beacon 2, but Kalman Filter will re-create the packet unless 5 seconds have passed
//        if (i != 2)
//            brds.push_back(BeaconReceivedData(timeStamp, uid, rssi));
//    }
//    outPos = navigator.process(brds);
//    cout << "  x  \t  y  \t  z  " << endl;
//    cout << outPos.x << "\t" << outPos.y << "\t" << outPos.z << endl;

//    processor = navigator.findProcessorByUid(BeaconUID("Guinea Pig", 1, 2));
//    if (processor == nullptr) {
//        cout << "Beacon Processor not found !!! " << endl;
//    } else {
//        cout << "Last distance = " << processor -> getLastDistance() << endl;
//        cout << "Last timestamp = " << processor -> getLastTimeStamp() << endl;
//    }

    return 0;
}
