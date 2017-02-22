//
// Created by  Oleksiy Grechnyev on 2/2/2017.
//

#ifndef TESTER_MYBRIDGE_H
#define TESTER_MYBRIDGE_H

#include "MyBeacon.h"

/** \brief My interface to tracking_lib (static methods only, no global data, uses tracking_lib)
 *
 *   Should allow to work with beacons etc. without resorting to using tracking_lib classes and datatypes directly
 */
namespace tester {
    class MyBridge {
    public:
        /// Init everything if needed, remove all beacons
        static void init();

        /// Add a new beacon
        static void newBeacon(double x, double y, double z, long long hash, double txPower, double damp);

        /// Add a new beacon from MyBeacon object
        static void newBeacon(MyBeacon const &beacon);

        /// Add a new measurement
        static void newMeasurement(long long hash, double txPower, double rssi, long long timestamp);

        /// Get position from trilateration
        static double getX();
        static double getY();
        static double getZ();
    };
}

#endif //TESTER_MYBRIDGE_H
