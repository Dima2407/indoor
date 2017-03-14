//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#pragma once

#include "../Math/Position3D.h"
#include "./BeaconReceivedData.h"

namespace Navi {
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

