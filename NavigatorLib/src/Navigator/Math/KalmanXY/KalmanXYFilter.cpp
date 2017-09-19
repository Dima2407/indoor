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
                                     const std::vector<Math::Position2D> beacPosition) {
                if (!isInitialized) {
                    lastX(0,0) = location.x;
                    lastX(1,0) = location.y;
                    lastP = config.matrixInitP;
                    isInitialized = true;
                    return location;
                }

                Eigen::Matrix<double, 1, 2> locationXY(location.x, location.y);
                Eigen::Matrix<double, 3, 2> posBeacons;

                // Check that we have exactly 3 beacons
                if (beacPosition.size() != 3)
                    throw runtime_error("KalmanXYFilter::process : beacPosition.size() != 3 !");

                for (int i = 0; i < 3; ++i) {
                    posBeacons(i, 0) = beacPosition[i].x;
                    posBeacons(i, 1) = beacPosition[i].y;
                }

                Eigen::Matrix<double, 1, 2> dtb1 = helpExpression(location, posBeacons(0,0), posBeacons(0, 1));
                Eigen::Matrix<double, 1, 2> dtb2 = helpExpression(location, posBeacons(1,0), posBeacons(1, 1));
                Eigen::Matrix<double, 1, 2> dtb3 = helpExpression(location, posBeacons(2,0), posBeacons(2, 1));

                Eigen::Matrix<double, 3, 2> matrixH;
                matrixH << dtb1(0,0), dtb1(0,1),
                           dtb2(0,0), dtb2(0,1),
                           dtb3(0,0), dtb3(0,1);

                predictCurrentMoment();
//                cout << "tempX = \n" << tempX << endl;
//                cout << " tempX(0,0) = " << tempX(0,0) << " tempX(1,0) = " << tempX(1,0) << endl;

                predictError();
//                cout << "tempP = \n" << tempP << endl;
//                std::cout << " tempP(0,0) = " << tempP(0,0) << " tempP(0,1) = " << tempP(0,1)
//                             << " tempP(1,0) = " << tempP(1,0) << " tempP(1,1) = " << tempP(1,1) << std::endl;

                Eigen::Matrix<double, 2, 3> kalmansCoefficient = correctKalman(posBeacons, matrixH);
                correctCurrentMoment(locationXY, kalmansCoefficient, matrixH);
                correctError(kalmansCoefficient, matrixH);

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

            Eigen::Matrix<double, 1, 2> KalmanXYFilter::helpExpression(const Math::Position2D &location,
                                                                       double x, double y) {
                double top = location.x - x;
                double bottom = sqrt(pow(location.x - x, 2) + pow(location.y - y, 2));
                double dSa_Dx = top/bottom;
                top = location.y - y;
                double dSa_Dy = top/bottom;
                return Eigen::Matrix<double, 1, 2>(dSa_Dx, dSa_Dy);
            }
        }
    }
}
