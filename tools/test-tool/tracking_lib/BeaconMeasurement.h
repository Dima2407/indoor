//
// Created by  Oleksiy Grechnyev on 3/1/2017.
//

#ifndef TESTTOOL_BEACONMEASUREMENT_H
#define TESTTOOL_BEACONMEASUREMENT_H

#include "common_defs.h"

/** \brief %Beacon measurement data (hash, txPower, rssi, timestamp)*/
struct BeaconMeasurement {

    /// Beacon unique ID (MAC address hash ?)
    int    hash = -1;
    /// Beacon unique ID (MAC address hash ?)
    double txPower = 0;
    /// Recieved signal strength, logarithmic
    double rssi = 0;
    /// Time stamp of the measurement
    timestamp_t   timestamp = -1;
};


typedef std::list<BeaconMeasurement> BeaconMeasurementsContainer;

typedef std::map<int, BeaconMeasurementsContainer > BeaconHistoryContainer;


#endif //TESTTOOL_BEACONMEASUREMENT_H
