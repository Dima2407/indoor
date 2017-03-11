//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//


#pragma once

#include "./BeaconUID.h"

namespace navi {
    namespace beacon {
        /// Data package for one beacon
        struct BeaconReceivedData {
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


