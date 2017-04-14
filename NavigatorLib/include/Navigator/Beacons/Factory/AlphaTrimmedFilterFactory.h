//
// Created by  Oleksiy Grechnyev on 4/5/2017.
//

#pragma once


#include "Navigator/Beacons/Factory/IFilterFactory.h"
#include "Navigator/Math/Filter/AlphaTrimmedFilter.h"

namespace Navigator {
    namespace Beacons {
        namespace Factory {
            /** @brief A factory for creating AlphaTrimmedFilter
             *
             * @startuml
             * class MovingAverageFilterFactory{
             * - winSize: unsigned int
             * - alpha: double
             * --
             * + MovingAverageFilterFactory(winSize: unsigned int)
             * + createFilter() : std::shared_ptr<IFilter>
             * }
             * note bottom : // A factory for creating MovingAverageFilter  //
             * MovingAverageFilterFactory .up.|> interface IFilterFactory : //implements//
             * @enduml
             */
            class AlphaTrimmedFilterFactory : public IFilterFactory {
            public: //==== Methods ====

                /// Constructor
                AlphaTrimmedFilterFactory(unsigned int winSize, double alpha) :
                        winSize(winSize),
                        alpha(alpha) {}

                /// Create a MovingAverageFilter object
                std::shared_ptr<Math::Filter::IFilter> createFilter() override {
                    return std::make_shared<Math::Filter::AlphaTrimmedFilter>(winSize, alpha);
                }


            private: // === Data ===
                /// Filter window size
                unsigned int winSize;

                // The parameter alpha
                double alpha;
            };


        }
    }
}
