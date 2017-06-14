//
// Created by  Victor Draban on 6/7/2017.
//

#pragma once

#include <cmath>

#include <Eigen/Geometry>

#include "AccelOutputData.h"
#include "AccelReceivedData.h"
#include "TempData.h"

namespace Navigator {
    namespace Accel {

        class ToGlobal {

        public:
            static constexpr double ACC_TH = 1.035;

            ToGlobal(double mapOrientationAngle = 0.0) : mapOrientationAngle(mapOrientationAngle) {}

            AccelOutputData process(AccelReceivedData data);

            Eigen::Quaternion<double> initQuaternion(double pitch, double roll, double yaw);

        private:
            void recognizeState(const AccelReceivedData &in, TempData &out);

            void angleCorrection(const AccelReceivedData &in, TempData &out);

            void filteringAccelerations(const AccelReceivedData &in, TempData &out);

            double mapOrientationAngle;

            double lastTime = std::nan("");
        };
    }
}
