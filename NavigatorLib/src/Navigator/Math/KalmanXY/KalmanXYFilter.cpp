//
// Created by  Victor Draban on 7/21/2017.
//

#include <iostream>
#include <iomanip>
#include <cmath>
#include "Navigator/Math/KalmanXY/KalmanXYFilter.h"
using namespace std;
namespace Navigator {
    namespace Math {
        namespace KalmanXY {

            Eigen::Matrix<double, 1, 2> KalmanXYFilter::process(const Eigen::Matrix<double, 1, 2> &locationXY,
                                                                const Eigen::Matrix<double, 3, 2> &distanceToBeacons) {
                if (!isInitialized) {
                    lastX << 0, 0;
                    lastP = config.matrixInitP;
                    isInitialized = true;
                    return lastX;
                }

                Eigen::Matrix<double, 1, 2> dtb1 = helpExpression(distanceToBeacons(0,0), distanceToBeacons(0, 1));
                Eigen::Matrix<double, 1, 2> dtb2 = helpExpression(distanceToBeacons(1,0), distanceToBeacons(1, 1));
                Eigen::Matrix<double, 1, 2> dtb3 = helpExpression(distanceToBeacons(2,0), distanceToBeacons(2, 1));

                Eigen::Matrix<double, 3, 2> matrixH;
                matrixH << dtb1(0,0), dtb1(0,1),
                           dtb2(0,0), dtb2(0,1),
                           dtb3(0,0), dtb3(0,1);

                predictCurrentMoment();
                predictError();
                Eigen::Matrix<double, 2, 3> kalmansCoefficient = correctKalman(distanceToBeacons, matrixH);
                correctCurrentMoment(locationXY, kalmansCoefficient, matrixH);
                correctError(kalmansCoefficient, matrixH);

                return Eigen::Matrix<double, 1, 2>(0, 0);
            }

            // -----------------

//            Filter::IFilter::Value KalmanXYFilter::processOnlyPredict(double timestamp) {
//                if (timestamp - lastPacketTime > config.timeout) {
////                    isInitialized = false;
//                    lastTime = timestamp;
//                    return Filter::IFilter::Value(lastX(0,0), timestamp);
//                }
//                double deltaT = timestamp - lastTime;
//                Eigen::Matrix<double, 2, 2> Ak;
//                Ak(0, 0) = 1;
//                Ak(0, 1) = deltaT;
//                Ak(1, 0) = 0;
//                Ak(1, 1) = 1;

//                lastX = predictCurrentMoment(Ak);
//                lastP = predictError(Ak);
//                tempX = lastX;
//                tempP = lastP;

//                lastTime = timestamp;
//                return Filter::IFilter::Value(lastX(0,0), timestamp);
//            }

            // ------------ private -----------------

            void KalmanXYFilter::predictCurrentMoment() {
                tempX = config.matrixAk * lastX;
            }

            // -----------------

            void KalmanXYFilter::predictError() {
                tempP = config.matrixAk * lastP * config.matrixAk.transpose() + config.matrixQ;
            }

            // -----------------

            Eigen::Matrix<double, 2, 3> KalmanXYFilter::correctKalman(const Eigen::Matrix<double, 3, 2> &distanceToBeacons,
                                                                      const Eigen::Matrix<double, 3, 2> &matrixH) {
                Eigen::Matrix<double, 3, 3> expression = matrixH * tempP * matrixH.transpose() + config.matrixR;
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        expression(i, j) = pow(expression(i, j), -1);
                    }
                }       // maybe need refactor, maybe exist standart function in eigen lib... i didn't found
                return tempP * matrixH.transpose() * expression;
            }

            // -----------------

            void KalmanXYFilter::correctCurrentMoment(const Eigen::Matrix<double, 1, 2> &locationXY,
                                                      const Eigen::Matrix<double, 2, 3> &kalmansCoefficient,
                                                      const Eigen::Matrix<double, 3, 2> &matrixH) {
                lastX = tempX + kalmansCoefficient * (matrixH * locationXY.transpose() - matrixH * tempX);
            }

            // -----------------

            void KalmanXYFilter::correctError(const Eigen::Matrix<double, 2, 3>& kalmansCoefficient,
                                              const Eigen::Matrix<double, 3, 2> &matrixH) {
                lastP = (config.matrixI - kalmansCoefficient * matrixH) * tempP;

            }

            Eigen::Matrix<double, 1, 2> KalmanXYFilter::helpExpression(double x, double y) {
                double top = tempX(0, 0) - x;
                double bottom = sqrt(pow(tempX(0, 0) - x, 2) + pow(tempX(1, 0) - y, 2));
                double dSa_Dx = top/bottom;
                top = tempX(1, 0) - y;
                double dSa_Dy = top/bottom;
                return Eigen::Matrix<double, 1, 2>(dSa_Dx, dSa_Dy);
            }
        }
    }
}
