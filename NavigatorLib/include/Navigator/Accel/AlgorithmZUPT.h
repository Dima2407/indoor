//
// Created by Igor Maschikevich on 6/7/2017.
//
#pragma once

#include "Navigator/Math/Position3D.h"
#include "AccelOutputData.h"

namespace Navigator {
namespace Accel {
class AlgorithmZUPT
{
public:
    Math::Position3D process(const AccelOutputData &data);

    static constexpr double maxV = 3.5;
    static constexpr double globG = 9.8066;

    // Default data
    double Vx = 0.0;
    double Vy = 0.0;
    double Vz = 0.0;

};
}
}
