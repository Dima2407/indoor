//
// Created by  Oleksiy Grechnyev on 2/7/2017.
//

#include "LinearTrajectory.h"

namespace tester {

    Vec3 LinearTrajectory::trajectory(double t) const{
        // Linear at present
        return point1 * ((t2 - t) / (t2 - t1)) + point2 * ((t - t1) / (t2 - t1));
    }
}