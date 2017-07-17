//
// Created by  Oleksiy Grechnyev on 6/7/2017.
//

#include "Navigator/Accel/StandardAccelNavigator.h"

namespace Navigator {
    namespace Accel {
        const Math::Position3D  & StandardAccelNavigator::process(const AccelReceivedData &ard) {
            // Convert accel to global coords + step detection
            AccelOutputData aod = toGlobal.process(ard);

            // Use either ZUPT or Dummy alorithm
//            lastPosition = trajectoryDetection.processZUPT(aod);
            lastPosition = trajectoryDetection.processDummy(aod);
            return lastPosition;
        }
    }
}
