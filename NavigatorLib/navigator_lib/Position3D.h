//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#pragma once

namespace navi_beacon {
    /// Point in 3d space + floor number (optional, when needed)
    struct Position3D {
        double x, y, z;

        unsigned int floor;
    };
}


