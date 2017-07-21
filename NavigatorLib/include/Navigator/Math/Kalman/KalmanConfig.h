//
// Created by Victor Draban on 7/21/2017.
//

#pragma once

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
                int beaconsN = 1;

                /**
                 *  @brief x_many
                 *  this array holds parameters RSSI and dRSSI of each beacons
                 **/
                double[2][beaconsN] x_many = {{0}};

                /**
                 *  @brief p_many
                 *  this array holds values matrix P for each beacons
                 **/
                double [4][beaconsN] p_many = {{0}};

                /**
                 *  @brief timer
                 *  array of counters that hold information about last time of change
                 **/
                double[1][beaconsN] timer;

                /**
                 *  @brief P_INIT
                 *  start values covariant matrix
                 **/
                constexpr int[][] P_INIT = {{100, 0}, {0, 100}};

                /**
                 *  @brief Q
                 *  Variance of process model noise
                 **/
                constexpr double[][] Q = {{0.001, 0}, {0, 0.001}};

                /**
                 *  @brief R
                 *  The value of the variance of the noise of the changes
                 **/
                constexpr double R = 0.1;

                /**
                 *  @brief timeout
                 *  if new packets from beacons don't come, will be use
                 *  last value at the end of out
                 **/
                constexpr double timeout = 1.5;

                /**
                 *  @brief H
                 *  matrix of identity
                 **/
                constexpr int[] H = {1, 0};

                /**
                 *  @brief I
                 *  unit matrix
                 **/
                constexpr int[][] I = {{1, 0}, {0,1}};
            };
        }
    }
}
