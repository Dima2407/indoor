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
                if (rMesh==nullptr || !rMesh->checkBlack(p.x, p.y))
                    return p; 
                else if (config.useWalls || config.useMeshMask)  // Check mask
                    return  rMesh->process(p);
                else if (config.useMapEdges)  // Check map edges only
                    return  rMesh->checkEdges(p);
                else
                    return (Position2D)p; 
            };
            
            auto allowMove = [this](const Position2D &p1, const Position2D &p2) -> bool {
                if (rMesh==nullptr)
                    return true; // Always allowed
                else if (config.useWalls)  // Check walls+mask (slower)
                    return  !rMesh->checkWall(p1.x, p1.y, p2.x, p2.y);
                else if (config.useMeshMask)  // Check endpoints only (faster)
                    return !rMesh->checkBlack(p1.x, p1.y) && !rMesh->checkBlack(p2.x, p2.y);
                else if (config.useMapEdges)  // Check map edges only
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
                lastPosition = postProcess(z); // Mesh + mask
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
            Position2D result = pFilter.process(delta, z, allowMove, meshCorrect);

            lastPosition = postProcess(result); // Mesh + mask
            return lastPosition;
        }
//=============================================================
        Math::Position3D ParticleNavigator::postProcess(const Math::Position3D &p) {
            if (std::isnan(p.x) || std::isnan(p.y))
                return p;

            // Postprocess using rMesh+masktable
            if (rMesh != nullptr && config.useMeshMask)
                return rMesh->process(p);
            else if (rMesh != nullptr && config.useMapEdges)
                return rMesh->checkEdges(p);
            else
                return p;
        }
//=============================================================

    }
}