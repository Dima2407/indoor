//
// Created by  Oleksiy Grechnyev on 8/9/2017.
//

#include <cmath>
#include <cstdio>

#include "Navigator/Particles/ParticleNavigator.h"

namespace Navigator {
    namespace Particles {
//=============================================================
        Math::Position3D ParticleNavigator::obtainLastPosition() {
            using namespace std;
            using namespace Math;
            // Note: implicit Position2D <-> Position3D conversion through type cast operators is used here
            Position2D z = bNav->getLastPosition(); // Get Last position from BLE
            if (isnan(z.x) || isnan(z.y))
                throw runtime_error("ParticleNavigator : BLE gives NAN !");

            // Lambdas
            auto meshCorrect = [this](const Position2D &p) -> Position2D{
                if (rMesh)
                    return rMesh->process(p, meshConfig);
                else
                    return p;
            };
            
            auto allowMove = [this](const Position2D &p1, const Position2D &p2) -> bool {
                if (rMesh==nullptr)
                    return true; // Always allowed
                else if (meshConfig.useWalls)  // Check walls+mask (slower)
                    return  !rMesh->checkWall(p1.x, p1.y, p2.x, p2.y);
                else if (meshConfig.useMeshMask)  // Check endpoints only (faster)
                    return !rMesh->checkBlack(p1.x, p1.y) && !rMesh->checkBlack(p2.x, p2.y);
                else if (meshConfig.useMapEdges)  // Check map edges only
                    return !rMesh->isOutsideMap(p1.x, p1.y) && !rMesh->isOutsideMap(p2.x, p2.y);
                else
                    return true; // Always allowed
            };
            
            // Initialize
            if (!isInitialized) {
                // Initialize the particle filter
                isInitialized = true;
                pFilter.initialize(z, meshCorrect);
                aNav->getResetDelta();  // Start delta from this time point, important !
                lastPosition = z;
                // Mesh + mask
                if (rMesh)
                    lastPosition = rMesh->process(lastPosition, meshConfig);
                return lastPosition;
            }

            // Get delta from the acc bluetoothNavigator and reset delta
            Position2D delta = aNav->getResetDelta();
            if (isnan(delta.x) || isnan(delta.y))
                throw runtime_error("ParticleNavigator : ACC gives NAN !");

            // printf("delta = %lf %lf \n", delta.x, delta.y);
            // Don't run the filter if delta is zero
            if (delta.abs() < 1.e-10)
                return lastPosition;

            // One step of the particle filter, with wall detection
            lastPosition = pFilter.process(delta, z, allowMove, meshCorrect);

            if (rMesh)
                lastPosition = rMesh->process(lastPosition, meshConfig);

            return lastPosition;
        }
//=============================================================

    }
}