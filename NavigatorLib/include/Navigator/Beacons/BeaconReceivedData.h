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
         *      +  timestamp : double
         *      +  uid : BeaconUID
         *      +  rssi : double
         *      +  txPower : double
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

            BeaconReceivedData() {}

            bool operator==(const BeaconReceivedData &rhs) const {
                return timestamp == rhs.timestamp &&
                       uid == rhs.uid &&
                       rssi == rhs.rssi /*&&
                       txPower == rhs.txPower*/;
            }

            bool operator!=(const BeaconReceivedData &rhs) const {
                return !(rhs == *this);
            }

            /// Timestamp in seconds
            double timestamp = std::nan("");

            /// Beacon uid
            BeaconUID uid;
            
            /// Received signal strength
            double rssi = std::nan("");

            //todo remove. Usually this parameter is calibrated, beacon sends wrong info
            /// TxPower from the measurement (optional, better not use?)
            double txPower = std::nan("");
        };
    }
}


