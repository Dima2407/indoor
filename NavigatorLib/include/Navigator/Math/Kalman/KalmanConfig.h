//
// Created by Victor Draban on 7/21/2017.
//

#pragma once

#include <Eigen/Dense>

namespace Navigator {
    namespace Math {
        namespace Kalman {
            /**
             * @brief The KalmanConfig struct
             * Started configuration for Kalman's Filter
             */
            struct KalmanConfig {
                /**
                 * @brief beaconsN
                 * count of beakons
                 */
                static const int beaconsN = 1;

                /**
                 *  @brief x_many
                 *  this array holds parameters RSSI and dRSSI of each beacons
                 **/
//                double x_many[2][beaconsN] = {{0}};
                Eigen::Matrix<double, 2, beaconsN> x_many;

                /**
                 *  @brief p_many
                 *  this array holds values matrix P for each beacons
                 **/
//                double p_many[4][beaconsN] = {{0}};
                Eigen::Matrix<double, 4, beaconsN> p_many;

                /**
                 *  @brief timer
                 *  array of counters that hold information about last time of change
                 **/
                double timer[beaconsN];

                /**
                 *  @brief P_INIT
                 *  start values covariant matrix
                 **/
//                double P_INIT[2][2] = {{100, 0}, {0, 100}};
                Eigen::Matrix<double, 2, 2> P_INIT;

                /**
                 *  @brief Q
                 *  Variance of process model noise
                 **/
//                double Q[2][2] = {{0.001, 0}, {0, 0.001}};
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
                int H[2] = {1, 0};
//                Eigen::Matrix<double, 1, 0> H;

                /**
                 *  @brief I
                 *  unit matrix
                 **/
//                int I[2][2] = {{1, 0}, {0,1}};
                Eigen::Matrix<double, 2, 2> I;
            };
         }
    }
}
