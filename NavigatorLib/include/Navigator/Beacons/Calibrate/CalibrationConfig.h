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
                CalibrationConfig(double maxDist, double kLos, double bLos, double initTxPower, double initDamp)
                        : maxDist(maxDist),
                          kLos(kLos),
                          bLos(bLos),
                          initTxPower(initTxPower),
                          initDamp(initDamp) {}

                // Constructor with all defaults
                CalibrationConfig() {}

                // ===Line-of-sight (LOS) data===
                // Note: changed at some point since the 1st version
                // LOS equation: rssi = k*10*log10(dist) + b
                // smaller rssi (after averaging) are discarded

                /// Max distance (e.g. 6 meters)
                double maxDist = 6.0;
                /// Parameter k of line-of-sight
                double kLos = -2.021;
                /// Parameter b of LOS
                double bLos = -74.21;

                /// Initial/ default txPower
                double initTxPower = -70.0;

                /// Initial/default damp
                double initDamp = 2.2;


                // ===== This is used to set a common z-coordinate to all input points

                bool useCommonZ = false;
                double commonZ = 1.5;

                // ===== This should not be normally used !!!! ====
                // This is for Alexey Roienko so-called "gradient decent" and such


                // So-called "Gradient descent" parameters
                double gradMu = 0.01;
                double gradEps = 1.0e-5;
                int gradMaxSteps = 10000;

            };

        }
    }
}

