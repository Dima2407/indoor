//
// Created by  Oleksiy Grechnyev on 3/24/2017.
//
#include <cmath>

#include "Navigator/Beacons/Calibrate/Algorithm/algorithm.h"

namespace Navigator {
    namespace Beacons {
        namespace Calibrate {
            namespace Algorithm {

                void calibrate(const CalibrationTable &table, const CalibrationConfig config, double &txPower,
                               double &damp) {

                    double newTxPower, newDamp; // New values of damp* txpower

                    if (table.size() == 0) return; // Empty table, nothing to do

                    if (config.mode == CalibrationConfig::Mode::ONE_POINT ||
                        config.mode == CalibrationConfig::Mode::ONE_POINT_D ||
                        config.mode == CalibrationConfig::Mode::ONE_POINT_TEST ||
                        table.size() == 1) {
                        // Perform one-point calibration
                        // We run the average of damp & txPower over all points
                        double sumTxPower = 0, sumDamp = 0;

                        // Loop over all pairs dist, rssi
                        for (const auto &val: table) {
                            double tempTxPower, tempDamp;

                            // Choose one of the 1-point routines
                            // Note: ONE_POINT_D is default is table.size() == 1

                            if (config.mode == CalibrationConfig::Mode::ONE_POINT)
                                calibrateOnePoint(val.first, val.second, config, tempTxPower, tempDamp);
                            else if (config.mode == CalibrationConfig::Mode::ONE_POINT_TEST)
                                calibrateOnePointTest(val.first, val.second, config, tempTxPower, tempDamp);
                            else
                                calibrateOnePointD(val.first, val.second, config, tempTxPower, tempDamp);


                            sumTxPower += tempTxPower;
                            sumDamp += tempDamp;
                        }

                        // New txpower
                        newTxPower = sumTxPower / table.size();
                        newDamp = sumDamp / table.size();

                    }


                    if (config.averageWithPrevious) {
                        // Average with previous
                        txPower = (txPower + newTxPower) / 2;
                        damp = (damp + newDamp) / 2;

                    } else {
                        // Pure new
                        txPower = newTxPower;
                        damp = newDamp;
                    }
                }

                void calibrateOnePoint(double dist, double rssi, const CalibrationConfig config, double &txPower,
                                       double &damp) {

                }

                void calibrateOnePointD(double dist, double rssi, const CalibrationConfig config, double &txPower,
                                        double &damp) {
                    // Set default TxPower
                    txPower = config.initTxPower;

                    // Find damp from the rssi formula
                    damp = (txPower - rssi) / (10 * std::log10(dist));
                }

                void calibrateOnePointTest(double dist, double rssi, const CalibrationConfig config, double &txPower,
                                           double &damp) {
                    // Set default TxPower
                    txPower = config.initTxPower;

                    // Set default damp
                    damp = config.initDamp;
                }


            }
        }
    }
}
