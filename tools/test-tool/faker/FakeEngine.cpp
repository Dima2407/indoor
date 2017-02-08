//
// Created by  Oleksiy Grechnyev on 2/3/2017.
//

#include "FakeEngine.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <cassert>

namespace faker {

    void FakeEngine::readData() {
        using namespace std;
        using namespace tester;

        // Read configuration
        assert(fakerConfig.readJSON("in_fakerconfig.json"));

        // Read beacons from input file (dat or json)
        assert(beaconList.readAuto(fakerConfig.getInBeaconsFile()));

        //  Check that there are at least 3 beacons
        if (beaconList.getBeacons().size() < 3) {
            cerr << "WARNING: Need at least 3 beacons for normal operation." << endl;
            // exit(1);
        }

        // Read beacon times
        assert(beaconTimeList.readAuto(fakerConfig.getInTimesFile()));
    }


    void FakeEngine::run() {
        using namespace std;
        using namespace tester;

        eventList.clear(); // Just in case
        // Create events for each beacon in beaconTimes
        for (BeaconTime const &bt: beaconTimeList.getBeaconTimes()) {
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


        LinearTrajectory const &traj = fakerConfig.getTrajectory();

        // Find start and end times (ooverlap of global and beacon range)
        double startTime = max(beaconTime.getT1(), traj.t1);
        double endTime = min(beaconTime.getT2(), traj.t2);

        for (double time = startTime; time < endTime; time += beaconTime.getPeriod()) {
            // Find a trajectory point
            Vec3 point = traj.trajectory(time);
            // Create a fake rssi for this point
            double rssi = beacon.calcRssiPos(point.x, point.y, point.z);

            // Create a new event, while converting time to timestamp
            eventList.getEvents().push_back(Event(beacon.hash, beacon.txPower, rssi,
                                                  (long long) (time * fakerConfig.getTicks())));
        }
    }

    void FakeEngine::writeResults() {
        assert(eventList.writeAuto(fakerConfig.getOutEventsFile()));
    }

}