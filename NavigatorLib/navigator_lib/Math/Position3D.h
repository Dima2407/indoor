//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#pragma once

#include <cmath>

namespace Navi {
    namespace Math {
        /// Point in 3d space + floor number (optional, when needed)
        struct Position3D {
            /// Constructors
            Position3D(double x, double y, double z, unsigned int floor = 0) : x(x), y(y), z(z), floor(floor) {}

            Position3D() {}


            double x = nan("");
            double y = nan("");
            double z = nan("");

            unsigned int floor = 0;
        };
    }
}


