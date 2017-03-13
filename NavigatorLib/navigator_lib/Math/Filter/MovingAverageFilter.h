//
// Created by  Oleksiy Grechnyev on 3/13/2017.
//

#pragma once

#include <memory>
#include <cassert>

#include "./IFilter.h"
#include "./RingBuffer.h"

namespace Navi {
    namespace Math {
        namespace Filter {

            class MovingAverageFilter : public IFilter {
                //-------------------------------------------------
                // Public methods:
                //-------------------------------------------------
            public:

                /** @brief Constructor
                 *
                 * Note: The bufffer size is winSize + 1
                 * winSize + 1 would suffice, but let's play it safe
                 *
                 * @param winSize  The filter window size
                 */
                MovingAverageFilter(unsigned int winSize) :
                        winSize(winSize),
                        buffer(winSize + 1)
                {
                    assert(winSize > 0);
                }

                /// Run a double value through the filter
                double process(double in) override;

                /// Reset the filter and forget all history
                void reset() override {
                    dataCount = 0;
                    buffer.clear();
                }

                //-------------------------------------------------
                // Private data:
                //-------------------------------------------------
                /// The filter window size
                unsigned winSize;

                /// The ring buffer
                RingBuffer<double> buffer;

                /// The current data count in the filter, 0 <= dataCount <= winSize
                unsigned dataCount = 0;

                /// The average caculated on each step
                double average = 0;
            };

        }
    }
}
