//
// Created by  Oleksiy Grechnyev on 8/9/2017.
//
#include "Navigator/Math/Position3D.h"


namespace Navigator {
    namespace Math {

        Position2D::operator Position3D() const {
            return Position3D(x, y, 0);
        }

        Position3D::operator Position2D() const {
            return Position2D(x, y);
        }
    }
}