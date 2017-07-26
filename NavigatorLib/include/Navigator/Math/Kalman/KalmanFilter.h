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
                Value processOnlyPredict(double timestamp);

            private:
                Eigen::Matrix<double, 2, 1> predictCurrentMoment(const Eigen::Matrix<double, 2, 2>& Ak);
                Eigen::Matrix<double, 2, 2> predictError(const Eigen::Matrix<double, 2, 2>& Ak);

                Eigen::Matrix<double, 2, 1> correctKalman(const Eigen::Matrix<double, 2, 2>& tempP);
                void correctCurrentMoment(Eigen::Matrix<double, 2, 1> tempX,
                                                                 const Eigen::Matrix<double, 2, 1>& kalmansCoefficient,
                                                                 const double val);
                void correctError(const Eigen::Matrix<double, 2, 2>& tempP,
                                                         const Eigen::Matrix<double, 2, 1>& kalmansCoefficient);

                KalmanConfig config;
                double currentTime = 0;
                Eigen::Matrix<double, 2, 1> lastX;
                Eigen::Matrix<double, 2, 2> lastP;
            };
        }
    }
}
