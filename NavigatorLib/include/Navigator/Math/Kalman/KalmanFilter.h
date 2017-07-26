//
// Created by Victor Draban on 7/21/2017.
//

#pragma once

#include "KalmanConfig.h"
#include "Navigator/Math/Filter/IFilter.h"

namespace Navigator {
    namespace Math {
        namespace Kalman {
            class KalmanFilter: public Filter::IFilter {

            public:
                KalmanFilter(const KalmanConfig& config = KalmanConfig()) :
                    config(config)
                {
                    rssi << 0, 0;
                }

                Value process(Value in) override;

            private:
                void predictCurrentMoment(const Eigen::Matrix<double, 2, 2>& Ak);
                void predictError(const Eigen::Matrix<double, 2, 2>& Ak);

                Eigen::Matrix<double, 2, 1> correctKalman();
                Eigen::Matrix<double, 2, 1> correctCurrentMoment(const double val, const Eigen::Matrix<double, 2, 1>& kalmansCoefficient);
                Eigen::Matrix<double, 2, 2> correctError(const Eigen::Matrix<double, 2, 1>& kalmansCoefficient);

                KalmanConfig config;
                Eigen::Matrix<double, 2, 1> rssi;
                double currentTime = 0;
                Eigen::Matrix<double, 2, 1> predictX;
                Eigen::Matrix<double, 2, 2> predictP;
            };
        }
    }
}
