//
// Created by  Victor Draban on 6/7/2017.
//

#include "Navigator/Accel/ToGlobal.h"

namespace Navigator {
namespace Accel {

        AccelOutputData ToGlobal::process(AccelReceivedData data)
        {
            using namespace Eigen;
            TempData tempData;
            AccelOutputData result;

            filteringAccelerations(data, tempData);
            angleCorrection(data, tempData);
            recognazeState(data, tempData);

            Quaternion<double> quat = initQuaternion(tempData.pitch, tempData.roll, tempData.yaw);
            Quaternion<double> invertQuat = quat.conjugate();
            Quaternion<double> r(0, tempData.ax, tempData.ay, tempData.az);

            Quaternion<double> resultQ = quat * r * invertQuat;

            result.ax = resultQ.x();
            result.ay = resultQ.y();
            result.az = resultQ.z();
            result.isStationary = tempData.isStationary;
            result.timestamp = data.timestamp;
            result.timeDiff = 0.3;

            return result;
        }

// =================================================================================

        void ToGlobal::recognazeState(const AccelReceivedData &in, TempData &out) {
            double accTH = 1.035;
            auto a_norm = sqrt(in.ax*in.ax + in.ay*in.ay + in.az*in.az);
            if (a_norm < accTH) {
                out.isStationary = true;
            } else {
                out.isStationary = false;
            }
        }

// =================================================================================

        void ToGlobal::angleCorrection(const AccelReceivedData &in, TempData &out) {
            double mapOrientationAngle = 0;
            out.pitch = in.pitch*(M_PI/180);
            out.roll = in.roll*(M_PI/180);
            out.yaw = (-in.yaw - 180 + mapOrientationAngle)*(M_PI/180);
        }

// =================================================================================

        void ToGlobal::filteringAccelerations(const AccelReceivedData &in, TempData &out) {

        }

// =================================================================================

/*
 *
 *
 * */
         Eigen::Quaternion<double> ToGlobal::initQuaternion(double pitch, double roll, double yaw) {
             double w = cos(pitch/2)*cos(roll/2)*cos(roll/2) -
                     sin(pitch/2)*sin(roll/2)*sin(yaw/2);
             double x = cos(pitch/2)*sin(roll/2)*sin(yaw/2) +
                     sin(pitch/2)*cos(roll/2)*sin(yaw/2);
             double y = cos(pitch/2)*sin(roll/2)*cos(yaw/2) -
                     sin(pitch/2)*cos(roll/2)*sin(yaw/2);
             double z = cos(pitch/2)*cos(roll/2)*sin(yaw/2) +
                     sin(pitch/2)*sin(roll/2)*cos(yaw/2);
             Eigen::Quaternion<double> result(w, x, y, z);
             return result;
         }
    }
}
