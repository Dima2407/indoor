//
// Created by  Victor Draban on 6/7/2017.
//

#pragma once

#include <cmath>

namespace Navigator {
    namespace Accel {
        /// Data from accelerometer and sensors (angles)
        struct AccelOutputData {

            double timestamp = std::nan("");

            double timeDiff = std::nan("");

            bool isStationary = true;

            double ax = std::nan(""), ay = std::nan(""), az = std::nan("");

        };
    }
}
