//
// Created by  Oleksiy Grechnyev on 3/14/2017.
//

#pragma once

#include <memory>

#include "../../Math/Filter/IFilter.h"

namespace Navi {
    namespace Beacons {
        namespace Factory {

            /** @brief A factory interface for filter creation
             *
             * @startuml
             * interface IFilterFactory {
             *   ..
             *   + {abstract} createFilter() : std::shared_ptr<IFilter>
             * }
             * note bottom
             *   A factory interface for filter creation
             * end note
             * @enduml
             */
            class IFilterFactory {
            public:
                /// Create a fiter object
                virtual std::shared_ptr<Math::Filter::IFilter> createFilter() = 0;
            };
        }
    }
}



