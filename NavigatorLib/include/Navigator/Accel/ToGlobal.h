//
// Created by  Victor Draban on 6/7/2017.
//

#pragma once

#include "AccelOutputData.h"
#include "AccelReceivedData.h"

namespace Navigator {
    namespace Accel {

        class ToGlobal {

        public:
            AccelOutputData process(AccelOutputData data);
        };
    }
}
