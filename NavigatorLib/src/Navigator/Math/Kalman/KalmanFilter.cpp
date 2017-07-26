//
// Created by  Victor Draban on 7/21/2017.
//

#include <cmath>
#include "Navigator/Math/Kalman/KalmanFilter.h"

namespace Navigator {
    namespace Math {
        namespace Kalman {

            /**
             * @brief KalmanFilter::process
             * @param in
             * @return
             * Application for Kalman's filter for raw RSSI
             * - smoothing of fluctuating RSSI values
             * - the restoration of "missing" packets with indications of the model Kalman filter
             */
            Filter::IFilter::Value KalmanFilter::process(Filter::IFilter::Value in) {
                double val = in.val;
                double deltaT = in.timeStamp - currentTime;
                Eigen::Matrix<double, 2, 2> Ak;
                Ak(0, 0) = 1;
                Ak(0, 1) = deltaT;
                Ak(1, 0) = 0;
                Ak(1, 1) = 1;

                Eigen::Matrix<double, 2, 1> tempX = predictCurrentMoment(Ak);
                Eigen::Matrix<double, 2, 2> tempP = predictError(Ak);
                Eigen::Matrix<double, 2, 1> kalmansCoefficient = correctKalman(tempP);
                correctCurrentMoment(tempX, kalmansCoefficient, val);
                correctError(tempP, kalmansCoefficient);

                currentTime = in.timeStamp;
                return Filter::IFilter::Value(lastX(0,0), currentTime);
            }

            /**
             * @brief KalmanFilter::processOnlyPredict
             * @param timestamp
             * @return
             * Application for Kalman's filter without section "Correct"
             */
            Filter::IFilter::Value KalmanFilter::processOnlyPredict(double timestamp) {
                double deltaT = timestamp - currentTime;
                Eigen::Matrix<double, 2, 2> Ak;
                Ak(0, 0) = 1;
                Ak(0, 1) = deltaT;
                Ak(1, 0) = 0;
                Ak(1, 1) = 1;

                lastX = predictCurrentMoment(Ak);
                lastP = predictError(Ak);

                currentTime = timestamp;
                return Filter::IFilter::Value(lastX(0,0), currentTime);
            }

            /**
            *  @brief KalmanFilter::predictCurrentMoment
            *  @param Ak
            *  this method calculate: in predicting the values ​​of RSSIk and ΔRSSIk
            *  for the current time moment k  from the filter model using the RSSI value,
            *  the previous time point k-1
            */
            Eigen::Matrix<double, 2, 1> KalmanFilter::predictCurrentMoment(const Eigen::Matrix<double, 2, 2>& Ak) {
                return Ak * lastX;
            }

            /**
             * @brief KalmanFilter::predictError
             * @param Ak
             *  this method calculate: In the prediction of the value of the model error
             *  covariance matrix (result) using the matrix value for the previous
             *  time point k-1 and the noise matrix of the filter model (Q)
             */
            Eigen::Matrix<double, 2, 2> KalmanFilter::predictError(const Eigen::Matrix<double, 2, 2>& Ak) {
                return Ak * lastP * Ak.transpose() + config.Q;
            }

            /**
             * @brief KalmanFilter::correctKalman
             * @param tempP
             * @return
             * calculate coefficient Kalmana
             */
            Eigen::Matrix<double, 2, 1> KalmanFilter::correctKalman(const Eigen::Matrix<double, 2, 2>& tempP) {
                double smallExpression = pow((config.H * tempP * config.H.transpose() + config.R), -1);
                return tempP * config.H.transpose() * smallExpression;
            }

            /**
             * @brief KalmanFilter::correctCurrentMoment
             * @param tempX
             * @param kalmansCoefficient
             * @param val
             * calculate values RSSI and ΔRSSI for current time
             * with given predictions
             */
            void KalmanFilter::correctCurrentMoment(Eigen::Matrix<double, 2, 1> tempX,
                                                                           const Eigen::Matrix<double, 2, 1>& kalmansCoefficient,
                                                                           const double val) {
                lastX = tempX + kalmansCoefficient * (val - config.H * lastX);
            }

            /**
             * @brief KalmanFilter::correctError
             * @param tempP
             * @param kalmansCoefficient
             * calculate values of matrix the covariance of the errors model for current time
             */
            void KalmanFilter::correctError(const Eigen::Matrix<double, 2, 2>& tempP,
                                            const Eigen::Matrix<double, 2, 1>& kalmansCoefficient) {
                lastP = (config.I - kalmansCoefficient * config.H) * tempP;
            }
        }
    }
}
