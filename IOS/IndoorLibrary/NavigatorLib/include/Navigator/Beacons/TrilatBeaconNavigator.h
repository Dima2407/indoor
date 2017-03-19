//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#include <unordered_map>
#include <memory>

#include "AbstractBeaconNavigator.h"
#include "BeaconProcessor.h"
#include "IFilterFactory.h"
#include "Trilat.h"

#pragma once
namespace Navigator {
    namespace Beacons {

        /** @brief Trilateration-based beacon navigator
         *
         * @startuml
         * class TrilatBeaconNavigator {
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
         * note bottom
         * // This is the trilateration-based beacon navigator //
         * // You must add at least 3 beacons //
         * // And process events for at least 3 beacons //
         * // To get a nonzero result //
         * // Currently in 2D (z is ignored) //
         * endnote
         *
         * class TrilatBeaconNavigator .up.|> abstract AbstractBeaconNavigator
         * interface Factory::IFilterFactory --o TrilatBeaconNavigator : rssiFilterFactory
         * interface Factory::IFilterFactory --o TrilatBeaconNavigator : distanceFilterFactory
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
    
            /// Add Beacons
            template <typename IterableT>
            void addBeacons(IterableT const& beacons) {
                for( auto b : beacons )
                    this->addBeacon(b);
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
            Math::Position3D lastPosition = Math::Position3D();
        };
    }
}
