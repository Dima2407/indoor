//
// Created by  Oleksiy Grechnyev on 2/3/2017.
//

#include <iostream>
#include "Vec3.h"

namespace faker {

    Vec3 &Vec3::operator+=(const Vec3 &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    const Vec3 Vec3::operator+(const Vec3 &rhs) const {
        Vec3 result = *this; // Clone
        result += rhs;
        return result;
    }


    Vec3 &Vec3::operator*=(const double rhs) {
        x *= rhs;
        y *= rhs;
        z *= rhs;
        return *this;
    }


    const Vec3 Vec3::operator*(const double rhs) const {
        Vec3 result = *this; // Clone
        result *= rhs;
        return result;
    }

    std::istream &operator>>(std::istream &is, Vec3 &vec3) {
        is >> vec3.x >> vec3.y >> vec3.z;
        return is;
    }

    std::ostream &operator<<(std::ostream &os, const Vec3 &vec3) {
        os << vec3.x << " " << vec3.y << " " << vec3.z;
        return os;
    }


}