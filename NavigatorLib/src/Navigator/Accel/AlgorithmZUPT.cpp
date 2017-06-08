//
// Created by Igor Maschikevich on 6/7/2017.
//

#pragma once

#include "Navigator/Accel/AlgorithmZUPT.h"


namespace Navigator {
namespace Accel {

bool AlgorithmZUPT::isStationary(){
    int a = 1;
    if(a == 0)
        return true;
    else
        return false;
}

Math::Position3D AlgorithmZUPT::process(const AccelOutputData &data)
{
    using namespace Math;

    if (isStationary() == false){
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
    Position3D position3d(Vx, Vy, Vz);
    return position3d;
}

//void AlgorithmZUPT::processTemp(float ax_glob,float ay_glob,float az_glob, bool as, float samplePeriod){
//    using namespace std;
//}
}
}
