//
// Created by  Oleksiy Grechnyev on 3/24/2017.
//

#pragma once

#include <utility>
#include <vector>

#include "Navigator/Beacons/Calibrate/CalibrationConfig.h"

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

                /** @brief Calibrate using one-point calibration method
                 *
                 *  Note: I follow the exact strange algorithm of Alexey Roienko
                 *
                 * @param[in]       dist      Distance
                 * @param[in]       rssi      RSSI
                 * @param[in]       config    Configuration data
                 * @param[out]      txPower   Result: txPower
                 * @param[out]      damp      Result: damp
                 */
                void calibrateOnePoint(double dist,
                                       double rssi,
                                       const CalibrationConfig config,
                                       double &txPower,
                                       double &damp);

                /** @brief Calibrate using one-point calibration method
                 *
                 *  Note: This version finds damp only, using default txPower
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

                /** @brief Calibrate using one-point calibration method
                 *
                 *  Test version, returns default damp  and default txPower
                 *
                 * @param[in]       dist      Distance
                 * @param[in]       rssi      RSSI
                 * @param[in]       config    Configuration data
                 * @param[out]      txPower   Result: txPower
                 * @param[out]      damp      Result: damp
                 */
                void calibrateOnePointTest(double dist,
                                           double rssi,
                                           const CalibrationConfig config,
                                           double &txPower,
                                           double &damp);
            }
        }
    }
}