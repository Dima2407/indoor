//
// Created by  Victor Draban on 6/7/2017.
//
#pragma once

#include "Navigator/Accel/ToGlobal.h"
#include <Eigen/Geometry>


namespace Navigator {
namespace Accel {

        AccelOutputData Navigator::Accel::ToGlobal::process(AccelReceivedData data)
        {
            using namespace Eigen;
            AccelReceivedData result = data;
            filteringAccelerations(result);
            angleCorrection(result);
            recognazeState(result);

            Quaternion<double> quat = initQuaternion(result.pitch, result.roll, result.yaw);
            Quaternion<double> invertQuat = quat.conjugate();
            Quaternion<double> r(0, result.ax, result.ay, result.az);

            return result;
        }

// =================================================================================

        void recognazeState(const AccelOutputData &data) {
            double accTH = 1.035;
            auto a_norm = sqrt(data.ax*data.ax + data.ay*data.ay + data.az*data.az);
            if (a_norm < accTH) {
                data.isStationary = false;
            } else {
                data.isStationary = true;
            }
        }

// =================================================================================

        void angleCorrection(const AccelReceivedData &data) {
            doubel mapOrientationAngle = 0;
            data.pitch = data.pitch*(pi/180);
            data.roll = data.roll*(pi/180);
            data.yaw = (-data.yaw - 180 + mapOrientationAngle)*(pi/180);
        }

// =================================================================================

        void filteringAccelerations(const AccelReceivedData &data) {
            return data;
        }

    }

// =================================================================================

         Quaternion<double> initQuaternion(double pitch, double roll, double yaw) {
             doubl w = cos(pitch/2)*cos(roll/2)*cos(roll/2) -
                     sin(pitch/2)*sin(roll/2)*sin(yaw/2);
             doubl x = cos(pitch/2)*sin(roll/2)*sin(yaw/2) +
                     sin(pitch/2)*cos(roll/2)*sin(yaw/2);
             doubl y = cos(pitch/2)*sin(roll/2)*cos(yaw/2) -
                     sin(pitch/2)*cos(roll/2)*sin(yaw/2);
             doubl z = cos(pitch/2)*cos(roll/2)*sin(yaw/2) +
                     sin(pitch/2)*sin(roll/2)*cos(yaw/2);
             Quaternion<double> result(w, x, y, z);
             return result;
         }
}
