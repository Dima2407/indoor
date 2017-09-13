//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#pragma once

#include <vector>

#include "Navigator/Math/Position3D.h"
#include "Navigator/Beacons/BeaconReceivedData.h"
#include "Navigator/Beacons/BeaconProcessor.h"
#include "Navigator/Beacons/Beacon.h"
#include "Navigator/INavigator.h"

namespace Navigator {
    namespace Beacons {
        /** @startuml
         * class  AbstractBeaconNavigator {
         * + {abstract} process(const BeaconReceivedData &brd) : const Position3D &
         * + {abstract} process(const std::vector<BeaconReceivedData> &brd) : const Position3D &
         * + {abstract} findProcessorByUid(uid : BeaconUID) : const std::shared_ptr<BeaconProcessor>
         * + {abstract} onst getLastPosition() : const Math::Position3D &
         * ..
         * + {abstract} addBeacon(beacon: const Beacon &) : void
         * + {abstract} deleteBeacon(uid: const BeaconUID &) : void
         * + {abstract} clear() : void
         * + {abstract} reset() : void
         *
         * }
         * @enduml */
        class AbstractBeaconNavigator : public INavigator{
        public:
            /// Process a single input data
            virtual const Math::Position3D &process(const BeaconReceivedData & brd) = 0;

            /// Process a vector of input data, assuming identical timestamps
            virtual const Math::Position3D &process(const std::vector<BeaconReceivedData> & brds) = 0;

            /// Get last position
            virtual const Math::Position3D &getLastPosition() const = 0;

            virtual Math::Position3D obtainLastPosition() override {
                return getLastPosition();
            }

            /// Add a new beacon
            virtual void addBeacon(const Beacon &beacon) = 0;

            /// Add Beacons
            template <typename IterableT>
            void addBeacons(IterableT const& beacons) {
                for( const auto & b : beacons )
                    this->addBeacon(b);
            }

            /// Find a BeaconProcessor by uid, nullptr if not found
            virtual const std::shared_ptr<BeaconProcessor> findProcessorByUid(const BeaconUID & uid) const = 0;

            /// Delete a beacon by uid
            virtual void deleteBeacon(const BeaconUID &uid) = 0;

            /// Delete all beacons and reset
            virtual void clear() = 0;

            /// Reset filters etc but don't clear beacons
            virtual void reset() = 0;

            virtual const bool isInitFinished() const = 0;

            const std::vector<Math::Position2D> &getLastTrilatPosition() const {
                return lastTrilatPosition;
            }

        protected:
            std::vector <Math::Position2D> lastTrilatPosition;
        };
    }
}

