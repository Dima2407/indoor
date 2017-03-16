//
// Created by  Oleksiy Grechnyev on 2/2/2017.
//

#include "MyBridge.h"


namespace tester {

    void MyBridge::newBeacon(double x, double y, double z, long long hash, double txPower, double damp) {

        using namespace Navigator::Beacons;
        using namespace Navigator::Math;

        // Create a new beacon object of NavigatorLib and add it
        navigator.addBeacon(Beacon(BeaconUID(hash), txPower, damp, Position3D(x, y, z), ""));
    }

}