//
// Created by  Oleksiy Grechnyev on 9/18/2017.
//

#pragma once
/// Unified configuration for mesh/mask/map postprocessing
namespace Navigator {
    namespace Mesh {
        struct MeshConfig {
            /// Apply map edges (only matters if useMesh == useMeshMask == false)
            bool useMapEdges = true;

            /// Apply wall algorithm (Used in accel and partcile navigators)
            bool useWalls = true;

            /// Use mesh+mask
            bool useMeshMask = true;

            /// Use mesh correction, used if useMeshMask = false
            bool useMesh = true;
        };
    }
}