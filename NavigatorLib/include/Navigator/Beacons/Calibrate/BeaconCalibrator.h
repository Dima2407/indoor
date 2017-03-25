//
// Created by  Oleksiy Grechnyev on 3/24/2017.
//

#include <vector>
#include <unordered_map>

#include "Navigator/Beacons/Beacon.h"
#include "Navigator/Beacons/BeaconUID.h"
#include "Navigator/Beacons/BeaconReceivedData.h"



#include "./CalibrationConfig.h"
#include "./CalibrationPoint.h"

#pragma once

namespace Navigator {
    namespace Beacons {
        namespace Calibrate {

            /**
             *
             */
            class BeaconCalibrator {

            public: // ==== methods ====

                const std::unordered_map<BeaconUID, Beacon> &
                calibrate(const std::vector<CalibrationPoint> & points, const CalibrationConfig & config);

                /// Check if the (dist, rssi) point is legit (5 meters rule + line of sight (LOS))
                bool isLegit(double dist, double rssi, const CalibrationConfig & config);

                /// Add one beacon
                void addBeacon(const Beacon &beacon) {
                    beaconMap[beacon.getUid()] = beacon;
                }

                /// Add several beacons
                template <typename IterableT>
                void addBeacons(IterableT const& beacons) {
                    for( const auto & b : beacons )
                        this->addBeacon(b);
                }

                /// Delete a beacon by uid
                void deleteBeacon(const BeaconUID &uid) {
                    beaconMap.erase(uid);
                }

                /// Delete all beacons
                void clear() {
                    beaconMap.clear();
                }

            public: // ==== getters ====

                const std::unordered_map<BeaconUID, Beacon> &getBeaconMap() const {
                    return beaconMap;
                }

            private: // === data ====
                /// Map of beacons currently in use versus their UID for easier search
                std::unordered_map<BeaconUID, Beacon> beaconMap;
            };

        }
    }
}

