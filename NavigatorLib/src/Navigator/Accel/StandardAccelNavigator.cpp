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

            // Accumulate delta for the particle bluetoothNavigator
            deltaMutex.lock(); // Thread safe
            delta += trajectoryDetection.getDelta();
            deltaMutex.unlock();

            return lastPosition;
        }
        //======================================================
        Math::Position2D StandardAccelNavigator::getResetDelta() {
            deltaMutex.lock(); // Thread safe
            Math::Position2D temp = delta;  // get
            delta = {0, 0};  // reset
            deltaMutex.unlock();
            return temp;
        }
    }
}
