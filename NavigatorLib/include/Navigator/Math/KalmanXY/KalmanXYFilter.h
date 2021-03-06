﻿//
// Created by Victor Draban on 9/06/2017.
//

#pragma once

//#define EIGEN_DONT_ALIGN

#include "KalmanXYConfig.h"
#include "Navigator/Math/Position3D.h"

namespace Navigator {
    namespace Math {
        namespace KalmanXY {
            class KalmanXYFilter {

            public:

                KalmanXYFilter(const KalmanXYConfig& config = KalmanXYConfig()) :
                    config(config)
                {}

                Math::Position2D process(const Math::Position2D &location,
                                         const std::vector<Math::Position2D> beacPosition);

                void reset() {
                    isInitialized = false;
                }

//                const Eigen::Matrix<double, 2, 1> &getLastX() const {
//                    return lastX;
//                }

//                const Eigen::Matrix<double, 2, 2> &getLastP() const {
//                    return lastP;
//                }

//                const Eigen::Matrix<double, 2, 1> &getTempX() const {
//                    return tempX;
//                }

//                const Eigen::Matrix<double, 2, 2> &getTempP() const {
//                    return tempP;
//                }

//                bool getIsInitialized() const {
//                    return isInitialized;
//                }

            private:

                void predictCurrentMoment();

                void predictError();

                Eigen::Matrix<double, 2, 3> correctKalman(const Eigen::Matrix<double, 3, 2> &posBeacons,
                                                          const Eigen::Matrix<double, 3, 2> &matrixH);

                void correctCurrentMoment(const Eigen::Matrix<double, 1, 2> &locationXY,
                                          const Eigen::Matrix<double, 2, 3> &kalmansCoefficient,
                                          const Eigen::Matrix<double, 3, 2> &matrixH);

                void correctError(const Eigen::Matrix<double, 2, 3>& kalmansCoefficient,
                                  const Eigen::Matrix<double, 3, 2> &matrixH);

                Eigen::Matrix<double, 1, 2> helpExpression(const Math::Position2D &location, double x, double y);


            private:
                bool isInitialized = false;
                KalmanXYConfig config;
                Eigen::Matrix<double, 2, 1> lastX;
                Eigen::Matrix<double, 2, 2> lastP;
                Eigen::Matrix<double, 2, 1> tempX;
                Eigen::Matrix<double, 2, 2> tempP;
            };
        }
    }
}
