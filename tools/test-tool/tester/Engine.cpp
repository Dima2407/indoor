//
// Created by  Oleksiy Grechnyev on 2/4/2017.
//

#include "Engine.h"
#include "MyBridge.h"

#include <cassert>
#include <iostream>

namespace tester {

    void Engine::readData() {
        using namespace std;

        // Read config
        testerConnfig.readJSON("in_testerconfig.json");

        // Read beacons from a DAT or JSON file
        assert(beaconList.readAuto(testerConnfig.getInBeaconsFile()));

        //  Check that there are at least 3 beacons
        if (beaconList.getBeacons().size() < 3) {
            cerr << "WARNING: Need at least 3 beacons !" << endl;
            //exit(1);
        }

        // Read events
        assert(eventList.readDAT(testerConnfig.getInEventsFile()));
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