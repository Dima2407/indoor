//
// Created by  Oleksiy Grechnyev on 3/24/2017.
//

#pragma once

namespace Navigator {
    namespace Beacons {
        namespace Calibrate {

            /// Calibration configuration data
            struct CalibrationConfig {
                /**
                 *
                 */
                enum class Mode {ONE_POINT, ONE_POINT_D, ONE_POINT_TEST, GRADIENT, MEAN_SQUARE};

                // ===Line-of-sight (LOS) data===

                /// Max distance (e.g. 5 meters)
                double maxDist;
                /// Parameter k of line-of-sight
                double kLos;
                /// Parameter b of LOS
                double bLos;

                /// Calibration mode
                Mode mode;

                /// Average 50/50 with previous calibration ?

                bool averageWithPrevious;

                // Initial/default txPower and damp

                /// Initial txPower
                double initTxPower;

                /// Initial damp
                double initDamp;

                // Gradient descent parameters



            };

        }
    }
}

