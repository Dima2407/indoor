//
// Created by  Victor Draban on 6/7/2017.
//

#pragma once

#include "AccelOutputData.h"
#include "AccelReceivedData.h"
#include "TempData.h"
#include <Eigen/Geometry>

namespace Navigator {
    namespace Accel {

        class ToGlobal {

        public:
            AccelOutputData process(AccelReceivedData data);

            Eigen::Quaternion<double> initQuaternion(double pitch, double roll, double yaw);

        private:
            void recognazeState(const AccelReceivedData &in, TempData &out);

            void angleCorrection(const AccelReceivedData &in, TempData &out);

            void filteringAccelerations(const AccelReceivedData &in, TempData &out);


        };
    }
}
