//
// Created by  Oleksiy Grechnyev on 2/2/2017.
//
#include <cmath>

#include "MyBeacon.h"

namespace tester {


    double MyBeacon::distance(double txPower, double damp, double rssi) {
        return std::pow(10.0, (txPower - rssi) / (10.0 * damp));
    }

    double MyBeacon::distanceTo(double rssi)  const{
        return distance(txPower, damp, rssi);
    }


    double MyBeacon::calcRssi(double txPower, double damp, double dist) {
        return txPower - 10.0 * damp * std::log10(dist);
    }

    double MyBeacon::calcRssiDist(double dist) const {
        return calcRssi(txPower, damp, dist);
    }

    double MyBeacon::calcRssiPos(double pX, double pY, double pZ)  const{
        // Distance from beacon to (pX, pY, pZ) squared
        double d2 = (pX - x) * (pX - x) + (pY - y) * (pY - y) + (pZ - z) * (pZ - z);

        return calcRssiDist(std::sqrt(d2));
    }

    std::ostream &operator<<(std::ostream &os, const MyBeacon &beacon) {
        os << "x: " << beacon.x << " y: " << beacon.y << " z: " << beacon.z << " hash: " << beacon.hash << " txPower: "
           << beacon.txPower << " damp: " << beacon.damp;
        return os;
    }


}
