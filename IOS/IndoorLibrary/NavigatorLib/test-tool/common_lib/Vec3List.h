//
// Created by  Oleksiy Grechnyev on 2/6/2017.
//

#ifndef TESTTOOL_VEC3LIST_H
#define TESTTOOL_VEC3LIST_H

#include <vector>
#include <string>

#include "Vec3.h"

namespace tester {
    /// A list of Vec3 with IO
    class Vec3List {
    public:

        /// Write points to a DAT file (true if successful)
        bool writeDAT(std::string const & fileName);

        /// Getter
        const std::vector<Vec3> &getPoints() const {
            return points;
        }

        /// Getter with non-constant value
        std::vector<Vec3> &getPoints() {
            return points;
        }

        /// Clear the list
        void clear(){
            points.clear();
        }

    private:
        std::vector<Vec3> points;
    };
}


#endif //TESTTOOL_VEC3LIST_H
