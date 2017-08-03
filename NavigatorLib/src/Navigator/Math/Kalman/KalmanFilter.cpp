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
                cout.precision(17);
//                cout << "--------------------" << endl;
//                cout << "KalmanFilter:   " << in.timeStamp << "   " << in.val << endl;

                if (!isInitialized) {  // CORRECT
                    lastX(0,0) = in.val;
                    lastX(1,0) = 0;
                    lastP = config.P_INIT;
                    lastTime = in.timeStamp;
                    isInitialized = true;
//                    cout << "lastX = \n" << lastX << endl;
//                    cout << "lastP = \n" << lastP << endl;
//                    cout << "lastX(0,0) = " << lastX(0,0) << endl;
//                    cout << "lastX(1,0) = " << lastX(1,0) << endl;
//                    cout << "lastP(0,0) = " << lastP(0,0) << endl;
//                    cout << "lastP(0,1) = " << lastP(0,1) << endl;
//                    cout << "lastP(1,0) = " << lastP(1,0) << endl;
//                    cout << "lastP(1,1) = " << lastP(1,1) << endl;
//                    cout << "lastTime = " << lastTime << endl;
//                    cout << "isInitialized = " << isInitialized << endl;
//                    cout << "-----------------------------" << endl;
                    return in;
                }
                double deltaT = in.timeStamp - lastTime;
                Eigen::Matrix<double, 2, 2> Ak;
                Ak(0, 0) = 1;
                Ak(0, 1) = deltaT;
                Ak(1, 0) = 0;
                Ak(1, 1) = 1;
//                cout << "Ak = \n" << Ak << endl;

//                std::cout << " Ak(0,0) = " << Ak(0,0) << " Ak(0,1) = " << Ak(0,1)
//                                 << " Ak(1,0) = " << Ak(1,0) << " Ak(1,1) = " << Ak(1,1) << std::endl;

                Eigen::Matrix<double, 2, 1> tempX = predictCurrentMoment(Ak); // CORRECT
//                cout << "tempX = \n" << tempX << endl;

                // ----------------
//                cout << " tempX(0,0) = " << tempX(0,0) << " tempX(1,0) = " << tempX(1,0) << endl;
                // ----------------
                Eigen::Matrix<double, 2, 2> tempP = predictError(Ak); // CORRECT
//                cout << "tempP = \n" << tempP << endl;

                // ----------------
//                std::cout << " tempP(0,0) = " << tempP(0,0) << " tempP(0,1) = " << tempP(0,1)
//                          << " tempP(1,0) = " << tempP(1,0) << " tempP(1,1) = " << tempP(1,1) << std::endl;
//                cout << " -----------  end step prediction  ------------" << endl;
                // ----------------
                Eigen::Matrix<double, 2, 1> kalmansCoefficient = correctKalman(tempP); // CORRECT
//                cout << "K = \n" << kalmansCoefficient << endl;

                // мои расчеты (0.999257  0.399677)  --- программа посчитала (0.999201  0.399677)
                // ----------------
//                std::cout << " kalmansCoefficient(0,0) = " << kalmansCoefficient(0,0)
//                          << " kalmansCoefficient(1,0) = " << kalmansCoefficient(1,0) << std::endl;
//                cout << " -----------  end step calculated kalmansCoefficient  ------------" << endl;
                // ----------------
                correctCurrentMoment(tempX, kalmansCoefficient, val); // CORRECT
                // ----------------
//                std::cout << " lastX(0,0) = " << lastX(0,0) << " lastX(1,0) = " << lastX(1,0) << " ";
                // ----------------
                correctError(tempP, kalmansCoefficient);
                // ----------------
//                std::cout << " lastP(0,0) = " << lastP(0,0) << " lastP(0,1) = " << lastP(0,1)
//                          << " lastP(1,0) = " << lastP(1,0) << " lastP(1,1) = " << lastP(1,1) << std::endl;
//                cout << " -----------  end step correction  ------------" << endl;
                // ----------------
//                cout << "lastX = \n" << lastX << endl;
//                cout << "lastP = \n" << lastP << endl;
                lastTime = in.timeStamp;
                return Filter::IFilter::Value(lastX(0,0), in.timeStamp);
            }

            // -----------------

            Filter::IFilter::Value KalmanFilter::processOnlyPredict(double timestamp) {
                if (timestamp - lastPacketTime > config.timeout) {
                    isInitialized = false;
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
//                Eigen::Matrix<double, 2, 1> result = Ak * lastX;
//                cout << result << endl;
                return Ak * lastX;
            }

            // -----------------

            Eigen::Matrix<double, 2, 2> KalmanFilter::predictError(const Eigen::Matrix<double, 2, 2>& Ak) {
//                Eigen::Matrix<double, 2, 2> result = Ak * lastP * Ak.transpose() + config.Q;
//                std::cout << " result(0,0) = " << result(0,0) << " result(0,1) = " << result(0,1)
//                          << " result(1,0) = " << result(1,0) << " result(1,1) = " << result(1,1) << std::endl;
                return Ak * lastP * Ak.transpose() + config.Q;
            }

            // -----------------

            Eigen::Matrix<double, 2, 1> KalmanFilter::correctKalman(const Eigen::Matrix<double, 2, 2>& tempP) {
                double smallExpression = pow((config.H * tempP * config.H.transpose() + config.R), -1);
//                cout << "config.H * tempP * config.H.transpose() + config.R"
//                     << config.H * tempP * config.H.transpose() + config.R << endl;
//                cout << "smallExpression = " << smallExpression << endl;
                return tempP * config.H.transpose() * smallExpression;
            }

            // -----------------

            void KalmanFilter::correctCurrentMoment(Eigen::Matrix<double, 2, 1> tempX,
                                                                           const Eigen::Matrix<double, 2, 1>& kalmansCoefficient,
                                                                           const double val) {
                lastX = tempX + kalmansCoefficient * (val - config.H * tempX);
            }

            // -----------------

            void KalmanFilter::correctError(const Eigen::Matrix<double, 2, 2>& tempP,
                                            const Eigen::Matrix<double, 2, 1>& kalmansCoefficient) {
                lastP = (config.I - kalmansCoefficient * config.H) * tempP;
            }
        }
    }
}
