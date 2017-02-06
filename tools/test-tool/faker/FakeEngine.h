//
// Created by  Oleksiy Grechnyev on 2/3/2017.
//

#ifndef TESTERALL_FAKEENGINE_H
#define TESTERALL_FAKEENGINE_H

#include <vector>
#include <cstdlib>
#include <EventList.h>

#include "MyBeacon.h"
#include "Vec3.h"
#include "BeaconTime.h"
#include "Event.h"
#include "MyBeaconList.h"

namespace faker {

    /// Main class of faker
    class FakeEngine {


    public:
        /////////////////////////

        /// Read beacons from file in_beacons.dat
        void readBeacons();

        /// Read faker input file in_faker.dat
        void readInput();

        /// Calculate trajectory Vec3(t), linear at present
        tester::Vec3 trajectory(double t);

        /// Do the actual calculation
        void run();

        /// Create events for a given MyBeacon and BeaconTime
        void createEvents(const tester::MyBeacon & beacon, const BeaconTime & beaconTime);

        // Write results (events)
        void writeResults();

    private:
        // Global data

        /// List of beacons
        tester::MyBeaconList beaconList;

        /// List of events
        tester::EventList eventList;

        /// Start and finish of our route
        tester::Vec3 point1, point2;
        /// Start and finish time in arbitrary units (e.g. seconds)
        double t1, t2;
        /// Number of timestamp ticks per time unit
        double ticksPerTimeUnit;
        /// Lest of beacon time data
        std::vector<BeaconTime> beaconTimes;

    };
}


#endif //TESTERALL_FAKEENGINE_H
