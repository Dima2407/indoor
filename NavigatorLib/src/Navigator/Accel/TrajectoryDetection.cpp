//
// Created by Igor Maschikevich on 6/8/2017.
//

#include <cmath>
#include "Navigator/Accel/TrajectoryDetection.h"

namespace Navigator {
    namespace Accel {
//==============================================================================
        Math::Position3D TrajectoryDetection::processZUPT(const Accel::AccelOutputData &data) {
            double dt = data.timeDiff;
            //    calculation velocity for aX
            vX = algorithmZUPT(data.ax, vX, data.isStationary, dt);
            //    calculation velocity for aY
            vY = algorithmZUPT(data.ay, vY, data.isStationary, dt);
            double dx = config.adjCoef * vX * dt;
            double dy = config.adjCoef * vY * dt;

            return step(dx, dy, data.isStationary);
        }
//==============================================================================
        Math::Position3D TrajectoryDetection::processDummy(const AccelOutputData &data) {
            double dt = data.timeDiff;
            // Movement step
            double dx = sin(data.yaw) * config.userAverageVelocity * dt;
            double dy = cos(data.yaw) * config.userAverageVelocity * dt;

            return step(dx, dy, data.isStationary);
        }
//==============================================================================
        double TrajectoryDetection::algorithmZUPT(double aXaY, double startVelocity, bool isStationary, double timeDiff) {
            double velocity;
            if (!isStationary)
                velocity = startVelocity + config.globG * aXaY * timeDiff;
            else
                velocity = 0;

            if (velocity > config.maxV)
                velocity = config.maxV;
             else if (velocity < -config.maxV)
                velocity = -config.maxV;

            return velocity;
        }
//==============================================================================
        Math::Position3D TrajectoryDetection::step(double dx, double dy, bool isStationary) {
            double posX0 = posX; // Save old pos
            double posY0 = posY;
            delta.x = dx;  // Save delta for the particle filter
            delta.y = dy;

            if (!isStationary) {
                posX += dx; // Update position
                posY += dy;

                if (rMesh != nullptr) {
                    // Check map edges
                    if (config.useMapEdges) {
                        posX = rMesh->checkX(posX); // Put into map boundaries
                        posY = rMesh->checkY(posY);
                    }
                    // Check walls
                    if (config.useWalls) {
                        if (rMesh->checkWall(posX0, posY0, posX, posY)) {
                            if (!rMesh->checkWall(posX0, posY0, posX0, posY))
                                posX = posX0;
                            else if (!rMesh->checkWall(posX0, posY0, posX, posY0))
                                posY = posY0;
                        }
                    }
                }
            }
            // Mesh + mask correction
            Math::Position3D position(posX, posY, 0.0);
            if (rMesh != nullptr && config.useMeshMask)
                return rMesh->process(position);
            else
                return position;
        }
//==============================================================================
    }
}
