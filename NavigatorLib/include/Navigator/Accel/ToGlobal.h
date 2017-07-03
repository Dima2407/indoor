//
// Created by  Victor Draban on 6/7/2017.
//

#pragma once

#include <cmath>
#include <vector>
#include <memory>

#include <Eigen/Geometry>

#include "AccelOutputData.h"
#include "AccelConfig.h"
#include "AccelReceivedData.h"
#include "TempData.h"
#include "FilterImpl.h"

namespace Navigator {
    namespace Accel {

        class ToGlobal {

        public:

            ToGlobal(const AccelConfig & config = AccelConfig()) :
                config(config)
            {
                using namespace std;

                // Create filters
                if (config.useFilter) {
                    filterAX = make_unique<FilterImpl>(8, config.a, config.b);
                    filterAY = make_unique<FilterImpl>(8, config.a, config.b);
                    filterAZ = make_unique<FilterImpl>(8, config.a, config.b);
                }
            }

            /// Process a data packet
            AccelOutputData process(const AccelReceivedData & data);

            /// Create a local->global rotation quaternion
            Eigen::Quaternion<double> initQuaternion(double pitch, double roll, double yaw);

        private: // ============= Methdos =============

            /// Create TempData: angle to radians, apply map orientation angle
            void angleCorrection(const AccelReceivedData &in, TempData &out);

            /// Filter the acceleration if config.useFilter == true
            void filterAccelerations(TempData &out);

            /// Detect steps and set  out.isStationary accordingly
            void recognizeStep(TempData &out);

            /// Rotate acceleration to global coordinates using angles
            void rotateAccelerations(TempData &out);

        private: // ============== Data ===============

            /// Configuration
            AccelConfig config;

            /// The last timestamp before the current one
            double lastTime = std::nan("");

//            std::vector<double> const a{1, -5.6403125091553754, 14.179734483869705, -20.695873101662205,
//                                        19.142583364228241, -11.472236200051777, 4.344994383668622,
//                                        -0.94986943840591642, 0.0916890050488007};


//            std::vector<double> const b{2.7733888284864122E-6, 2.2187110627891297E-5, 7.7654887197619541E-5,
//                                        0.00015530977439523908, 0.00019413721799404885, 0.00015530977439523908,
//                                        7.7654887197619541E-5, 2.2187110627891297E-5, 2.7733888284864122E-6};


            /// Filters, allocate if needed
            std::unique_ptr<FilterImpl> filterAX, filterAY, filterAZ;
        };
    }
}
