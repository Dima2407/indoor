//
// Created by  Victor Draban on 6/7/2017.
//

#include <iostream>
#include <vector>
#include "Navigator/Accel/ToGlobal.h"

namespace Navigator {
namespace Accel {

// =================================================================================

AccelOutputData ToGlobal::process(const AccelReceivedData & data)
{
    TempData tempData;
    AccelOutputData result;

    // Create tempData, angle to radians
    angleCorrection(data, tempData);

    // Rotate accel to global coords
    rotateAccelerations(tempData);
    // To left-hand XY coordinate system because of maps
    tempData.ay = - tempData.ay;

    // Filter if needed
    filterAccelerations(tempData);

    // The "recognize step" algorithm
    recognizeStep(tempData);

    // Copy data to result. No more angles !
    result.isStationary = tempData.isStationary;
    result.ax = tempData.ax;
    result.ay = tempData.ay;
    result.az = tempData.az;
    result.timestamp = data.timestamp;

    // Calculate time elapsed since the previous packet
    if (std::isnan(lastTime)) {
        result.timeDiff = 0;
    } else {
        result.timeDiff = result.timestamp - lastTime;
    }
    lastTime = result.timestamp;

    return result;
}

// =================================================================================

void ToGlobal::recognizeStep(TempData &out) {
    auto a_norm = sqrt(out.ax*out.ax + out.ay*out.ay + out.az*out.az) - 1.0;
    out.isStationary = (a_norm < config.accThreshold);
}

// =================================================================================

void ToGlobal::angleCorrection(const AccelReceivedData &in, TempData &out) {
    // Angle to radians + map orientation
    out.pitch = in.pitch*(M_PI/180);
    out.roll = in.roll*(M_PI/180);
    out.yaw = (in.yaw + config.mapOrientationAngle)*(M_PI/180);

    // Don't forget to copy accelerations and timestamp also
    out.ax = in.ax;
    out.ay = in.ay;
    out.az = in.az;
    out.timestamp = in.timestamp;
}

// =================================================================================

void ToGlobal::filterAccelerations(TempData &out) {
    if (config.useFilter) {
        out.az += 1.0; // Exclude gravity

        out.ax = filterAX->process({out.ax, out.timestamp}).val;
        out.ay = filterAY->process({out.ay, out.timestamp}).val;
        out.az = filterAZ->process({out.az, out.timestamp}).val;

        out.az -= 1.0; // Put the gravity back again
    }
}

// =================================================================================
void ToGlobal::rotateAccelerations(TempData &out)
{
    using namespace Eigen;

    Quaternion<double> quat = initQuaternion(out.pitch, out.roll, out.yaw);
    Quaternion<double> invertQuat = quat.conjugate();
    Quaternion<double> r(0, out.ax, out.ay, out.az);

    Quaternion<double> resultQ = quat * r * invertQuat;

    out.ax = resultQ.x();
    out.ay = resultQ.y();
    out.az = resultQ.z();
}


// =================================================================================

Eigen::Quaternion<double> ToGlobal::initQuaternion(double pitch, double roll, double yaw) {
    double w = cos(yaw/2)*cos(pitch/2)*cos(roll/2) - sin(yaw/2)*sin(pitch/2)*sin(roll/2);
    double x = cos(yaw/2)*sin(pitch/2)*cos(roll/2) - sin(yaw/2)*cos(pitch/2)*sin(roll/2);
    double y = cos(yaw/2)*cos(pitch/2)*sin(roll/2) + sin(yaw/2)*sin(pitch/2)*cos(roll/2);
    double z = cos(yaw/2)*sin(pitch/2)*sin(roll/2) + sin(yaw/2)*cos(pitch/2)*cos(roll/2);

    return Eigen::Quaternion<double>(w, x, y, z);
}

}
}
