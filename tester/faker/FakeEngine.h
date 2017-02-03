//
// Created by  Oleksiy Grechnyev on 2/3/2017.
//

#ifndef TESTERALL_FAKEENGINE_H
#define TESTERALL_FAKEENGINE_H

#include <vector>
#include <cstdlib>

#include "MyBeacon.h"
#include "Vec3.h"
#include "BeaconTime.h"
#include "Event.h"



namespace faker {

    /// Main class of faker, static only
    class FakeEngine {
    private:
        /// Don't do that !
        FakeEngine() { exit(1); }

    public:
        // Global data

        /// List of beacons
        static std::vector<tester::MyBeacon> beacons;

        /// Start and finish of our route
        static Vec3 point1, point2;
        /// Start and finish time in arbitrary units (e.g. seconds)
        static double t1, t2;
        /// Number of timestamp ticks per time unit
        static double ticksPerTimeUnit;
        /// Lest of beacon time data
        static std::vector<BeaconTime> beaconTimes;
        /// List of events
        static std::vector<Event> events;

        /////////////////////////

        /// Read beacons from file in_beacons.dat
        static void readBeacons();

        /// Read faker input file in_faker.dat
        static void readInput();

        /// Calculate trajectory Vec3(t), linear at present
        static Vec3 trajectory(double t);

        /// Check if beacon with hash exists iin beacons
        static bool beaconExists(long long hash);

        /// Find beacon by hash
        static tester::MyBeacon & findBeacon(long long hash);

        /// Do the actual calculation
        static void run();
    };
}


#endif //TESTERALL_FAKEENGINE_H
