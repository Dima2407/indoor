//
// Created by  Victor Draban on 7/21/2017.
//

#include "Navigator/Math/Kalman/KalmanFilter.h"

namespace Navigator {
    namespace Math {
        namespace Kalman {

        /**
        *  @brief KalmanFilter::predictCurrentMoment
        *  this method calculate: in predicting the values ​​of RSSIk and ΔRSSIk
        *  for the current time moment k  from the filter model using the RSSI value,
        *  the previous time point k-1
        */
        void KalmanFilter::predictCurrentMoment() {
            double rssiPred = config.x_many(0, 1);
            double rssiBeforPred = config.x_many(0, 2);

            double deltaRssiPred = rssiPred - rssiBeforPred;
            Eigen::Matrix<double, 2, 1> xk1(rssiPred, deltaRssiPred);
//            double xk1[2][1] = {{rssiPred}, {deltaRssiPred}};

            double deltaT = config.x_many(0, 0) - config.x_many(1, 0);
            Eigen::Matrix<double, 2, 2> Ak;
            Ak(0, 0) = 1;
            Ak(0, 1) = deltaT;
            Ak(1, 0) = 0;
            Ak(1, 1) = 1;
//            double Ak[2][2] = {{1, deltaT},{0, 1}};

//            double result[2][1] = {{Ak[0][0]*xk1[0][0] + Ak[0][1]*xk1[1][0]},
//                                   {Ak[1][0]*xk1[0][0] + Ak[1][1]*xk1[1][0]}};
        }

        /**
         * @brief KalmanFilter::predictError
         *  this method calculate: In the prediction of the value of the model error
         *  covariance matrix (result) using the matrix value for the previous
         *  time point k-1 and the noise matrix of the filter model (Q)
         */
        void KalmanFilter::predictError() {
            double deltaT = config.x_many(0, 0) - config.x_many(1, 0);
            Eigen::Matrix<double, 2, 2> Ak;
            Ak(0, 0) = 1;
            Ak(0, 1) = deltaT;
            Ak(1, 0) = 0;
            Ak(1, 1) = 1;
//            double ak[2][2] = {{1, deltaT}, {0, 1}};
//            Eigen::Matrix<double, 2, 2> transparentAk = ak.transpose();
//            double transparentAk[2][2];
//            for (int i = 0; i < 2; ++i) {
//                for (int j = 0; j < 2; ++j) {
//                    transparentAk[j][i] = ak[i][j];
//                }
//            }
//            double P[2][2] = config.P_INIT;
//            Eigen::Matrix<double, 2, 2> pPred(config.p_many(0, 1), config.p_many(1, 1),
//                               config.p_many(2, 1), config.p_many(3, 1));
            Eigen::Matrix<double, 2, 2> pPred;
            pPred(0, 0) = config.p_many(0, 1);
            pPred(0, 1) = config.p_many(1, 1);
            pPred(1, 0) = config.p_many(2, 1);
            pPred(1, 1) = config.p_many(3, 1);
//            double result[2][2] = ak * pPred * transparentAk + config.Q;
            Eigen::Matrix<double, 2, 2> result = Ak * pPred * Ak.transpose() + config.Q;

        }

        }
    }
}
