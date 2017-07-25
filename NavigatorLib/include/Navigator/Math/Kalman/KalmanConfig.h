//
// Created by Victor Draban on 7/21/2017.
//

#pragma once

#include <vector>
#include <Eigen/Dense>

namespace Navigator {
    namespace Math {
        namespace Kalman {
            /**
             * @brief The KalmanConfig struct
             * Started configuration for Kalman's Filter
             */
            struct KalmanConfig {

                KalmanConfig() {
//                    x_many(10);
                    P_INIT << 100, 0,
                              0, 100;
                    Q << 0.001, 0,
                         0, 0.001;
                    H << 1, 0;
                    I << 1, 0,
                         0, 1;
                }

                /**
                 *  @brief x_many
                 *  this Matrix holds parameters RSSI and dRSSI of each beacons
                 **/
                double currentRssi = 0;
                double rssiPrev = 0;

                double currentDeltaRssi = 0;
                double deltaRssiPrev = 0;

                /**
                 *  @brief timer
                 *  array of counters that hold information about last time of change
                 **/
                double timer = 0;

                /**
                 *  @brief P_INIT
                 *  start values covariant matrix
                 **/
                Eigen::Matrix<double, 2, 2> P_INIT;

                /**
                 *  @brief Q
                 *  Variance of process model noise
                 **/
                Eigen::Matrix<double, 2, 2> Q;

                /**
                 *  @brief R
                 *  The value of the variance of the noise of the changes
                 **/
                double R = 0.1;

                /**
                 *  @brief timeout
                 *  if new packets from beacons don't come, will be use
                 *  last value at the end of out
                 **/
                double timeout = 1.5;

                /**
                 *  @brief H
                 *  matrix of identity
                 **/
                Eigen::Matrix<double, 1, 2> H;

                /**
                 *  @brief I
                 *  unit matrix
                 **/
                Eigen::Matrix<double, 2, 2> I;
            };
         }
    }
}
