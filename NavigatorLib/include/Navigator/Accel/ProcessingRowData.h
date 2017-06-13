//
// Created by  Victor Draban on 6/8/2017.
//

#pragma once

#include "AccelReceivedData.h"
#include "AccelOutputData.h"

namespace Navigator {
    namespace Accel {

        class ProcessingRowData {

        public:
            AccelOutputData process(const AccelReceivedData &data);
        };
    }
}
