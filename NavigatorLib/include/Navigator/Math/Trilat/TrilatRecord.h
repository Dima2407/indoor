//
// Created by  Oleksiy Grechnyev on 3/29/2017.
//

#pragma once

#include <cmath>


#include "Navigator/Math/Position3D.h"


namespace Navigator {
    namespace Math {
        namespace Trilat {

            /// Data record (position, distance) used for trilateration
            struct TrilatRecord {
                TrilatRecord(const Position3D &pos, double dist) : pos(pos), dist(dist) {}

                TrilatRecord() {}

                /// Relation for sorting
                bool operator<(const TrilatRecord &rhs) const {
                    return dist < rhs.dist;
                }

                Position3D pos;
                double dist = std::nan("");
            };

        }
    }
}

