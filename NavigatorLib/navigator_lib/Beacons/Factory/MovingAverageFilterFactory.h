//
// Created by  Oleksiy Grechnyev on 3/14/2017.
//

#pragma once

#include "./IFilterFactory.h"
#include "../../Math/Filter/MovingAverageFilter.h"

namespace Navi {
    namespace Beacons {
        namespace Factory {
            /** @brief A factory for creating MovingAverageFilter
             *
             * @startuml
             * class MovingAverageFilterFactory{
             * // A factory for creating MovingAverageFilter  //
             * --
             * - winSize: unsigned int
             * --
             * + MovingAverageFilterFactory(winSize: unsigned int)
             * + createFilter() : std::shared_ptr<IFilter>
             * }
             *
             * MovingAverageFilterFactory <|.. interface IFilterFactory
             * @enduml
             */
            class MovingAverageFilterFactory : IFilterFactory {
                // -----  Public metthods ------
            public:
                /// Constructor
                MovingAverageFilterFactory(unsigned int winSize) :
                        winSize(winSize) {}

                /// Create a MovingAverageFilter object
                std::shared_ptr<Math::Filter::IFilter> createFilter() override {
                    return std::make_shared<Math::Filter::MovingAverageFilter>(winSize);
                }

                //---   Private data ------
            private:
                /// Filter window size
                unsigned int winSize;

            };

        }
    }
}
