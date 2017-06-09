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

    // page 8
    const float maxV = 3.5;
    const float consG = 9.8066;

    // page 9
    const float samplePeriod = 0.033;

    // Default data
    const float Vx = 0.0;
    const float Vy = 0.0;
    const float Vz = 0.0;

};
}
}
