//
// Created by  Oleksiy Grechnyev on 3/14/2017.
//

#pragma once

#include "Navigator/Beacons/Factory/IFilterFactory.h"
#include "Navigator/Math/Filter/MovingAverageFilter.h"

namespace Navi {
    namespace Beacons {
        namespace Factory {
            /** @brief A factory for creating MovingAverageFilter
             *
             * @startuml
             * class MovingAverageFilterFactory{
             * - winSize: unsigned int
             * --
             * + MovingAverageFilterFactory(winSize: unsigned int)
             * + createFilter() : std::shared_ptr<IFilter>
             * }
             * note bottom : // A factory for creating MovingAverageFilter  //
             * MovingAverageFilterFactory .up.|> interface IFilterFactory : //implements//
             * @enduml
             */
            class MovingAverageFilterFactory : public IFilterFactory {
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
