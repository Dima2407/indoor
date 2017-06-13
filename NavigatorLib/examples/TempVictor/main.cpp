//
// Created by  Victor Draban on 6/9/2017.
//
#include <iostream>
#include "Navigator/Accel/ToGlobal.h"
using namespace std;
using namespace Navigator;
using namespace Accel;
using namespace Eigen;

// Test Quaternion
int main(){

        double pitch = 0.2;
        double roll = 0.3;
        double yaw = 0.4;
        ToGlobal global;
        Quaternion<double> q1 = global.initQuaternion(pitch, roll, yaw);
        cout << "it's normalize = " << q1.norm() << endl;
        cout << "test" << endl;

        return 0;
}
