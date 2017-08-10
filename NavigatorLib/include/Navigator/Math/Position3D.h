//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#pragma once

#include <cmath>
#include <limits>

namespace Navigator {
    namespace Math {

        struct Position3D;

        /// Point in 2-dimension space
        struct Position2D {
        public:
            /// Constructors
            Position2D(double x, double y)
                    : x(x), y(y) {}

            Position2D() = default;

            // Type cast
            operator Position3D() const;

            Position2D &operator+=(const Position2D &rhs) {
                x += rhs.x;
                y += rhs.y;
                return *this;
            }

            double abs() {
                return sqrt(x * x + y * y);
            }

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

            // Type cast
            operator Position2D() const;

        public:  // == VARIABLES / FIELDS ==
            double x = nan("");
            double y = nan("");
            double z = nan("");
            
        public:  // == METHODS ==
            /// Calculate distance to other point/position
            double distance(Position3D const& p2) const{
                return sqrt(pow(this->x - p2.x, 2) + pow(this->y - p2.y, 2) + pow(this->z - p2.z, 2));
            }
            
            /// Contains one or more wrong values
            bool isFinite(){
                using std::isfinite;
                return isfinite(x) && isfinite(y) && isfinite(z);
            }
            bool isWrong(){ return !isFinite(); };

            /// Approx. equality between 2 points
            bool approx_equals(Position3D const& other, double precision) const{
            	using std::abs;
                return  (abs(x-other.x) <= precision) &&
                        (abs(y-other.y) <= precision) &&
                        (abs(z-other.z) <= precision);
            }
            
        public:  // == OPERATORS ==
            bool operator==(Position3D const& other) const {
                return x==other.x && y==other.y && z==other.z;
            }
        };


        //-------------------------------------------


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


