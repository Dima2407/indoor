//
// Created by  Oleksiy Grechnyev on 3/1/2017.
//

#ifndef TESTTOOL_BEACONMEASUREMENT_H
#define TESTTOOL_BEACONMEASUREMENT_H

#include "common_defs.h"

/** \brief %Beacon measurement data (hash, txPower, rssi, timestamp)*/
struct BeaconMeasurement {
    /// Default constructor with stupid values
    BeaconMeasurement() : hash(-1), txPower(0), rssi(0), timestamp(-1) {}
    /// Beacon unique ID (MAC address hash ?)
    int    hash;
    /// Beacon unique ID (MAC address hash ?)
    double txPower;
    /// Recieved signal strength, logarithmic
    double rssi;
    /// Time stamp of the measurement
    timestamp_t   timestamp;
};


typedef std::list<BeaconMeasurement> BeaconMeasurementsContainer;

typedef std::map<int, BeaconMeasurementsContainer > BeaconHistoryContainer;


#endif //TESTTOOL_BEACONMEASUREMENT_H
