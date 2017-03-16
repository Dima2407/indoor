//
// Created by  Oleksiy Grechnyev on 2/8/2017.
//

#ifndef TESTTOOL_VEC3T_H
#define TESTTOOL_VEC3T_H

#include <iostream>
#include "Vec3.h"


namespace tester {
    /// A Vec3 r + time t
    class Vec3t {
    public:
        /// Time
        double t;
        /// Position
        Vec3 r;

        /// Deaful constrcutor
        Vec3t() {}

        /// tr constrcutor
        Vec3t(double t, const Vec3 &r) : t(t), r(r) {}

        /// txyz constrcutor
        Vec3t(double t, double x, double y, double z) : t(t), r(x, y, z) {}

        /// Write to osteam
        friend std::ostream &operator<<(std::ostream &os, const Vec3t &vt);

        /// Read from istream
        friend std::istream &operator>>(std::istream &is, Vec3t &vt);

        /// The compare operator, order by time t, might use it for sorting
        bool operator<(const Vec3t &rhs) const{
            return t < rhs.t;
        }
    };
}


#endif //TESTTOOL_VEC3T_H
