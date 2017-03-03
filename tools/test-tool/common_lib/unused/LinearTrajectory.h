//
// Created by  Oleksiy Grechnyev on 2/7/2017.
//

#ifndef TESTTOOL_LINEARTRAJECTORY_H
#define TESTTOOL_LINEARTRAJECTORY_H

#include "Vec3.h"

namespace tester {
    /** \brief Linear trajectory from t1, point1 to t2, point2
     *
     */
    class LinearTrajectory {
    public:
        /// Calculate the linear trajectory Vec3(t)
        Vec3 trajectory(double t) const;

        /// Start and finish of our route
        Vec3 point1, point2;
        /// Start and finish time in arbitrary units (e.g. seconds)
        double t1, t2;
    };
}


#endif //TESTTOOL_LINEARTRAJECTORY_H
