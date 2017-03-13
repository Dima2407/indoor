//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#pragma once

#include "../INavigator.h"
#include "../Math/Position3D.h"
#include "./BeaconReceivedData.h"

namespace Navi {
    namespace Beacons {
        /** @startuml
         * class  AbstractBeaconNavigator
         * @enduml */
        class AbstractBeaconNavigator : public INavigator {
        public:
            virtual Math::Position3D &process(BeaconReceivedData b) = 0;
        };
    }
}

