//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#pragma once

#include <cmath>

namespace navi {
    namespace beacon {
        /// Point in 3d space + floor number (optional, when needed)
        struct Position3D {
            double x = nan("");
            double y = nan("");
            double z = nan("");

            unsigned int floor = 0;
        };
    }
}


