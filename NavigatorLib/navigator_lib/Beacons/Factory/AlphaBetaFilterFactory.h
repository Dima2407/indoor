//
// Created by  Oleksiy Grechnyev on 3/14/2017.
//

#pragma once


#include "./IFilterFactory.h"
#include "../../Math/Filter/AlphaBetaFilter.h"

namespace Navi {
    namespace Beacons {
        namespace Factory {
            /** @brief A factory for creating AlphaBetaFilter
             *
             * @startuml
             * class AlphaBetaFilterFactory{
             * // A factory for creating AlphaBetaFilter  //
             * --
             * - alpha: douuble
             * - beta: douuble
             * --
             * + AlphaBetaFilterFactory(alpha: douuble, beta: douuble)
             * + createFilter() : std::shared_ptr<IFilter>
             * }
             *
             * AlphaBetaFilterFactory <|.. interface IFilterFactory
             * @enduml
             */
            class AlphaBetaFilterFactory : public IFilterFactory {
                // -----  Public metthods ------
            public:
                /// Constructor
                AlphaBetaFilterFactory(double alpha, double beta) :
                        alpha(alpha),
                        beta(beta) {}

                /// Create an AlphaBetaFilter object
                std::shared_ptr<Math::Filter::IFilter> createFilter() override {
                    return std::make_shared<Math::Filter::AlphaBetaFilter>(alpha, beta);
                }

                //---   Private data ------
            private:
                /// Alpha of AlphaBetaFilter
                double alpha;

                /// Beta of AlphaBetaFilter
                double beta;
            };

        }
    }
}

