//
// Created by  Oleksiy Grechnyev on 6/7/2017.
//

#pragma once

#include "Navigator/Math/Position3D.h"
#include "Navigator/Accel/AccelReceivedData.h"
#include "Navigator/INavigator.h"

namespace Navigator {
    namespace Accel {
        class AbstractAccelNavigator : public INavigator {
        public:
            /// Process a single input data
            virtual const Math::Position3D  & process(const AccelReceivedData & brd) = 0;

            /// Get last position
            virtual const Math::Position3D  & getLastPosition() const = 0;

            virtual Math::Position3D obtainLastPosition() override {
                return getLastPosition();
            }

            /// Get delta and reset it to 0 (thread safe)
            virtual Math::Position2D getResetDelta() = 0;
        };

    }
}

