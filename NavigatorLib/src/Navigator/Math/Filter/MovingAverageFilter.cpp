//
// Created by  Oleksiy Grechnyev on 3/13/2017.
//

#include "Navigator/Math/Filter/MovingAverageFilter.h"

namespace Navigator {
    namespace Math {
        namespace Filter {

            //todo Maybe make Iterative mean to improve speed
            IFilter::Value MovingAverageFilter::process(IFilter::Value in) {
                double result;

                if (0 == dataCount) {
                    // The very first value
                    dataCount = 1;
                    result = in.val;

                } else if (winSize == dataCount) {

                    // Filter is in the stationary mode, dataCount is already at the max
                    // At each step we push one element, pop one element
                    // dataCount never changes from now on

                    IFilter::Value oldestPair;
                    assert(buffer.pop(oldestPair)); // Pop the oldest value

                    // The oldest element, we discard it
                    result = average + (in.val - oldestPair.val) / dataCount; // Update the average

                } else {

                    // Not the first element, but not full yet, 0 < dataCount < winSize
                    double sum = average * dataCount; // The previous sum
                    dataCount++; // Update the count
                    sum += in.val; // Add the new value without subtracting anything
                    result = sum / dataCount; // The new average with the new dataCount
                }


                assert(buffer.push(in)); // Push the latest value

                average = result; // Save the new average

                // Keep the in timestamp for out
                return Value(result, in.timeStamp);
            }
        }
    }
}

