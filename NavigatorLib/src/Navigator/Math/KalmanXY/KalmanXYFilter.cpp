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
                                                                const Eigen::Matrix<double, 1, 3> &distanceToBeacons) {
                if (!isInitialized) {
                    lastX << 0, 0;
                    lastP = config.matrixInitP;
                    isInitialized = true;
                }

                tempX = predictCurrentMoment();
                tempP = predictError();

//                Eigen::Matrix<double, 2, 1> kalmansCoefficient = correctKalman(tempP);
//                cout << "K = \n" << kalmansCoefficient << endl;

                // мои расчеты (0.999257  0.399677)  --- программа посчитала (0.999201  0.399677)
                // ----------------
//                std::cout << " kalmansCoefficient(0,0) = " << kalmansCoefficient(0,0)
//                          << " kalmansCoefficient(1,0) = " << kalmansCoefficient(1,0) << std::endl;
//                cout << " -----------  end step calculated kalmansCoefficient  ------------" << endl;
                // ----------------
//                correctCurrentMoment(tempX, kalmansCoefficient, val);
                // ----------------
//                std::cout << " lastX(0,0) = " << lastX(0,0) << " lastX(1,0) = " << lastX(1,0) << " ";
                // ----------------
//                correctError(tempP, kalmansCoefficient);
                // ----------------
//                std::cout << " lastP(0,0) = " << lastP(0,0) << " lastP(0,1) = " << lastP(0,1)
//                          << " lastP(1,0) = " << lastP(1,0) << " lastP(1,1) = " << lastP(1,1) << std::endl;
//                cout << " -----------  end step correction  ------------" << endl;
                // ----------------
//                cout << "lastX = \n" << lastX << endl;
//                cout << "lastP = \n" << lastP << endl;
//                lastTime = in.timeStamp;
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

            Eigen::Matrix<double, 2, 1> KalmanXYFilter::predictCurrentMoment() {
                return config.matrixAk * lastX;
            }

            // -----------------

            Eigen::Matrix<double, 2, 2> KalmanXYFilter::predictError() {
                return config.matrixAk * lastP * config.matrixAk.transpose() + config.matrixQ;
            }

            // -----------------

            Eigen::Matrix<double, 2, 1> KalmanXYFilter::correctKalman(const Eigen::Matrix<double, 2, 2>& tempP,
                                                                      const Eigen::Matrix<double, 2, 3> &distanceToBeacons) {
//                double smallExpression = pow((config.H * tempP * config.H.transpose() + config.R), -1);
//                return tempP * config.H.transpose() * smallExpression;
                Eigen::Matrix<double, 1, 2> first = helpExpression(distanceToBeacons(0,0), distanceToBeacons(0, 1));
                Eigen::Matrix<double, 1, 2> second = helpExpression(distanceToBeacons(1,0), distanceToBeacons(1, 1));
                Eigen::Matrix<double, 1, 2> third = helpExpression(distanceToBeacons(2,0), distanceToBeacons(2, 1));

                Eigen::Matrix<double, 3, 2> matrixH;
                matrixH << first(0,0), first(0,1),
                           second(0,0), second(0,1),
                           third(0,0), third(0,1);

                Eigen::Matrix<double, 2, 1> result(0, 0);
                return result;
            }

            // -----------------

//            void KalmanXYFilter::correctCurrentMoment(Eigen::Matrix<double, 2, 1> tempX,
//                                                                           const Eigen::Matrix<double, 2, 1>& kalmansCoefficient,
//                                                                           const double val) {
//                lastX = tempX + kalmansCoefficient * (val - config.H * tempX);
//            }

            // -----------------

//            void KalmanXYFilter::correctError(const Eigen::Matrix<double, 2, 2>& tempP,
//                                            const Eigen::Matrix<double, 2, 1>& kalmansCoefficient) {
//                lastP = (config.matrixI - kalmansCoefficient * config.H) * tempP;
//            }

            Eigen::Matrix<double, 1, 2> KalmanXYFilter::helpExpression(double x, double y) {
                double topX = tempX(0, 0) - x;
                double bottomX = std::sqrt(std::pow(tempX(0, 0) - x, 2)
                                          + std::pow(tempX(1, 0) - y, 2));
                double dSa_Dx = topX/bottomX;

                double topY = tempX(1, 0) - y;
                double bottomY = std::sqrt(std::pow(tempX(0, 0) - x, 2)
                                          + std::pow(tempX(1, 0) - y, 2));
                double dSa_Dy = topY/bottomY;
                return Eigen::Matrix<double, 1, 2>(dSa_Dx, dSa_Dy);
            }
        }
    }
}
