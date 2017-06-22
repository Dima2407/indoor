//
// Created by  Victor Draban on 6/7/2017.
//

#pragma once

#include <cmath>

#include <Eigen/Geometry>
#include <vector>

#include "AccelOutputData.h"
#include "AccelReceivedData.h"
#include "TempData.h"
#include "FilterImpl.h"

namespace Navigator {
    namespace Accel {

        class ToGlobal {

        public:
            static constexpr double ACC_TH = 1.035;

            ToGlobal(double mapOrientationAngle = 0.0) : mapOrientationAngle(mapOrientationAngle) {}

            AccelOutputData process(const AccelReceivedData & data);

            Eigen::Quaternion<double> initQuaternion(double pitch, double roll, double yaw);

        private:
            void recognizeState(const AccelReceivedData &in, TempData &out);

            void angleCorrection(const AccelReceivedData &in, TempData &out);

            void filteringAccelerations(const AccelReceivedData &in, TempData &out);

            double mapOrientationAngle;

            double lastTime = std::nan("");

            std::vector<double> const a{1, -5.6403125091553754, 14.179734483869705, -20.695873101662205,
                                        19.142583364228241, -11.472236200051777, 4.344994383668622,
                                        -0.94986943840591642, 0.0916890050488007};

            std::vector<double> const b{2.7733888284864122E-6, 2.2187110627891297E-5, 7.7654887197619541E-5,
                                        0.00015530977439523908, 0.00019413721799404885, 0.00015530977439523908,
                                        7.7654887197619541E-5, 2.2187110627891297E-5, 2.7733888284864122E-6};
            FilterImpl filterAX{8, a, b};
            FilterImpl filterAY{8, a, b};
            FilterImpl filterAZ{8, a, b};
        };
    }
}
