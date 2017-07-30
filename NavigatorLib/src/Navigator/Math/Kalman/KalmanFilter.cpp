//
// Created by  Victor Draban on 7/21/2017.
//

#include <iostream>
#include <iomanip>
#include <cmath>
#include "Navigator/Math/Kalman/KalmanFilter.h"
using namespace std;
namespace Navigator {
    namespace Math {
        namespace Kalman {

            Filter::IFilter::Value KalmanFilter::process(Filter::IFilter::Value in) {
                double val = in.val;
                lastPacketTime = in.timeStamp;
                if (!isInitialize) {
                    lastX(0,0) = in.val;
                    lastX(1,0) = 0;
                    lastP = config.P_INIT;
                    lastTime = in.timeStamp;
                    isInitialize = true;
                    return in;
                }
                double deltaT = in.timeStamp - lastTime;
                Eigen::Matrix<double, 2, 2> Ak;
                Ak(0, 0) = 1;
                Ak(0, 1) = deltaT;
                Ak(1, 0) = 0;
                Ak(1, 1) = 1;

                Eigen::Matrix<double, 2, 1> tempX = predictCurrentMoment(Ak); // CORRECT
                // ----------------
//                cout << " tempX(0,0) = " << tempX(0,0) << " tempX(1,0) = " << tempX(1,0) << endl;
                // ----------------
                Eigen::Matrix<double, 2, 2> tempP = predictError(Ak); // CORRECT
                // ----------------
                std::cout << " tempP(0,0) = " << tempP(0,0) << " tempP(0,1) = " << tempP(0,1)
                          << " tempP(1,0) = " << tempP(1,0) << " tempP(1,1) = " << tempP(1,1) << std::endl;
                // ----------------
                Eigen::Matrix<double, 2, 1> kalmansCoefficient = correctKalman(tempP);
                // ----------------
//                std::cout << " kalmansCoefficient(0,0) = " << kalmansCoefficient(0,0)
//                          << " kalmansCoefficient(1,0) = " << kalmansCoefficient(1,0) << std::endl;
                // ----------------
                correctCurrentMoment(tempX, kalmansCoefficient, val);
                // ----------------
//                std::cout << " lastX(0,0) = " << lastX(0,0) << " lastX(1,0) = " << lastX(1,0) << std::endl;
                // ----------------
                correctError(tempP, kalmansCoefficient);
                // ----------------
//                std::cout << " lastP(0,0) = " << lastP(0,0) << " lastP(0,1) = " << lastP(0,1)
//                          << " lastP(1,0) = " << lastP(1,0) << " lastP(1,1) = " << lastP(1,1) << std::endl;
                // ----------------

                lastTime = in.timeStamp;
                return Filter::IFilter::Value(lastX(0,0), lastTime);
            }

            // -----------------

            Filter::IFilter::Value KalmanFilter::processOnlyPredict(double timestamp) {
                if (timestamp - lastPacketTime > config.timeout) {
                    isInitialize = false;
                    return Filter::IFilter::Value(lastX(0,0), timestamp);
                }
                double deltaT = timestamp - lastTime;
                Eigen::Matrix<double, 2, 2> Ak;
                Ak(0, 0) = 1;
                Ak(0, 1) = deltaT;
                Ak(1, 0) = 0;
                Ak(1, 1) = 1;

                lastX = predictCurrentMoment(Ak);
                lastP = predictError(Ak);

                lastTime = timestamp;
                return Filter::IFilter::Value(lastX(0,0), timestamp);
            }

            // ------------ private -----------------

            Eigen::Matrix<double, 2, 1> KalmanFilter::predictCurrentMoment(const Eigen::Matrix<double, 2, 2>& Ak) {
                return Ak * lastX;
            }

            // -----------------

            Eigen::Matrix<double, 2, 2> KalmanFilter::predictError(const Eigen::Matrix<double, 2, 2>& Ak) {
                return Ak * lastP * Ak.transpose() + config.Q;
            }

            // -----------------

            Eigen::Matrix<double, 2, 1> KalmanFilter::correctKalman(const Eigen::Matrix<double, 2, 2>& tempP) {
                double smallExpression = pow((config.H * tempP * config.H.transpose() + config.R), -1);
                return tempP * config.H.transpose() * smallExpression;
            }

            // -----------------

            void KalmanFilter::correctCurrentMoment(Eigen::Matrix<double, 2, 1> tempX,
                                                                           const Eigen::Matrix<double, 2, 1>& kalmansCoefficient,
                                                                           const double val) {
                lastX = tempX + kalmansCoefficient * (val - config.H * lastX);
            }

            // -----------------

            void KalmanFilter::correctError(const Eigen::Matrix<double, 2, 2>& tempP,
                                            const Eigen::Matrix<double, 2, 1>& kalmansCoefficient) {
                lastP = (config.I - kalmansCoefficient * config.H) * tempP;
            }
        }
    }
}