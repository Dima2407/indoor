//
// Created by  Oleksiy Grechnyev on 8/9/2017.
//

#pragma once

namespace Navigator {
    namespace Particles {
        struct ParticleNavigatorConfig {
            /// Apply map edges
            bool useMapEdges = true;
            /// Apply wall algorithm
            bool useWalls = true;
            /// Use mesh+mask to the final position
            bool useMeshMask = true;
        };
    }
}
