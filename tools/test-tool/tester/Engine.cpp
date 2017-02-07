//
// Created by  Oleksiy Grechnyev on 2/4/2017.
//

#include "Engine.h"
#include "MyBridge.h"

#include <cassert>
#include <iostream>

namespace tester {

    void Engine::readBeacons() {
        using namespace std;


        // Read beacons from a DAT file
        assert(beaconList.readAuto("in_beacons.json"));
        //cout << "result =" << beaconList.readAuto("in_beacons.json") << endl;

        //exit(0);

        //  Check that there are at least 3 beacons
        if (beaconList.getBeacons().size() < 3) {
            cerr << "ERROR: Need at least 3 beacons !" << endl;
            exit(1);
        }

    }

    void Engine::readEvents() {
        using namespace std;

        const char *fileName = "out_measure.dat";

        assert(eventList.readDAT(fileName));
    }

    void Engine::run() {
        using namespace std;

        // Send beacons to the bridge
        MyBridge::init();
        for (MyBeacon const & b: beaconList.getBeacons()) MyBridge::newBeacon(b);

        // Send measurements to the bridge and get XYZ after each measurements

        vec3List.clear(); // Just in case
        for (Event const & e: eventList.getEvents()) {
            MyBridge::newMeasurement(e.hash, e.txPower, e.rssi, e.timestamp);
            // Store position after each measurement
            vec3List.getPoints().push_back(Vec3(MyBridge::getX(), MyBridge::getY(), MyBridge::getZ()));
        }

    }

    void Engine::writeData() {
        vec3List.writeDAT("out_xyz.dat");
    }


}