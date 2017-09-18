//
// Created by  Oleksiy Grechnyev on 7/24/2017.
//

#pragma once

#include "Navigator/Mesh/MeshConfig.h"

namespace Navigator {
    namespace Beacons {
        /// Configuration for StandardBeaconNavigator, with defaults, could be extended if needed
        struct StandardBeaconNavigatorConfig {

            // ========= Init phase config
            /// Do we do the initialization at all ?
            bool useInit = true;

            /// Initialization phase duration in seconds
            double initPhaseDuration = 5.0;

            // ========= Post-init filters config

            // Not yet, can be added if needed

            // ======== Trilat config
            /// Do we use full 3D trilat instead of 2D ? (default = false)
            bool use3DTrilat = false;

            /// Max number of strongest (largest RSSI) beacons to use on each trilateration, 0 = unlimited (so-called multilateration)
            int useStrongest = 3;

            // ======== Mesh+mask config
            Mesh::MeshConfig meshConfig;
        };
    }
}


