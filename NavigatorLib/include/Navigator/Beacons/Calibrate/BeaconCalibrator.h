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
#include "Navigator/Beacons/Calibrate/Algorithm/algorithm.h"


#pragma once

namespace Navigator {
    namespace Beacons {
        namespace Calibrate {

            /** @brief This class is used to calibrate beacons
             *
             * @startuml
             * class BeaconCalibrator{
             * // This class is used to calibrate beacons //
             * --
             * - beaconMap : std::unordered_map<BeaconUID, Beacon>
             * --
             * + calibrate(points : const std::vector<CalibrationPoint> & , config : const CalibrationConfig & ) :
             * const std::unordered_map<BeaconUID, Beacon> &
             * + isLegit(dist : double, rssi : double, config : const CalibrationConfig &) : bool
             * + addBeacon(beacon : const Beacon &) : void
             * + addBeacons<IterableT>(beacons : IterableT const&) : void
             * + deleteBeacon(uid : const BeaconUID &) : void
             * }
             * @enduml
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

                const std::unordered_map<BeaconUID, Algorithm::CalibrationTable> &getCalTables() const {
                    return calTables;
                }

            private: // === data ====
                /// Map of beacons currently in use versus their UID for easier search
                std::unordered_map<BeaconUID, Beacon> beaconMap;

                // Calibration tables for each beacons from the input signal
                // Format: 2-column table
                // distance average_RSSI
                // For each beacon
                std::unordered_map<BeaconUID, Algorithm::CalibrationTable> calTables;
            };

        }
    }
}

