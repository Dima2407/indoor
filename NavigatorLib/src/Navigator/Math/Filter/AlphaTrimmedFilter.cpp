//
// Created by  Oleksiy Grechnyev on 4/3/2017.
//

#include <vector>
#include <algorithm>


#include "Navigator/Math/Filter/AlphaTrimmedFilter.h"

namespace Navigator {
    namespace Math {
        namespace Filter {


            IFilter::Value AlphaTrimmedFilter::process(IFilter::Value in) {
                using namespace std;

                if (buffer.size() == winSize) {
                    // Buffer full, we need to pop before we push anything
                    IFilter::Value temp;

                    assert(buffer.pop(temp));
                }

                // Push the new value
                buffer.push(in);

                // Number of available elements
                unsigned size = buffer.size();

                // How many min and max elements to skip ?
                unsigned nskip = (unsigned) alpha*size;

                if (2*nskip == size)
                    nskip--; // You cannot skip everything

                // For now: ignore timestamps
                // Array of last size items
                vector<double> data;

                // Copy data into this array
                for (unsigned i = 0; i < size; i++) {
                    Value temp;
                    assert(buffer.peek(i, temp));
                    data.push_back(temp.val);
                }

                if (nskip > 0) {
                    // Sort data only if non-zero skip
                    sort(data.begin(), data.end());
                }

                // Calculate sum of all non-skipped data
                double sum = 0;
                for (unsigned i = nskip; i < size-nskip; i++)
                    sum += data[i];

                double result = sum / (size - 2*nskip);
                // Keep the in timestamp for out
                return Value(result, in.timeStamp);
            }
        }
    }
}