//
// Created by  Oleksiy Grechnyev on 2/2/2017.
//

#ifndef TESTER_MYBEACON_H
#define TESTER_MYBEACON_H

/** \brief Beacon class for tester
 *
 * It is completely separate from any classes in tracking_lib
 */
namespace tester {

    struct MyBeacon {
        /// Beacon coordinates
        double x, y, z;

        /// Hash code
        long long hash;

        /// Emission power in dBm
        double txPower;

        /// Dampening parameter
        double damp;

        /// Default constructor
        MyBeacon() {}

        /// Good constructor
        MyBeacon(double x, double y, double z, long long int hash, double txPower, double damp) : x(x), y(y), z(z),
                                                                                                  hash(hash),
                                                                                                  txPower(txPower),
                                                                                                  damp(damp) {}

        /// The distance function (from rssi, txPower, damp)
        static double distance(double txPower, double damp, double rssi);

        /// Distance to the beacon from RSSI and beacon data
        double distanceTo(double rssi);

        /// RSSI from txPower, damp, distance (Inverse of distance)
        static double calcRssi(double txPower, double damp, double dist);

        /// RSSI from distance from current beacon
        double calcRssiDist(double dist);

        /// RSSI from point position
        double calcRssiPos(double pX, double pY, double pZ);
    };

}
#endif //TESTER_MYBEACON_H
