//
// Created by  Oleksiy Grechnyev on 3/11/2017.
//

#pragma once

#include <cmath>

#include "./IFilter.h"

namespace Navigator {
    namespace Math {
        namespace Filter {
            
            /** @brief Alpha-Beta filter implementing IFilter interface
             *
             *
             * @startuml
             * class AlphaBetaFilter {
             *   ..
             *   + AlphaBetaFilter(alpha: double, beta: double)
             *   + process(in: double) : double
             *   + reset() : void
             * }
             * note bottom
             * // Alpha-Beta Filter //
             * // operator() is an alias to process() //
             * endnote
             *
             * AlphaBetaFilter .up.|> interface IFilter : implements
             * @enduml
             */
            class AlphaBetaFilter : public IFilter {
            public:
                //------------------------------------
                // Public methods
                //------------------------------------

                /// Constructor
                AlphaBetaFilter(double alpha, double beta) :
                        alpha(alpha),
                        beta(beta) {}

                /// Run a double value through the filter
                double process(double in) override;

                /// Reset the filter and forget all history
                void reset() override {
                    initialized = false; // This is important

                    x0 = nan(""); // This isn't
                    v0 = nan("");
                }


            private:

                //------------------------------------
                // Private const
                //------------------------------------

                /// dt of the alpha-beta filter, we can always use 1.0
                static constexpr double DT = 1.0;

            private:
                //------------------------------------
                // Private fields
                //------------------------------------

                /// Parameter alpha
                double alpha;

                /// Parameter beta
                double beta;

                /// True if the filter has been initialized by the first data value
                bool initialized = false;

                /// Previous position
                double x0 = nan("");

                /// Previous velocity
                double v0 = nan("");

            };


        }
    }
}