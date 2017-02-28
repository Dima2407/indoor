//
// Created by  Oleksiy Grechnyev on 2/2/2017.
//

#include "MyBridge.h"

#include <BeaconSensor.h>

namespace tester {

    void MyBridge::newBeacon(double x, double y, double z, long long hash, double txPower, double damp) {

        // Create a new beacon object
        Sensors::Hardware::Beacon b(hash, damp, txPower);
        Point p;
        p.x = x;
        p.y = y;
        p.z = z;
        b.setPosition(p);
        b.setFilterWinSize(10); // Change if needed

        // Add it to the beacon sensor
        navigator.beacon().addBeacon(b);
    }

}