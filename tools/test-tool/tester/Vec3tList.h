//
// Created by  Oleksiy Grechnyev on 2/8/2017.
//

#ifndef TESTTOOL_VEC3TLIST_H
#define TESTTOOL_VEC3TLIST_H

#include <vector>
#include <string>

#include "Vec3t.h"

namespace tester {
    /// Vec3t list with IO
    class Vec3tList {
    public:

        /// Write the list to DAT file, return true if success
        bool writeDAT(std::string const & fileName);

        /// Getter
        const std::vector<Vec3t> &getPoints() const {
            return points;
        }

        /// Non-const Getter
        std::vector<Vec3t> &getPoints() {
            return points;
        }

        /// Clear the list
        void clear(){
            points.clear();
        }

    private:
        std::vector<Vec3t> points;
    };
}


#endif //TESTTOOL_VEC3TLIST_H
