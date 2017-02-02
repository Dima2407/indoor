//
// Created by  Oleksiy Grechnyev on 2/2/2017.
//
#include <cmath>

#include "MyBeacon.h"

namespace tester {
    double MyBeacon::distanceTo(double rssi) {
        return std::pow(10.0, (txPower - rssi) / (10.0 * damp));;
    }

    double MyBeacon::calcRssi(double dist) {
        return txPower - 10.0 * damp * std::log10(dist);
    }

    double MyBeacon::calcRssiPos(double pX, double pY, double pZ) {
        // Distance from beacon to (pX, pY, pZ) squared
        double d2 = (pX - x) * (pX - x) + (pY - y) * (pY - y) + (pZ - z) * (pZ - z);

        return calcRssi(std::sqrt(d2));
    }
}
