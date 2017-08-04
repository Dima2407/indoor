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

            /// The expected gravity along az (+1.0 or -1.0)
            static constexpr double GRAVITY_AZ = +1.0;

            /// The last timestamp before the current one
            double lastTime = std::nan("");

            /// Filters, allocate if needed
            std::unique_ptr<FilterImpl> filterAX, filterAY, filterAZ;
        };
    }
}
