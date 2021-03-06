//
// Created by Igor Maschikevich on 6/8/2017.
// Modified by Oleksiy Grechnyev
//
#pragma once

#include <memory>
#include <cmath>

#include "Navigator/Math/Position3D.h"
#include "Navigator/Mesh/MeshData.h"
#include "Navigator/Mesh/RectanMesh.h"
#include "AccelOutputData.h"
#include "AccelConfig.h"


namespace Navigator {
    namespace Accel {


        class TrajectoryDetection {
        private: //============Fields
            AccelConfig config;

            std::shared_ptr<Mesh::RectanMesh> rMesh;

            /// The raw (no mesh/mask) position shift at the last step
            Math::Position2D delta;

            double minX;
            double minY;
            double maxX;
            double maxY;
            double xi;

            double posX;
            double posY;
            double vX = 0.0;
            double vY = 0.0;

//    static constexpr double adjCoef = 3;
//    static constexpr double maxV = 3.5;
//    static constexpr double globG = 9.8066;



        public:  //======== Methods

            double getVX() {
                return vX;
            }

            double getVY() {
                return vY;
            }

            TrajectoryDetection(const std::shared_ptr<Mesh::RectanMesh> &rMesh, double posX, double posY,
                                const AccelConfig &config = AccelConfig()) :
                    rMesh(rMesh),
                    posX(posX),
                    posY(posY),
                    config(config) {

                if (rMesh != nullptr) {
                    // Calculate mesh boundaries and xi
                    const Mesh::MeshData &mesh = rMesh->getMesh();

                    xi = std::fmin(mesh.dx / 2, mesh.dy / 2);
                    minX = mesh.x0;
                    minY = mesh.y0;
                    maxX = mesh.x0 + (mesh.nx - 1) * mesh.dx;
                    maxY = mesh.y0 + (mesh.ny - 1) * mesh.dy;
                }
            }

            /// Process input data using ZUPT algorithm
            Math::Position3D processZUPT(const Accel::AccelOutputData &data);

            /// Process input data using Dummy algorithm
            Math::Position3D processDummy(const Accel::AccelOutputData &data);

            /// The algorithm calculates the speed taking into account the static and dynamic stages of the user's movement.
            double algorithmZUPT(double axAy, double startVelocity, bool isStationary, double timeDiff);

            const Math::Position2D &getDelta() const {
                return delta;
            }

        private: //================ Methods
            /// Make a step with calculated dx, dy, with checking map, mask if neeeded
            Math::Position3D step(double dx, double dy, bool isStationary);
        };

    }
}
