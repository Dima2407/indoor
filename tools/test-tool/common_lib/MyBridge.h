//
// Created by  Oleksiy Grechnyev on 2/2/2017.
//

#ifndef TESTER_MYBRIDGE_H
#define TESTER_MYBRIDGE_H

#include "MyBeacon.h"

#include <Navigator.h>


/** \brief My very thin interface to tracking_lib (uses tracking_lib)
 *
 *   Should allow to work with beacons etc. without resorting to using tracking_lib classes and datatypes directly
 */
namespace tester {
    class MyBridge {
    public:

        // Stupid stupid Eigen !
        // This is needed to create this class with new, so it seems
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW


        //--------------------------------
        // Public Methods
        //--------------------------------

        /// Init everything if needed, empty for now
        void init() {}

        /// Add a new beacon
        void newBeacon(double x, double y, double z, long long hash, double txPower, double damp);

        /// Add a new beacon from MyBeacon object
        void newBeacon(MyBeacon const &beacon){
            newBeacon(beacon.x, beacon.y, beacon.z, beacon.hash, beacon.txPower, beacon.damp);
        }

        /// Add a new measurement
       void newMeasurement(long long hash, double txPower, double rssi, long long timestamp) {
            navigator.addBeaconMeasurement(hash, txPower, rssi, timestamp);
        }

        /// Get position from trilateration
        double getX(){
            return navigator.beacon().lastState().position().x;
        }

        double getY(){
            return navigator.beacon().lastState().position().y;
        }

        double getZ(){
            return navigator.beacon().lastState().position().z;
        }


    private:
        //--------------------------------
        // Private fields
        //--------------------------------

        /// The instance of Navigator from tracking_lib
        Navigator navigator;
    };
}

#endif //TESTER_MYBRIDGE_H
