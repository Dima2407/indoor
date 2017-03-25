//
// Created by  Oleksiy Grechnyev on 3/24/2017.
//

#pragma once

#include <utility>
#include <vector>

#include "Navigator/Beacons/Calibrate/CalibrationConfig.h"

/** @file algorith.h
 *  @brief Algorithms for calibration
 *
 *  Note: the basic formula for RSSI is
 *
 *  R = T - 10*n*log10(d) , where
 *
 *  R = RSSI, T= TxPower, n = damp, d = distance (meters)
 *  The coefficient 10 comes from decibels
 */

namespace Navigator {
    namespace Beacons {
        namespace Calibrate {
            namespace Algorithm {

                /// The table of calibration data
                using CalibrationTable = std::vector<std::pair<double, double>>;

                /** @brief  Calibrate one beacon from a table
                 *
                 * @param[in]       table     Input data : table of dist : rssi
                 * @param[in]       config    Configuration data
                 * @param[in, out]  txPower   Result: txPower
                 * @param[in, out]  damp      Result: damp
                 */
                void calibrate(const CalibrationTable &table,
                               const CalibrationConfig config,
                               double &txPower,
                               double &damp);

                /** @brief Linear least square fit with the formula y = a*x + b
                 *
                 *  This version requires at least 2 data points
                 *  Gives nan, nan if anything is wrong
                 * @param[in]  x
                 * @param[in]  y
                 * @param[out] a
                 * @param[out] b
                 */
                void leastSquares(const std::vector<double> &x,
                                  const std::vector<double> &y,
                                  double &a,
                                  double &b);


                /**  @brief Calibrate using least squares
                 *
                 *   Gives nan, nan if less than 2 data points
                 *
                 * @param[in]   table
                 * @param[out]  txPower
                 * @param[out]  damp
                 */
                void calibrateLeastSquares(const CalibrationTable &table,
                               double &txPower,
                               double &damp);

                /** @brief Calibrate using one-point calibration method
                 *
                 *  Note: I follow the exact strange algorithm of Alexey Roienko
                 *  The so-called gradient descent
                 *
                 * @param[in]       dist      Distance
                 * @param[in]       rssi      RSSI
                 * @param[in]       config    Configuration data
                 * @param[out]      txPower   Result: txPower
                 * @param[out]      damp      Result: damp
                 */
                void calibrateOnePointG(double dist,
                                        double rssi,
                                        const CalibrationConfig config,
                                        double &txPower,
                                        double &damp);

                /** @brief Calibrate using one-point calibration method
                 *
                 *  Note: This version finds damp only, using default txPower
                 *  Warning : can give negative damp !!!
                 *  Should we exclude negative damp ?
                 *
                 * @param[in]       dist      Distance
                 * @param[in]       rssi      RSSI
                 * @param[in]       config    Configuration data
                 * @param[out]      txPower   Result: txPower
                 * @param[out]      damp      Result: damp
                 */
                void calibrateOnePointD(double dist,
                                        double rssi,
                                        const CalibrationConfig config,
                                        double &txPower,
                                        double &damp);


            }
        }
    }
}