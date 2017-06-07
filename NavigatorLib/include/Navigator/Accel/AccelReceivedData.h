//
// Created by  Oleksiy Grechnyev on 6/7/2017.
//

#pragma once

namespace Navigator {
    namespace Accel {
        /// Data from accelerometer and sensors (angles)
        struct AccelReceivedData {
            /// Acceleration in g units, g ~= 9.8 m/s^2, check
            double ax, ay, az;
            /// Angles in RADIANS
            double piitch, yaw, roll;
        };
    }
}


