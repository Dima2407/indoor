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
                {}

                Value process(Value in) override;

            private:
                void predictCurrentMoment(const Eigen::Matrix<double, 2, 2>& Ak);
                void predictError(const Eigen::Matrix<double, 2, 2>& Ak);

                Eigen::Matrix<double, 2, 1> correctKalman(const Eigen::Matrix<double, 1, 2>& H);
                void correctCurrentMoment();
                void correctError();

                KalmanConfig config;
                Eigen::Matrix<double, 2, 1> rssi;
                double currentTime = 0;
                Eigen::Matrix<double, 2, 1> predictX;
                Eigen::Matrix<double, 2, 2> predictP;
            };
        }
    }
}
