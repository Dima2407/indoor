//
// Created by Victor Draban on 7/21/2017.
//

#pragma once

#include "KalmanConfig.h"

namespace Navigator {
    namespace Math {
        namespace Kalman {
            class KalmanFilter {

            public:
                KalmanFilter(const KalmanConfig& config = KalmanConfig()) :
                    config(config) {}

                void process();

                virtual ~KalmanFilter() {};
            private:
                void predictCurrentMoment();
                void predictError();

                void correctKalman();
                void correctCurrentMoment();
                void correctError();

                KalmanConfig config;
            };
        }
    }
}
