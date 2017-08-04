//
// Created by  Victor Draban on 6/7/2017.
//

#pragma once

#include <cmath>

namespace Navigator {
    namespace Accel {
        /// Data from accelerometer and sensors (angles)
        struct AccelOutputData {

            /// Timestamp in SECONDS
            double timestamp = std::nan("");

            /// Time elapsed since the previods timestamp
            double timeDiff = std::nan("");

            /// Are we "stationary" in the sense of the step-detection algorithm?
            bool isStationary = true;

            /// Acceleration in global coordinates
            double ax = std::nan(""), ay = std::nan(""), az = std::nan("");
            
            /// The processed YAW (=azimuth) angle in radians for the dummy algorithm
            double yaw = std::nan("");

        };
    }
}
