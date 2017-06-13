//
// Created by  Victor Draban on 6/7/2017.
//

#pragma once

#include "AccelOutputData.h"
#include "AccelReceivedData.h"

namespace Navigator {
    namespace Accel {

        class AHRSCorrection {
        public:
            AccelOutputData angleCorrection(const AccelReceivedData &data);
        };

    }
}
