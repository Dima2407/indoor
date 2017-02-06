//
// Created by  Oleksiy Grechnyev on 2/3/2017.
//

#include "FakeEngine.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cassert>

namespace faker {

    void FakeEngine::readBeacons() {
        using namespace std;
        using namespace tester;

        const char *fileName = "in_beacons.dat";

        // Read beacons from input file
        assert(beaconList.readDAT(fileName));

        //  Check that there are at least 3 beacons
        if (beaconList.getBeacons().size() < 3) {
            cerr << "ERROR: Need at least 3 beacons !" << endl;
            exit(1);
        }
    }

    void FakeEngine::readInput() {
        using namespace std;
        using namespace tester;

        // Open file
        const char *fileName = "in_faker.dat";
        ifstream in(fileName);
        if (!in) {
            cerr << "ERROR: Cannot open input file : " << fileName << endl;
            exit(1);
        }

        // Read the data
        cout << endl << "Reading configuration :" << endl << endl;

        in >> t1 >> t2 >> ticksPerTimeUnit;
        cout << "t1 = " << t1 << ", t2 = " << t2 << ", ticksPerTimeUnit = " << ticksPerTimeUnit << endl;

        in >> point1 >> point2;
        cout << "point1 = " << point1 << endl;
        cout << "point2 = " << point2 << endl;

        if (!in) {
            cerr << "ERROR: Corrupt file : " << fileName << endl;
            exit(1);
        }

        // Read beaconTimes
        cout << endl << "Reading beacon time data :" << endl << endl;

        BeaconTime bt;

        beaconTimes.clear(); // Just in case
        while (in >> bt) {
            beaconTimes.push_back(bt); // Add to list
            cout << bt << endl;
        }

        //  Check that there are at least 3 beacons in beaconTimes
        if (beaconTimes.size() < 3) {
            cerr << "ERROR: Need time data for at least 3 beacons in !" << endl;
            exit(1);
        }

        in.close();
    }


    tester::Vec3 FakeEngine::trajectory(double t) {
        // Linear at present
        return point1 * ((t2 - t) / (t2 - t1)) + point2 * ((t - t1) / (t2 - t1));
    }

    void FakeEngine::run() {
        using namespace std;
        using namespace tester;

        eventList.clear(); // Just in case
        // Create events for each beacon in beaconTimes
        for (BeaconTime const &bt: beaconTimes) {
            // Do nothing if wrong hash
            if (beaconList.beaconExists(bt.getHash())) {
                // Find the beacon by hash
                const MyBeacon &b = beaconList.findBeacon(bt.getHash());

                cout << "b.hash = " << b.hash << endl;

                // Create events (fake measurements) for this beacon
                createEvents(b, bt);

            } else {
                cout << "Warning ! Cannot find beacon with hash = " << bt.getHash() << endl;
            }
        }

        // Sort the list of events by timestamp
        eventList.sort();
    }

    void FakeEngine::createEvents(const tester::MyBeacon &beacon, const BeaconTime &beaconTime) {
        using namespace std;
        using namespace tester;

        // Find start and end times (ooverlap of global and beacon range)
        double startTime = max(beaconTime.getT1(), t1);
        double endTime = min(beaconTime.getT2(), t2);

        for (double time = startTime; time < endTime; time += beaconTime.getPeriod()) {
            // Find a trajectory point
            Vec3 point = trajectory(time);
            // Create a fake rssi for this point
            double rssi = beacon.calcRssiPos(point.x, point.y, point.z);

            // Create a new event, while converting time to timestamp
            eventList.getEvents().push_back(Event(beacon.hash, beacon.txPower, rssi, (long long)(time*ticksPerTimeUnit)));
        }
    }

    void FakeEngine::writeResults() {
        assert(eventList.writeDAT("out_measure.dat"));
    }

}