//
// Created by  Oleksiy Grechnyev on 3/24/2017.
//
#include <cmath>

#include "Navigator/Beacons/Calibrate/Algorithm/algorithm.h"

namespace Navigator {
    namespace Beacons {
        namespace Calibrate {
            namespace Algorithm {
//================================================================================

                void calibrate(const CalibrationTable &table, const CalibrationConfig config, double &txPower,
                               double &damp) {
                    using namespace std;

                    if (table.size() == 0) {
                        // Empty table, nothing to do
                        txPower = nan("");
                        damp = nan("");

                    } else if (table.size() == 1) {
                        // Use 1-point calibration. BAD ! D-version currently.
                        calibrateOnePointD(table[0].first, table[0].second, config, txPower, damp);

                    } else {
                        // Linear Least squares calibration
                        calibrateLeastSquares(table, txPower, damp);
                    }

                }
//================================================================================

                void calibrateOnePointG(double dist, double rssi, const CalibrationConfig config, double &txPower,
                                        double &damp) {

                }
//================================================================================

                void calibrateOnePointD(double dist, double rssi, const CalibrationConfig config, double &txPower,
                                        double &damp) {

                    if (dist==1.0) {
                        txPower = std::nan("");
                        damp = std::nan("");
                        return;
                    }

                    // Set default TxPower
                    txPower = config.initTxPower;

                    // Find damp from the rssi formula
                    damp = (txPower - rssi) / (10 * std::log10(dist));

                    // Set nan if failure
                    if (std::isnan(damp))
                        txPower = std::nan("");
                }
//================================================================================

                void leastSquares(const std::vector<double> &x, const std::vector<double> &y, double &a, double &b) {
                    int n = x.size(); // Number of input points

                    // This version requires at least 2 data points
                    if (n<2 || n!=y.size()) {
                        a = std::nan("");
                        b = a;
                        return ;
                    }

                    // Find average x,y
                    double xAvg = 0, yAvg = 0;

                    for (int i = 0; i < n; ++i) {
                        xAvg += x[i];
                        yAvg += y[i];
                    }
                    xAvg /= n;
                    yAvg /= n;

                    double c1 = 0, c2 = 0;
                    // Find a, b
                    for (int i = 0; i < n; ++i) {
                        c1 += (x[i] - xAvg) * (y[i] - yAvg);
                        c2 += (x[i] - xAvg) * (x[i] - xAvg);
                    }

                    // The only way you can get nan here is if
                    // c2 = 0, i.e. all x[i] are equal
                    a = c1 / c2;
                    b = yAvg - a*xAvg;
                }
//================================================================================

                void calibrateLeastSquares(const CalibrationTable &table, double &txPower, double &damp) {
                    using namespace std;

                    // data for leastSquares
                    vector<double> x, y;
                    double a, b;

                    // Theory: we seek the dependence
                    // R = T - 10*n*log10(d)
                    // R = RSSI, T= TxPower, n = damp, d = distance (meters)
                    // We use the linear least squares y = a*x +b
                    // with y=R, x=log10(d), a = -10*n, b = T

                    // Loop over pairs
                    for (const auto & val: table) {
                        x.push_back(log10(val.first));  // log10(dist)
                        y.push_back(val.second); // RSSI
                    }

                    leastSquares(x, y, a, b);  // Find a, b

                    txPower = b;
                    damp = - a/10;
                }
//================================================================================


            }
        }
    }
}
