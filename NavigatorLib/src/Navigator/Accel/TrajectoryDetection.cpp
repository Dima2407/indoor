//
// Created by Igor Maschikevich on 6/8/2017.
//

//#pragma once

#include "Navigator/Accel/TrajectoryDetection.h"

namespace Navigator {
namespace Accel {
Math::Position3D TrajectoryDetection::process(const AlgorithmZUPT &velocity)
{
    using namespace Math;

    double posX, posY, posZ;
    Position3D velocityTrajectory(velocity.Vx, velocity.Vy, velocity.Vz);

    //    velocityTrajectory.distance();


    Position3D positionAfter(posX, posY, posZ);
    return positionAfter;
}
}
}
