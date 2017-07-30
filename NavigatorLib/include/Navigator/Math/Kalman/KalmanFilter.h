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

                /**
                 * @brief KalmanFilter::process
                 * @param in
                 * @return
                 * Application for Kalman's filter for raw RSSI
                 * - smoothing of fluctuating RSSI values
                 * - the restoration of "missing" packets with indications of the model Kalman filter
                 */
                Value process(Value in) override;

                /**
                 * @brief KalmanFilter::processOnlyPredict
                 * @param timestamp
                 * @return
                 * Application for Kalman's filter without section "Correct"
                 */
                Value processOnlyPredict(double timestamp);

            private:

                /**
                *  @brief KalmanFilter::predictCurrentMoment
                *  @param Ak
                *  this method calculate: in predicting the values ​​of RSSIk and ΔRSSIk
                *  for the current time moment k  from the filter model using the RSSI value,
                *  the previous time point k-1
                */
                Eigen::Matrix<double, 2, 1> predictCurrentMoment(const Eigen::Matrix<double, 2, 2>& Ak);

                /**
                 * @brief KalmanFilter::predictError
                 * @param Ak
                 *  this method calculate: In the prediction of the value of the model error
                 *  covariance matrix (result) using the matrix value for the previous
                 *  time point k-1 and the noise matrix of the filter model (Q)
                 */
                Eigen::Matrix<double, 2, 2> predictError(const Eigen::Matrix<double, 2, 2>& Ak);

                /**
                 * @brief KalmanFilter::correctKalman
                 * @param tempP
                 * @return
                 * calculate coefficient Kalmana
                 */
                Eigen::Matrix<double, 2, 1> correctKalman(const Eigen::Matrix<double, 2, 2>& tempP);

                /**
                 * @brief KalmanFilter::correctCurrentMoment
                 * @param tempX
                 * @param kalmansCoefficient
                 * @param val
                 * calculate values RSSI and ΔRSSI for current time
                 * with given predictions
                 */
                void correctCurrentMoment(Eigen::Matrix<double, 2, 1> tempX,
                                                                 const Eigen::Matrix<double, 2, 1>& kalmansCoefficient,
                                                                 const double val);

                /**
                 * @brief KalmanFilter::correctError
                 * @param tempP
                 * @param kalmansCoefficient
                 * calculate values of matrix the covariance of the errors model for current time
                 */
                void correctError(const Eigen::Matrix<double, 2, 2>& tempP,
                                                         const Eigen::Matrix<double, 2, 1>& kalmansCoefficient);

                bool isInitialize = false;
                KalmanConfig config;
                double lastTime;
                double lastPacketTime;
                Eigen::Matrix<double, 2, 1> lastX;
                Eigen::Matrix<double, 2, 2> lastP;
            };
        }
    }
}
