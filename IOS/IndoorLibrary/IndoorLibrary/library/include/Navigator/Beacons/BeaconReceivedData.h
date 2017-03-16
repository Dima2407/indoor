//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//


#pragma once

#include "./BeaconUID.h"

namespace Navi {
    namespace Beacons {
        /// Data package for one beacon
        struct BeaconReceivedData {

            BeaconReceivedData(double timestamp, const BeaconUID &uid, double rssi, double txPower = 0.0) :
                    timestamp(timestamp),
                    uid(uid),
                    rssi(rssi),
                    txPower(txPower) {}

            /// Timestamp in seconds
            double timestamp;

            /// Beacon uid
            BeaconUID uid;

            /// Received signal strenggth
            double rssi;

            /// TxPower from the measurement (optional, bettter not use?)
            double txPower;
        };
    }
}


