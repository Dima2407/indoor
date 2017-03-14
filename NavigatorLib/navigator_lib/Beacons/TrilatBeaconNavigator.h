//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#include <map>
#include <memory>

#include "./AbstractBeaconNavigator.h"
#include "./BeaconProcessor.h"
#include "Factory/IFilterFactory.h"
#include "../Math/Trilat/trilat.h"

#pragma once
namespace Navi {
    namespace Beacons {

        // TODO : implement this class
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
            Math::Position3D &process(const BeaconReceivedData & brd) override;

            //------ Beacon operations -----

            /// Add a new beacon
            void addBeacon(const Beacon &beacon) {
                /// uid is the map keys
                /// Factories create filter objects
                beaconProcessorList.insert(std::make_pair(beacon.getUid(),
                                                          std::make_shared<BeaconProcessor>(
                                                                  beacon,
                                                                  rssiFilterFactory->createFilter(),
                                                                  distanceFilterFactory->createFilter()
                                                          )));
            }

            /// Delete a beacon by uid
            void deleteBeacon(const BeaconUID &uid) {
                beaconProcessorList.erase(uid);
            }

            /// Delete all beacons
            void clear() {
                beaconProcessorList.clear();
            }

            //----------------------------
            //---   Private data ------
        private:
            /// The RSSI filter factory
            std::shared_ptr<Factory::IFilterFactory> rssiFilterFactory;

            /// The distance filter factory
            std::shared_ptr<Factory::IFilterFactory> distanceFilterFactory;

            /// List of beacon processors for all beacons currently in use
            std::map<BeaconUID, std::shared_ptr<BeaconProcessor>> beaconProcessorList;

            /// Last located position
            Math::Position3D lastPosition = Math::Position3D(0, 0, 0, 0);
        };
    }
}