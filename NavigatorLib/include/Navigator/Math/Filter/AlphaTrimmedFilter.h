//
// Created by  Oleksiy Grechnyev on 4/3/2017.
//

#pragma once

#include "./IFilter.h"
#include "./RingBuffer.h"

namespace Navigator {
    namespace Math {
        namespace Filter {

            class AlphaTrimmedFilter : public IFilter {
            public: // ======= Methods

                AlphaTrimmedFilter(unsigned int winSize, double alpha) :
                        winSize(winSize),
                        alpha(alpha),
                        buffer(winSize) {
                    assert(0.0 <= alpha && alpha <= 0.5);
                    assert(winSize > 0);
                }

                /// Run a value through the filter
                Value process(Value in) override;

                /// Reset the filter and forget all history
                void reset() override {
                    buffer.clear();
                }

            private: // ====== Values
                /// The filter window size
                unsigned winSize;

                /// The parameter alpha
                double alpha;

                /// The ring buffer
                RingBuffer<Value> buffer;

            };

        }
    }
}

