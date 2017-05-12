//
// Created by  Oleksiy Grechnyev on 3/11/2017.
//

#include "Navigator/Math/Filter/AlphaBetaFilter.h"

namespace Navigator {
    namespace Math {
        namespace Filter {

            IFilter::Value AlphaBetaFilter::process(IFilter::Value in) {
                double x = 0; // The result (new position)
                double v = 0; // The new velocity

                if (initialized) {
                    // This IS NOT the first data value
                    // Update x,v

                    // Linear update
                    x = x0 + v0 * DT;
                    v = v0;

                    // Adjust x, v based on the value of in
                    double residue = in.val - x;

                    x += alpha * residue;
                    v += beta * residue / DT;
                } else {
                    // This IS the first data value
                    // Initialize
                    x = in.val;
                    v = 0;
                    initialized = true; // Set the initialized flag HERE
                }

                // Replace the previos data with the current one
                x0 = x;
                v0 = v;

                return Value(x, in.timeStamp);
            }
        }
    }
}