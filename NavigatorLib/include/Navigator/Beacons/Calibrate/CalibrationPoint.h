//
// Created by  Oleksiy Grechnyev on 3/24/2017.
//

#pragma once

#include <vector>

#include "Navigator/Math/Position3D.h"
#include "Navigator/Beacons/BeaconReceivedData.h"

namespace Navigator {
    namespace Beacons {
        namespace Calibrate {

            /** \brief
             *
             */
            struct CalibrationPoint {
                /// Coordinates of the point where the calibration is made
                Math::Position3D position;

                /// Data packets received at that point
                std::vector<BeaconReceivedData> packets;
            };
        }
    }
}


