//
// Created by  Oleksiy Grechnyev on 6/7/2017.
//

#pragma once

#include <cmath>


namespace Navigator {
    namespace Accel {
        /// Data from accelerometer and sensors (angles)
        struct AccelReceivedData {

            /// Timestamp in SECONDS since an arbitrary origin
            double timestamp = std::nan("");

            /// Acceleration in g units, g ~= 9.8 m/s^2, relative to the Phone's XYZ axes
            double ax = std::nan(""), ay = std::nan(""), az = std::nan("");

            /// Euler Angles in RADIANS
            double pitch = std::nan(""), yaw = std::nan(""), roll = std::nan("");
        };
    }
}


