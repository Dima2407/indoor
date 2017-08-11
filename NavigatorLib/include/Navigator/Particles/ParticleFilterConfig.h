//
// Created by  Oleksiy Grechnyev on 8/7/2017.
//

#pragma once

namespace Navigator {
    namespace Particles {
        struct ParticleFilterConfig {
            /**
             * @brief numPart
             * Number of particles
             */
            int numPart = 20;

            /**
             * @brief sigmaX
             * The accuracy of the model describing the process
             */
            double sigmaX = 0.1;

            /**
             * @brief sigmaY
             * The accuracy of the model describing the process
             */
            double sigmaY = 0.1;

            /**
             * @brief alpha
             * accuracy position by beacons
             */
            double alpha = 1.0;
        };

    }
}

