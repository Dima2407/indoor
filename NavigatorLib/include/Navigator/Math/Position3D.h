//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#pragma once

#include <cmath>
#include <limits>
//#include <gmpxx.h>

namespace Navigator {
    namespace Math {
    
        /// Point in 2-dimension space
        struct Position2D {
            /// Constructors
            Position2D(double x, double y)
                    : x(x), y(y) {}
    
            Position2D() {}
        
            double x = nan("");
            double y = nan("");
        };
        
        
        /// Point in 3d space
        struct Position3D
        {
        public:  // == CONSTRUCTORS ==
            Position3D(double x, double y, double z)
                    : x(x), y(y), z(z) {}

            Position3D() = default;

        public:  // == VARIABLES / FIELDS ==
            double x = nan("");
            double y = nan("");
            double z = nan("");
            
        public:  // == METHODS ==
            /// Calculate distance to ather point/position
            double distance(Position3D const& p2) const{
                return sqrt(pow(this->x - p2.x, 2) + pow(this->y - p2.y, 2));
            }
            
            /// Contains one or more wrong values
            bool isFinite(){
                using std::isfinite;
                return isfinite(x) && isfinite(y) && isfinite(z);
            }
            bool isWrong(){ return !isFinite(); };
        };
        
        
        /// Point in 3d space + floor number (optional, may be will be needed)
        struct Position3DFloor : Position3D
        {
        public:  // == CONSTRUCTORS ==
            Position3DFloor(double x, double y, double z, unsigned int floor)
                    : Position3D(x,y,z)
                    , floor(floor) {}
            
            using Position3D::Position3D;  // inherit constructor
    
            Position3DFloor() {}
        
        public:  // == VARIABLES / FIELDS ==
            unsigned int floor = std::numeric_limits<unsigned int>::min();  // UNUSED
        };
    }
}


