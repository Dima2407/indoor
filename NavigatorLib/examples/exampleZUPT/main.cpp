//
// Created by Igor Maschikevich on 6/9/2017.
//
#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

// This includes everything you need
#include "Navigator.h"

using namespace std;
using Navigator::Accel::AlgorithmZUPT;
using Navigator::Accel::TrajectoryDetection;
using Navigator::Accel::AccelOutputData;
using Navigator::Math::Position3D;

// Test the AlgorithmZUPT
int main() {
    // AccelOutputData from Victora
    AccelOutputData victor;
    // All enter data in AlgorithmZUPT.h and AlgorithmZUPT.cpp
    AlgorithmZUPT algoritm;
    algoritm.process(victor);
    algoritm.Vx=2;
    algoritm.Vy=2;
        cout<<"Vx "<<algoritm.Vx<<endl;
        cout<<"Vy "<<algoritm.Vy<<endl;
        cout<<"Vz "<<algoritm.Vz<<endl;

    return 0;
}
