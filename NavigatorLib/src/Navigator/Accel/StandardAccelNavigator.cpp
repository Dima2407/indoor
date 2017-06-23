//
// Created by  Oleksiy Grechnyev on 6/7/2017.
//

#include "Navigator/Accel/StandardAccelNavigator.h"

namespace Navigator {
    namespace Accel {
        Math::Position3D StandardAccelNavigator::process(const AccelReceivedData &ard) {
            AccelOutputData aod = toGlobal.process(ard);

            // We need this to use the stupid left-handed coordinates in this navigator
            // We use the same coordinate system as in the beacon navigator (or, rather, meshgen2 and mobile apps)
            // The (0,0) is the UPPER LEFT map corner and the y axis goes DOWN
            // The trasformation to normal coordinates is
            // y<->h-y , where h = map heightin meters, thus ay<->-ay, vy<->-vy
            // I did it here so that the unit tests for toGlobal and trajectoryDetection wouldn't be affected
            aod.ay = -aod.ay;

            return trajectoryDetection.process(aod);
        }
    }
}