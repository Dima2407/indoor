//
// Created by  Oleksiy Grechnyev on 3/13/2017.
//

#pragma once

#include <memory>
#include <cassert>

#include "./IFilter.h"
#include "./RingBuffer.h"

namespace Navigator {
    namespace Math {
        namespace Filter {

            /** @brief Moving Average Filter
             *
             * @startuml
             * class MovingAverageFilter{
             * // Moving Average Filter //
             * // //
             * // window size must be specified //
             * // operator() is an alias to process() //
             * --
             * - winSize : unsigned
             * - buffer : RingBuffer<double>
             * - dataCount : unsigned
             * - average : double
             * --
             * + MovingAverageFilter(winSize : unsigned int)
             * + process(in: Value) : Value
             * + reset() : void
             * + operator() (in: Value) : Value
             * }
             *
             * MovingAverageFilter <|.. interface IFilter
             * @enduml
             */
            class MovingAverageFilter : public IFilter {
                //-------------------------------------------------
                // Public methods:
                //-------------------------------------------------
            public:

                /** @brief Constructor
                 *
                 * Note: The bufffer size is winSize
                 *
                 * @param winSize  The filter window size
                 */
                explicit MovingAverageFilter(unsigned int winSize) :
                        winSize(winSize),
                        buffer(winSize)
                {
                    if (0 == winSize ) throw std::runtime_error("MovingAverageFilter : winSize == 0 !");
                }

                /// Run a double value through the filter
                Value process(Value in) override;

                /// Reset the filter and forget all history
                void reset() override {
                    dataCount = 0;
                    buffer.clear();
                }
                
                //-------------------------------------------------
                // Private data:
                //-------------------------------------------------
            private:
                /// The filter window size
                unsigned winSize;

                /// The ring buffer
                RingBuffer<Value> buffer;

                /// The current data count in the filter, 0 <= dataCount <= winSize
                unsigned dataCount = 0;

                /// The average caculated on each step
                double average = 0;
            };

        }
    }
}
