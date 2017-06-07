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

            // G = 6.7*18^-11 H*m^2/kg^2
            double ax = std::nan(""), ay = std::nan(""), az = std::nan("");
        };
    }
}
