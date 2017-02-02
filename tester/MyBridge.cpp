//
// Created by  Oleksiy Grechnyev on 2/2/2017.
//

#include "MyBridge.h"

#include <navigator.h>

namespace tester{
    void MyBridge::init() {
        Navigator::instance()->beacon().clear();
    }

    void MyBridge::newBeacon(long long hash, double txPower, double damp, double x, double y, double z) {

        // Create a new beacon object
        Sensors::Hardware::Beacon b(hash, damp, txPower);
        Point p;
        p.x = x;
        p.y = y;
        p.z = z;
        b.setPosition(p);
        b.setFilterWinSize(10);

        // Add it to the beacon sensor
        Navigator::instance()->beacon().addBeacon(b);
    }

    void MyBridge::newBeacon(MyBeacon &beacon) {
        newBeacon(beacon.hash, beacon.txPower, beacon.damp, beacon.x, beacon.y, beacon.z);
    }

    void MyBridge::newMeasurement(long long hash, double txPower, double rssi, long long timestamp) {
        Navigator::instance()->addBeaconMeasurement(hash, txPower, rssi,
                                                    timestamp);
    }

    double MyBridge::getX() {
        return Navigator::instance()->beacon().lastState().position().x;
    }

    double MyBridge::getY() {
        return Navigator::instance()->beacon().lastState().position().y;
    }

    double MyBridge::getZ() {
        return Navigator::instance()->beacon().lastState().position().z;
    }
}