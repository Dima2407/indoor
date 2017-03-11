//
// Created by  Oleksiy Grechnyev on 3/10/2017.
//

#pragma once

#include "./IFilter.h"

namespace navi {
    namespace filter {

        /// Empty filter implementation: returns the input double value
        class NoFilter : public IFilter {
        public:
            double process(double in) override
            {
                return in;
            }
        };
    }
}


