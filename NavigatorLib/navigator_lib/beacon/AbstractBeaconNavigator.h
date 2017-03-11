//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#pragma once

#include "../INavigator.h"
#include "./Position3D.h"
#include "./BeaconReceivedData.h"

namespace navi {
    namespace beacon {
        /** @startuml
         * class  AbstractBeaconNavigator
         * @enduml */
        class AbstractBeaconNavigator : public navi::INavigator {
        public:
            virtual Position3D &process(BeaconReceivedData b) = 0;
        };
    }
}

