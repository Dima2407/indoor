//
// Created by Igor Maschikevich on 6/7/2017.
//

#pragma once

#include "Navigator/Accel/AlgorithmZUPT.h"


namespace Navigator {
namespace Accel {

Math::Position3D AlgorithmZUPT::process(const AccelOutputData &data)
{
    using namespace Math;
    //     must add Victor algoritm
//        double ax_glob=5, ay_glob=5, az_glob=2;
        double ax_glob=0.111,ay_glob=0.2333,az_glob=0.1;
        bool isStationary=true;

    //    if (&data.isStationary() == false){
    if (isStationary == false){
        Vx = Vx + consG * ax_glob * samplePeriod;
        Vy = Vy + consG * ay_glob * samplePeriod;
        Vz = Vz + consG * az_glob * samplePeriod;
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
