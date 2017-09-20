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

            // Accuracy parameters,

            /**
             * @brief sigmaX
             * The accuracy of the model describing the process
             */
            double sigmaModelX = 0.2;

            /**
             * @brief sigmaY
             * The accuracy of the model describing the process
             */
            double sigmaModelY = 0.2;


            /// Signa for weight calculation
            double sigmaWeightX = 0.7;

            double sigmaWeightY = 0.7;

            /**
             * @brief alpha
             * accuracy position by beacons
             */
            double alpha = 2.0;

            // The following options are used for testing and debugging only
            /// Use simulated random numbers instead of random numbers
            bool simulatedRandom = false;

            /// Do we use resampling?
            bool useResampling = true;
        };

    }
}

