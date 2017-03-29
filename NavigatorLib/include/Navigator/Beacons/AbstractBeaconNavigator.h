//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#pragma once

#include <vector>

#include "Navigator/Math/Position3D.h"
#include "Navigator/Beacons/BeaconReceivedData.h"

namespace Navigator {
    namespace Beacons {
        /** @startuml
         * class  AbstractBeaconNavigator {
         * + {abstract} process(const BeaconReceivedData &brd) : const Position3D &
         * + {abstract} process(const std::vector<BeaconReceivedData> &brd) : const Position3D &
         * + {abstract} const getLastPosition() : const Math::Position3D &
         *
         * }
         * @enduml */
        class AbstractBeaconNavigator {
        public:
            /// Process a single input data
            virtual const Math::Position3D &process(const BeaconReceivedData & brd) = 0;

            /// Process a vector of input data, assuming identical timestamps
            virtual const Math::Position3D &process(const std::vector<BeaconReceivedData> & brds) = 0;

            /// Get last position
            virtual const Math::Position3D &getLastPosition() const = 0;
        };
    }
}

