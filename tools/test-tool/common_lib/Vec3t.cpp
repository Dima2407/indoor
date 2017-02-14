//
// Created by  Oleksiy Grechnyev on 2/8/2017.
//

#include "Vec3t.h"

#include <iomanip>

namespace tester {

    std::ostream & operator<<(std::ostream &os, const Vec3t &vt) {
        os << std::setw(12) <<  vt.t << " " << std::setw(12) << vt.r;
        return os;
    }

    std::istream &operator>>(std::istream &is, Vec3t &vt) {
        is >> vt.t >> vt.r;
        return is;
    }

}