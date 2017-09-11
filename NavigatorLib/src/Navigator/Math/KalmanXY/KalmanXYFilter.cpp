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

            Math::Position2D KalmanXYFilter::process(const Math::Position2D &location,
                                     const std::vector<Math::Position2D> distances) {
                if (!isInitialized) {
                    lastX << 0, 0;
                    lastP = config.matrixInitP;
                    isInitialized = true;
                    return Math::Position2D(lastX(0,0), lastX(1,0));
                }

                Eigen::Matrix<double, 1, 2> locationXY(location.x, location.y);
                Eigen::Matrix<double, 3, 2> distanceToBeacons;
                for (int i = 0; i < 3; ++i) {
                    distanceToBeacons << distances[i].x;
                    distanceToBeacons << distances[i].y;
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

//                return Eigen::Matrix<double, 1, 2>(lastX(0,0), lastX(1,0));
                return Math::Position2D(lastX(0,0), lastX(1,0));
            }


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
                return tempP * matrixH.transpose() * expression.inverse();
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
