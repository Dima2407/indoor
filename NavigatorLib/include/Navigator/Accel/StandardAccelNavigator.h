//
// Created by  Oleksiy Grechnyev on 6/7/2017.
//

#pragma once

#include "./AbstractAccelNavigator.h"

namespace Navigator {
    namespace Accel {

        class StandardAccelNavigator : public AbstractAccelNavigator{
        public:
            const Math::Position3D &process(const AccelReceivedData &brd) override;
        };
    }
}


