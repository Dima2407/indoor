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

    // used this config for correct on "map" before arraive result into filter
    config.useMeshMask = false;
    config.useMapEdges = true;
    KalmanConfig filterConfig;

    shared_ptr<KalmanBeaconNavigator> navigator = make_shared<KalmanBeaconNavigator>(mesh1, config, filterConfig);

    const Beacon beacons[] = {
        Beacon(BeaconUID("Guinea Pig", 1, 0), -30.0, 2.0, Position3D(0.6, 0.2, 0.0), ""),
        Beacon(BeaconUID("Guinea Pig", 1, 1), -35.0, 2.5, Position3D(9.8, 0.3, 0.0), ""),
        Beacon(BeaconUID("Guinea Pig", 1, 2), -40.0, 3.0, Position3D(-0.1, 10.4, 0.0), ""),
        Beacon(BeaconUID("Guinea Pig", 1, 3), -45.0, 2.4, Position3D(9.9, 10.1, 0.0), "")
    };

    navigator->addBeacons(beacons);

    // ------------------------------------------------------------------------------

    KalmanXYBeaconNavigator beaconNavigator(navigator, mesh1);
    // used this config for correct on "mesh" after execute result in filter
    beaconNavigator.setUseMapEdges(true);
    beaconNavigator.setUseMeshMask(true);

    // ------------------------------------------------------------------------------

    vector<BeaconReceivedData> brds;
    double timeStamp = 1.7;
    Position3D inPos(2.31, 6.95, 0.0);

    for (int i = 0; i < 4; i++) {
        const Beacon &b = beacons[i];
        double rssi = fakeRSSI(inPos, b.getPos(), b.getTxPower(), b.getDamp());
        BeaconUID uid = BeaconUID("Guinea Pig", 1, i);
        brds.push_back(BeaconReceivedData(timeStamp, uid, rssi));
    }

    Position3D outPos = beaconNavigator.process(brds);
    cout << "  x  \t  y  \t  z  " << endl;
    cout << outPos.x << "\t" << outPos.y << "\t" << outPos.z << endl;


    // ------------------------------------------------------------------------------

    brds.clear();

    timeStamp = 6.69;
    inPos = Position3D(3.1415, 0.1234, 0.0);
    for (int i = 0; i < 4; i++) {
        const Beacon &b = beacons[i];
        double rssi = fakeRSSI(inPos, b.getPos(), b.getTxPower(), b.getDamp());
        BeaconUID uid = BeaconUID("Guinea Pig", 1, i);
        if (i != 2)
            brds.push_back(BeaconReceivedData(timeStamp, uid, rssi));
    }
    outPos = beaconNavigator.process(brds);
    cout << "  x  \t  y  \t  z  " << endl;
    cout << outPos.x << "\t" << outPos.y << "\t" << outPos.z << endl;

    // ------------------------------------------------------------------------------

    brds.clear();

    timeStamp = 8.33;
    inPos = Position3D(7.9451, 4.8172, 0.0);
    for (int i = 0; i < 4; i++) {
        const Beacon &b = beacons[i];
        double rssi = fakeRSSI(inPos, b.getPos(), b.getTxPower(), b.getDamp());
        BeaconUID uid = BeaconUID("Guinea Pig", 1, i);
        if (i != 2)
            brds.push_back(BeaconReceivedData(timeStamp, uid, rssi));
    }
    outPos = beaconNavigator.process(brds);
    cout << "  x  \t  y  \t  z  " << endl;
    cout << outPos.x << "\t" << outPos.y << "\t" << outPos.z << endl;

    // ------------------------------------------------------------------------------


    return 0;
}
