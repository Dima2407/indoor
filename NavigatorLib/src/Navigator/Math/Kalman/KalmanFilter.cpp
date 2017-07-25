//
// Created by  Victor Draban on 7/21/2017.
//

#include <cmath>
#include "Navigator/Math/Kalman/KalmanFilter.h"

namespace Navigator {
    namespace Math {
        namespace Kalman {




        Filter::IFilter::Value KalmanFilter::process(Filter::IFilter::Value in) {
            double deltaT = in.timeStamp - currentTime;
            Eigen::Matrix<double, 2, 2> Ak;
            Ak(0, 0) = 1;
            Ak(0, 1) = deltaT;
            Ak(1, 0) = 0;
            Ak(1, 1) = 1;

            predictCurrentMoment(Ak);
            predictError(Ak);
            Eigen::Matrix<double, 2, 1> K = correctKalman(config.H);
        }


        /**
        *  @brief KalmanFilter::predictCurrentMoment
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
         *  this method calculate: In the prediction of the value of the model error
         *  covariance matrix (result) using the matrix value for the previous
         *  time point k-1 and the noise matrix of the filter model (Q)
         */
        void KalmanFilter::predictError(const Eigen::Matrix<double, 2, 2>& Ak) {
            predictP = Ak * predictP * Ak.transpose() + config.Q;
        }

        /**
         * @brief KalmanFilter::correctKalman
         * @param H
         * @return
         *  calculate coefficient Kalmana
         */
        Eigen::Matrix<double, 2, 1> KalmanFilter::correctKalman(const Eigen::Matrix<double, 1, 2>& H) {
            double m = pow((H * predictP * H.transpose() + config.R), -1);
            Eigen::Matrix<double, 2, 1> result = predictP * H.transpose() * m;
        }



        }
    }
}
