//
// Created by  Oleksiy Grechnyev on 3/24/2017.
//

#pragma once

namespace Navigator {
    namespace Beacons {
        namespace Calibrate {

            /// Calibration configuration data
            struct CalibrationConfig {

                // Constructor
                CalibrationConfig(double maxDist, double kLos, double bLos, double initTxPower) :
                        maxDist(maxDist),
                        kLos(kLos),
                        bLos(bLos),
                        initTxPower(initTxPower) {}

                // Constructor with all defaults
                CalibrationConfig() {}

                // ===Line-of-sight (LOS) data===

                /// Max distance (e.g. 5 meters)
                double maxDist = 5.0;
                /// Parameter k of line-of-sight
                double kLos = -3.074;
                /// Parameter b of LOS
                double bLos = -72.88;

                /// Initial/ default txPower
                double initTxPower = -70.0;

                // ===== This should not be used !!!! ====
                // This is for Alexey Roienko so-called "gradient decent" and such

                /// Initial/default damp
                double initDamp = 2.0;

                // Gradient descent parameters


            };

        }
    }
}

