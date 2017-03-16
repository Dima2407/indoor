//
// Created by  Oleksiy Grechnyev on 3/11/2017.
//

#include "Navigator/Math/Filter/AlphaBetaFilter.h"

namespace Navigator {
    namespace Math {
        namespace Filter {

            double AlphaBetaFilter::process(double in) {
                double x = 0; // The result (new position)
                double v = 0; // The new velocity

                if (initialized) {
                    // This IS NOT the first data value
                    // Update x,v

                    // Linear update
                    x = x0 + v0 * DT;
                    v = v0;

                    // Adjust x, v based on the value of in
                    double residue = in - x;

                    x += alpha * residue;
                    v += beta * residue / DT;
                } else {
                    // This IS the first data value
                    // Initialize
                    x = in;
                    v = 0;
                    initialized = true; // Set the initialized flag HERE
                }

                // Replace the previos data with the current one
                x0 = x;
                v0 = v;

                return x;
            }
        }
    }
}