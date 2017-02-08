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


    void Engine::runLocation() {
        using namespace std;

        // Send beacons to the bridge
        MyBridge::init();
        for (MyBeacon const &b: beaconList.getBeacons()) MyBridge::newBeacon(b);

        // Timestamp of the 1st event
        timeOrigin = eventList.getEvents()[0].timestamp;

        // Send measurements to the bridge and get XYZ after each measurements

        txyzActual.clear(); // Just in case

        // Loop over all events
        for (int i = 0; i < eventList.getEvents().size(); i++) {

            Event const &e = eventList.getEvents()[i]; // Event # i

            MyBridge::newMeasurement(e.hash, e.txPower, e.rssi, e.timestamp);

            // Store time, position after each measurement
            // skiping first skipEvents ones
            // That's why we need i here, and not a for each loop
            if (i >= testerConnfig.getSkipEvents()) {
                // Time, starting from 0.0, in arbitrary time units given by ticks (e.g. seconds)
                double t = (e.timestamp - timeOrigin) / testerConnfig.getTicks();

                txyzActual.getPoints().push_back(Vec3t(t, MyBridge::getX(), MyBridge::getY(), MyBridge::getZ()));
            }
        }

    }


    void Engine::runDelta() {

    }


    void Engine::writeData() {
        txyzActual.writeDAT("out_txyz_actual.dat");
    }


}