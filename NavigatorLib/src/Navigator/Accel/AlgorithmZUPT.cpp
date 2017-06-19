//
// Created by Igor Maschikevich on 6/7/2017.
//


#include "Navigator/Accel/AlgorithmZUPT.h"


namespace Navigator {
namespace Accel {

Math::Position3D AlgorithmZUPT::process(const AccelOutputData &data)
{
    using namespace Math;

    if (data.isStationary == false){
        double dt = data.timeDiff;
        Vx = Vx + globG * data.ax * dt;
        Vy = Vy + globG * data.ay * dt;
        Vz = Vz + globG * data.az * dt;
    }
    else{
        Vx = Vy = Vz = 0;
    }
    if (Vx > maxV){
        Vx = maxV;
    }
    if (Vy > maxV){
        Vy = maxV;
    }
    if (Vz > maxV){
        Vz = maxV;
    }
    Position3D velocity(Vx, Vy, Vz);
    return velocity;
}

}
}
