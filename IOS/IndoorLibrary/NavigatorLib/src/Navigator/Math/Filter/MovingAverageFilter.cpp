//
// Created by  Oleksiy Grechnyev on 3/13/2017.
//

#include "MovingAverageFilter.h"

namespace Navigator {
    namespace Math {
        namespace Filter {

            //todo Maybe make Iterative mean to improve speed
            double MovingAverageFilter::process(double in) {
                double result; // The result (the new average)

                if (0 == dataCount) {
                    // The very first value
                    dataCount = 1;
                    result = in;

                } else if (winSize == dataCount) {

                    // Filter is in the stationary mode, dataCount is already at the max
                    // At each step we push one element, pop one element
                    // dataCount never changes from now on

                    double oldest; // The oldest element, we discard it
                    assert(buffer.pop(oldest)); // Pop the oldest value

                    result = average + (in - oldest) / dataCount; // Update the average

                } else {

                    // Not the first element, but not full yet, 0 < dataCount < winSize
                    double sum = average * dataCount; // The previous sum
                    dataCount++; // Update the count
                    sum += in; // Add the new value without subtracting anything
                    result = sum / dataCount; // The new average with the new dataCount
                }


                assert(buffer.push(in)); // Push the latest value

                average = result; // Save the new average

                return result;
            }
        }
    }
}

