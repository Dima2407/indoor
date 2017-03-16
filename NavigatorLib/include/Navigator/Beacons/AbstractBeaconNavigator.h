//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#pragma once

#include "Navigator/Math/Position3D.h"
#include "Navigator/Beacons/BeaconReceivedData.h"

namespace Navigator {
    namespace Beacons {
        /** @startuml
         * class  AbstractBeaconNavigator
         * @enduml */
        class AbstractBeaconNavigator {
        public:
            /// Process a single input data
            virtual const Math::Position3D &process(const BeaconReceivedData & brd) = 0;
        };
    }
}

