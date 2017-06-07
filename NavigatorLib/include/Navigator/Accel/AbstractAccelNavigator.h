//
// Created by  Oleksiy Grechnyev on 6/7/2017.
//

#pragma once

#include "Navigator/Math/Position3D.h"
#include "Navigator/Accel/AccelReceivedData.h"

namespace Navigator {
    namespace Accel {
        class AbstractAccelNavigator {
        public:
            /// Process a single input data
            virtual const Math::Position3D &process(const AccelReceivedData & brd) = 0;
        };

    }
}

