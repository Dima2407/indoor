//
// Created by Victor Draban on 7/21/2017.
//

#pragma once

#include "Navigator/Math/Filter/AlphaBetaFilter.h"

namespace Navigator {
    namespace Math {
        namespace Kalman {
            class KalmanFilter {
            public:
                void process();

                virtual ~KalmanFilter() {};
            private:
                void predictCurrentMoment();
                void predictError();

                void correctKalman();
                void correctCurrentMoment();
                void correctError();
            };
        }
    }
}
