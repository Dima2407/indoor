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

        // Destructor
        ~MyBridge(){
            delete navigator;
        }

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
            navigator->addBeaconMeasurement(hash, txPower, rssi, timestamp);
        }

        /// Get position from trilateration
        double getX(){
            return navigator->beacon().lastState().position().x;
        }

        double getY(){
            return navigator->beacon().lastState().position().y;
        }

        double getZ(){
            return navigator->beacon().lastState().position().z;
        }


    private:
        //--------------------------------
        // Private fields
        //--------------------------------

        /** \brief The instance of Navigator from tracking_lib
         *
         * I use a pointer here to localize the Eigen trouble
         */
        Navigator *navigator = new Navigator;
    };
}

#endif //TESTER_MYBRIDGE_H
