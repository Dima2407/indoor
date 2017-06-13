//
// Created by  Victor Draban on 6/7/2017.
//

#pragma once

#include "AccelOutputData.h"

namespace Navigator {
    namespace Accel {

        class StepDetection {
        public:
            bool recognazeState(const AccelOutputData &data, double accTH);

            bool recognazeState(const AccelOutputData &data) {
                recognazeState(data, 1.035);
            }
        };
    }
}
