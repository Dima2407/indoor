//
// Created by  Victor Draban on 6/7/2017.
//

#include <iostream>
#include "Navigator/Accel/ToGlobal.h"

namespace Navigator {
namespace Accel {

        AccelOutputData ToGlobal::process(const AccelReceivedData & data)
        {
            using namespace Eigen;
            TempData tempData;
            AccelOutputData result;

            filteringAccelerations(data, tempData);
            angleCorrection(data, tempData);
            recognizeState(data, tempData);

            result.isStationary = tempData.isStationary;

            if (!result.isStationary) {
                Quaternion<double> quat = initQuaternion(tempData.pitch, tempData.roll, tempData.yaw);
                Quaternion<double> invertQuat = quat.conjugate();
                Quaternion<double> r(0, tempData.ax, tempData.ay, tempData.az);

                Quaternion<double> resultQ = quat * r * invertQuat;

                result.ax = resultQ.x();
                result.ay = resultQ.y();
                result.az = resultQ.z()-1;
            } else {
                result.ax = 0;
                result.ay = 0;
                result.az = 0;
            }

            result.timestamp = data.timestamp;
            if (std::isnan(lastTime)) {
                result.timeDiff = 0;
            } else {
                result.timeDiff = result.timestamp - lastTime;
            }
            lastTime = result.timestamp;
            return result;
        }

// =================================================================================

        void ToGlobal::recognizeState(const AccelReceivedData &in, TempData &out) {
            auto a_norm = sqrt(in.ax*in.ax + in.ay*in.ay + in.az*in.az);
            if (a_norm < ACC_TH) {
                out.isStationary = true;
            } else {
                out.isStationary = false;
            }
        }

// =================================================================================

        void ToGlobal::angleCorrection(const AccelReceivedData &in, TempData &out) {
            out.pitch = in.pitch*(M_PI/180);
            out.roll = in.roll*(M_PI/180);
            out.yaw = (-in.yaw - 180 + mapOrientationAngle)*(M_PI/180);
        }

// =================================================================================

        void ToGlobal::filteringAccelerations(const AccelReceivedData &in, TempData &out) {
            if (useFilter) {
                out.ax = filterAX.process({in.ax, in.timestamp}).val;
                out.ay = filterAY.process({in.ay, in.timestamp}).val;
                out.az = filterAZ.process({in.az, in.timestamp}).val;
            } else {
                out.ax = in.ax;
                out.ay = in.ay;
                out.az = in.az;
            }
        }

// =================================================================================

/*
 *
 *
 * */
         Eigen::Quaternion<double> ToGlobal::initQuaternion(double pitch, double roll, double yaw) {
             double w = cos(pitch/2)*cos(roll/2)*cos(yaw/2) - sin(pitch/2)*sin(roll/2)*sin(yaw/2);
             double x = cos(pitch/2)*sin(roll/2)*sin(yaw/2) + sin(pitch/2)*cos(roll/2)*cos(yaw/2);
             double y = cos(pitch/2)*sin(roll/2)*cos(yaw/2) - sin(pitch/2)*cos(roll/2)*sin(yaw/2);
             double z = cos(pitch/2)*cos(roll/2)*sin(yaw/2) + sin(pitch/2)*sin(roll/2)*cos(yaw/2);
             return Eigen::Quaternion<double>(w, x, y, z);
         }
    }
}
