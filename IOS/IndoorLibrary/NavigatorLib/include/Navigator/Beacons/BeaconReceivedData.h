//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//


#pragma once


#include <cmath>
#include "./BeaconUID.h"

namespace Navigator {
    namespace Beacons {
        
        /// Data package for one beacon
        /** @startuml
         *  class BeaconReceivedData <<(S,#FF7700)>>{
         *      + double timestamp
         *      + BeaconUID uid
         *      + double rssi
         *      + double txPower
         *  }
         *  note bottom : struct
         *  @enduml
         */
        struct BeaconReceivedData {

            BeaconReceivedData(double timestamp, const BeaconUID &uid, double rssi, double txPower = nan("")) :
                    timestamp(timestamp),
                    uid(uid),
                    rssi(rssi),
                    txPower(txPower) {}

            /// Timestamp in seconds
            double timestamp;

            /// Beacon uid
            BeaconUID uid;
            
            /// Received signal strength
            double rssi;

            //todo remove. Usually this parameter is calibrated, beacon sends wrong info
            /// TxPower from the measurement (optional, better not use?)
            double txPower = nan("");
        };
    }
}


