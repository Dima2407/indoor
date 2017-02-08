//
// Created by  Oleksiy Grechnyev on 2/4/2017.
//

#include "Engine.h"
#include "MyBridge.h"

#include <cassert>
#include <iostream>
#include <fstream>
#include <iomanip>

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
        assert(eventList.readAuto(testerConnfig.getInEventsFile()));
    }


    void Engine::runLocation() {
        using namespace std;

        // Send beacons to the bridge
        MyBridge::init();
        for (MyBeacon const &b: beaconList.getBeacons()) MyBridge::newBeacon(b);

        // Timestamp of the 1st event
        timeOrigin = eventList.getEvents()[0].timestamp;

        // Set t1 and t2 for the trajectoty
        testerConnfig.getTrajectory().t1 = 0;
        // t2 is the last timestamp, converted
        testerConnfig.getTrajectory().t2 = stamp2Time(eventList.getEvents().back().timestamp);

        // Send measurements to the bridge and get XYZ after each measurements

        txyzActual.clear(); // Just in case

        // Loop over all events
        for (int i = 0; i < eventList.getEvents().size(); i++) {

            Event const &e = eventList.getEvents()[i]; // Event # i

            if (!beaconList.beaconExists(e.hash)) {
                cerr << "Warning: Event for non-existent beacon, hash = " << e.hash << endl;
            }

            MyBridge::newMeasurement(e.hash, e.txPower, e.rssi, e.timestamp);

            // Store time, position after each measurement
            // skiping first skipEvents ones
            // That's why we need i here, and not a for each loop
            if (i >= testerConnfig.getSkipEvents()) {
                // Time, starting from 0.0, in arbitrary time units given by ticks (e.g. seconds)
                double t = stamp2Time(e.timestamp);

                txyzActual.getPoints().push_back(Vec3t(t, MyBridge::getX(), MyBridge::getY(), MyBridge::getZ()));
            }
        }

    }


    void Engine::runDelta() {
        double sumDelta2=0; // Sum of all delta^2 for averaging

        maxDelta=0;

        txyzExpected.clear();  // Just in case
        txyzDelta.clear();
        tDelta.clear();

        // Loop over all actual txyz points
        for (Vec3t const & vat: txyzActual.getPoints()) {

            double t = vat.t; // Time
            // Expected trajectory point
            Vec3 ve = testerConnfig.getTrajectory().trajectory(t);
            // Vector delta
            Vec3 vd =  vat.r - ve;
            // Scalar delta
            double d = vd.len();

            sumDelta2 += d*d; // Do the sum

            if (d > maxDelta) maxDelta = d;

            // Store data
            txyzExpected.getPoints().push_back(Vec3t(t, ve));
            txyzDelta.getPoints().push_back(Vec3t(t, vd));
            tDelta.push_back(DoublePair(t, d));
        }

        // Calculate square averaged delta
        averageDelta = sqrt(sumDelta2 / txyzActual.getPoints().size());

    }


    void Engine::writeData() {
        using namespace std;

        txyzActual.writeDAT("out_txyz_actual.dat");
        txyzExpected.writeDAT("out_txyz_expected.dat");
        txyzDelta.writeDAT("out_txyz_delta.dat");

        // Write scalar delta
        ofstream out("out_tdelta.dat");
        for (DoublePair const & dp: tDelta) {
            out << fixed << setw(12) << dp.t  << setw(12) << dp.v << endl;
        }
        out.close();

        cout << "Max delta = " << maxDelta << endl;
        cout << "Avg delta = " << averageDelta << endl;
    }


}