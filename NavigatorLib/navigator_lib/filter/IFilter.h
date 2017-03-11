//
// Created by  Oleksiy Grechnyev on 3/10/2017.
//

#pragma once

namespace navi {
    namespace filter {

        /// Filter interface
        class IFilter {
        public:
            /// Run a double through the filter and get the result
            virtual double process(double in) = 0;

            /// Alias to process() by default
            virtual double operator()(double in)
            {
                return process(in);
            }

            /// Virtual Destructor
            virtual ~IFilter() {}
        };
    }
}
