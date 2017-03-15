//
// Created by  Oleksiy Grechnyev on 3/14/2017.
//

#pragma once


#include "./IFilterFactory.h"
#include "../../Math/Filter/NoFilter.h"

namespace Navi {
    namespace Beacons {
        namespace Factory {
            /** @brief A factory for creating AlphaBetaFilter
             *
             * @startuml
             * class NoFilterFactory{
             * // A factory for creating NoFilter  //
             * --
             * + NoFilterFactory()
             * + createFilter() : std::shared_ptr<IFilter>
             * }
             *
             * NoFilterFactory <|.. interface IFilterFactory
             * @enduml
             */
            class NoFilterFactory : public IFilterFactory{
            public:
            private:
                std::shared_ptr<Math::Filter::IFilter> createFilter() override {
                    return std::make_shared<Math::Filter::NoFilter>();
                }
            };
        }
    }
}
