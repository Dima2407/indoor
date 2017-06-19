//
// Created by  Oleksiy Grechnyev on 6/7/2017.
//

#include "Navigator/Accel/StandardAccelNavigator.h"

namespace Navigator {
    namespace Accel {
        Math::Position3D StandardAccelNavigator::process(const AccelReceivedData &ard) {
            return trajectoryDetection.process(
                    toGlobal.process(ard)
            );
        }
    }
}