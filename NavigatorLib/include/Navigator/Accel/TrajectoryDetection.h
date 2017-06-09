//
// Created by Igor Maschikevich on 6/8/2017.
//
#include "Navigator/Math/Position3D.h"
#include "AccelOutputData.h"
#include "AlgorithmZUPT.h"
#pragma once
namespace Navigator {
namespace Accel {


class TrajectoryDetection
{
public:
    Math::Position3D process(const AlgorithmZUPT &velocity);

    const float X_init = 3.5;
    const float Y_init = 3.5;
    const float adjCoef = 3;

};
}
}
