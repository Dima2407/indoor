//
// Created by  Oleksiy Grechnyev on 2/3/2017.
//

#ifndef TESTERALL_VEC3_H
#define TESTERALL_VEC3_H

#include <iostream>
#include <cmath>

namespace tester {
    /** \brief A 3-vector (x, y, z)
     *
     * I probably could have found a ready-made one, but I needed an exercize in C++
     */
    class Vec3 {
    public:
        /// Coordinates
        double x, y, z;

        /// Constructors
        Vec3(double x, double y, double z) : x(x), y(y), z(z) {}

        Vec3() {}

        /// Vector length
        double len(){
            return std::sqrt(x*x + y*y +z*z);
        }

        /// Operations Vec3 +- Vec3 and Vec3 * double
        Vec3 &operator+=(const Vec3 &rhs);
        Vec3 &operator-=(const Vec3 &rhs);

        const Vec3 operator+(const Vec3 &rhs) const;
        const Vec3 operator-(const Vec3 &rhs) const;

        Vec3 &operator*=(const double rhs);

        const Vec3 operator*(const double rhs) const;

        /// Write to ostream
        friend std::ostream &operator<<(std::ostream &os, const Vec3 &vec3);

        /// Read from istream
        friend std::istream &operator>>(std::istream &is, Vec3 &vec3);
    };
}


#endif //TESTERALL_VEC3_H
