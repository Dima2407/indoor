//
// Created by  Victor Draban on 7/21/2017.
//

#include <cmath>
#include "Navigator/Math/Kalman/KalmanFilter.h"

namespace Navigator {
    namespace Math {
        namespace Kalman {
            Filter::IFilter::Value KalmanFilter::process(Filter::IFilter::Value in) {
                double val = in.val;
                double deltaT = in.timeStamp - currentTime;
                Eigen::Matrix<double, 2, 2> Ak;
                Ak(0, 0) = 1;
                Ak(0, 1) = deltaT;
                Ak(1, 0) = 0;
                Ak(1, 1) = 1;

                predictCurrentMoment(Ak);
                predictError(Ak);
                Eigen::Matrix<double, 2, 1> kalmansCoefficient = correctKalman();
                Eigen::Matrix<double, 2, 1> currentX = correctCurrentMoment(val, kalmansCoefficient);
                Eigen::Matrix<double, 2, 2> currentP = correctError(kalmansCoefficient);

                currentTime = in.timeStamp;
                predictX = currentX;
                predictP = currentP;
            }

            /**
            *  @brief KalmanFilter::predictCurrentMoment
            *  @param Ak
            *  this method calculate: in predicting the values ​​of RSSIk and ΔRSSIk
            *  for the current time moment k  from the filter model using the RSSI value,
            *  the previous time point k-1
            */
            void KalmanFilter::predictCurrentMoment(const Eigen::Matrix<double, 2, 2>& Ak) {
                Eigen::Matrix<double, 2, 1> xk1(rssi(0, 0), rssi(1, 0));
                predictX = Ak * xk1;
            }

            /**
             * @brief KalmanFilter::predictError
             * @param Ak
             *  this method calculate: In the prediction of the value of the model error
             *  covariance matrix (result) using the matrix value for the previous
             *  time point k-1 and the noise matrix of the filter model (Q)
             */
            void KalmanFilter::predictError(const Eigen::Matrix<double, 2, 2>& Ak) {
                predictP = Ak * predictP * Ak.transpose() + config.Q;
            }

            /**
             * @brief KalmanFilter::correctKalman
             * @return
             * calculate coefficient Kalmana
             */
            Eigen::Matrix<double, 2, 1> KalmanFilter::correctKalman() {
                double smallExpression = pow((config.H * predictP * config.H.transpose() + config.R), -1);
                return predictP * config.H.transpose() * smallExpression;
            }

            /**
             * @brief KalmanFilter::correctCurrentMoment
             * @param val
             * @param kalmansCoefficient
             * @return
             * calculate values RSSI and ΔRSSI for current time
             * with given predictions
             */
            Eigen::Matrix<double, 2, 1> KalmanFilter::correctCurrentMoment(const double val,
                                                    const Eigen::Matrix<double, 2, 1>& kalmansCoefficient) {
                return predictX + kalmansCoefficient * (val - config.H * predictX);
            }

            /**
             * @brief KalmanFilter::correctError
             * @param kalmansCoefficient
             * @return
             * calculate values of matrix the covariance of the errors model for current time
             */
            Eigen::Matrix<double, 2, 2> KalmanFilter::correctError(const Eigen::Matrix<double, 2, 1>& kalmansCoefficient) {
                return (config.I - kalmansCoefficient * config.H) * predictP;
            }
        }
    }
}
