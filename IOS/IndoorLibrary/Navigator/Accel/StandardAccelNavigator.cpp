//
// Created by  Oleksiy Grechnyev on 6/7/2017.
//

#include "Navigator/Accel/StandardAccelNavigator.h"

namespace Navigator {
    namespace Accel {
        const Math::Position3D  & StandardAccelNavigator::process(const AccelReceivedData &ard) {
            AccelOutputData aod = toGlobal.process(ard);

            lastPosition = trajectoryDetection.process(aod);
            return lastPosition;
        }
    }
}
