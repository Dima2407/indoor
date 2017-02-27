//
// Created by  Oleksiy Grechnyev on 2/2/2017.
//

#ifndef TESTER_MYBRIDGE_H
#define TESTER_MYBRIDGE_H

#include "MyBeacon.h"

/** \brief My very thin interface to tracking_lib (uses tracking_lib)
 *
 *   Should allow to work with beacons etc. without resorting to using tracking_lib classes and datatypes directly
 */
namespace tester {
    class MyBridge {
    public:
        /// Init everything if needed, remove all beacons
        void init();

        /// Add a new beacon
        void newBeacon(double x, double y, double z, long long hash, double txPower, double damp);

        /// Add a new beacon from MyBeacon object
        void newBeacon(MyBeacon const &beacon);

        /// Add a new measurement
       void newMeasurement(long long hash, double txPower, double rssi, long long timestamp);

        /// Get position from trilateration
        double getX();
        double getY();
        double getZ();
    };
}

#endif //TESTER_MYBRIDGE_H
