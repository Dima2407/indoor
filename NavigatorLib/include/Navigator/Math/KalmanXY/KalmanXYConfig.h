//
// Created by Victor Draban on 9/06/2017.
//

#pragma once

#include <vector>
#include <Eigen/Dense>

//#define EIGEN_DONT_ALIGN

namespace Navigator {
    namespace Math {
        namespace KalmanXY {

            /**
             * @brief The KalmanXYConfig struct
             * Started configuration for KalmanXY's Filter
             */
            struct KalmanXYConfig {

                KalmanXYConfig() {
                    matrixAk << 1, 0,
                                0, 1;

                    matrixInitP << 10, 0,
                                    0, 10;

                    matrixQ << 0.1, 0,
                               0, 0.1;

                    matrixR << 1, 0, 0,
                               0, 1, 0,
                               0, 0, 1;

                    matrixI << 1, 0,
                               0, 1;

                }

                /**
                 * @brief matrixAk
                 * unit matrix
                 */
                Eigen::Matrix<double, 2, 2> matrixAk;

                /**
                 * @brief matrixInitP
                 * start values covariant matrix
                 */
                Eigen::Matrix<double, 2, 2> matrixInitP;

                /**
                 * @brief matrixQ
                 * Variance of process model noise
                 */
                Eigen::Matrix<double, 2, 2> matrixQ;

                /**
                 * @brief matrixR
                 * The value of the variance of the noise of the changes
                 */
                Eigen::Matrix<double, 3, 3> matrixR;

                /**
                 * @brief matrixI
                 * unit matrix
                 */
                Eigen::Matrix<double, 2, 2> matrixI;
            };
         }
    }
}
