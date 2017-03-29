//
// Created by  Oleksiy Grechnyev on 3/10/2017.
//

#pragma once

#include "./IFilter.h"

namespace Navigator {
    namespace Math {
        namespace Filter {

            /// Empty filter implementation: returns the input double value
            class NoFilter : public IFilter {
            public:
                Value process(Value in) override {
                    return in;
                }
            };
        }
    }
}
