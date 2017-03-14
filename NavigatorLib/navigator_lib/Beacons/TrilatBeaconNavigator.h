//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#include <unordered_map>
#include <memory>

#include "./AbstractBeaconNavigator.h"
#include "./BeaconProcessor.h"
#include "Factory/IFilterFactory.h"
#include "../Math/Trilat/trilat.h"

#pragma once
namespace Navi {
    namespace Beacons {

        /** @brief Trilateration-based beacon navigator
         *
         * @startuml
         * class TrilatBeaconNavigator {
         * // This is the trilateration-based beacon navigator //
         * // You must add at least 3 beacons //
         * // And process events for at least 3 beacons //
         * // To get a nonzero result //
         * // Currently in 2D (z is ignored) //
         * --
         * + {static} BEACON_TIMEOUT : double = 10.0
         * ..
         * - rssiFilterFactory : std::shared_ptr<IFilterFactory>
         * - distanceFilterFactory : std::shared_ptr<IFilterFactory>
         * - beaconProcessorList : std::unordered_map<BeaconUID, std::shared_ptr<BeaconProcessor>>
         * - lastPosition : Position3D
         * --
         * + TrilatBeaconNavigator(rssiFilterFactory : const std::shared_ptr<IFilterFactory> &,
         *                        distanceFilterFactory : const std::shared_ptr<IFilterFactory> &)
         * ..
         * + process(const BeaconReceivedData &brd) : const Position3D &
         * + addBeacon(beacon: const Beacon &) : void
         * + deleteBeacon(uid: const BeaconUID &) : void
         * + clear() : void
         * + const getLastPosition() : const Math::Position3D &
         * }
         *
         * class TrilatBeaconNavigator <|.. abstract AbstractBeaconNavigator
         * @enduml
         *
         */
        class TrilatBeaconNavigator : public AbstractBeaconNavigator {
        public:
            /// Time to keep beacon filter history data since the last signal (in seconds)
            static constexpr double BEACON_TIMEOUT = 10.0;

            // -----  Public metthods ------
            /// Constructor
            TrilatBeaconNavigator(const std::shared_ptr<Factory::IFilterFactory> &rssiFilterFactory,
                                  const std::shared_ptr<Factory::IFilterFactory> &distanceFilterFactory)
                    : rssiFilterFactory(rssiFilterFactory),
                      distanceFilterFactory(distanceFilterFactory) {}

            /// Process a single input data
            const Math::Position3D &process(const BeaconReceivedData &brd) override;

            //------ Beacon operations -----

            /// Add a new beacon
            void addBeacon(const Beacon &beacon) {
                /// uid is the map key
                /// Factories create filter objects
                beaconProcessorList[beacon.getUid()] = std::make_shared<BeaconProcessor>(
                        beacon,
                        rssiFilterFactory->createFilter(),
                        distanceFilterFactory->createFilter()
                );
            }

            /// Delete a beacon by uid
            void deleteBeacon(const BeaconUID &uid) {
                beaconProcessorList.erase(uid);
            }

            /// Delete all beacons
            void clear() {
                beaconProcessorList.clear();
            }

            const Math::Position3D &getLastPosition() const {
                return lastPosition;
            }

            //----------------------------
            //---   Private data ------
        private:
            /// The RSSI filter factory
            std::shared_ptr<Factory::IFilterFactory> rssiFilterFactory;

            /// The distance filter factory
            std::shared_ptr<Factory::IFilterFactory> distanceFilterFactory;

            /// List of beacon processors for all beacons currently in use
            std::unordered_map<BeaconUID, std::shared_ptr<BeaconProcessor>> beaconProcessorList;

            /// Last located position
            Math::Position3D lastPosition = Math::Position3D(0, 0, 0, 0);
        };
    }
}