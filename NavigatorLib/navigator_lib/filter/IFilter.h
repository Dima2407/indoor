//
// Created by  Oleksiy Grechnyev on 3/10/2017.
//

#pragma once

namespace navi {
    namespace filter {

        /// Filter interface
        class IFilter {
        public:
            //------------------------------------
            // Public abstract method: must implement
            //------------------------------------

            /// Run a double value through the filter
            virtual double process(double in) = 0;

            //------------------------------------
            // Public methods: default and optional
            //------------------------------------

            /// Reset the filter and forget all history, optional
            virtual void reset() {}

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
