//
// Created by Igor Maschikevich on 6/8/2017.
//
#pragma once

#include <memory>
#include <cmath>

#include "Navigator/Math/Position3D.h"
#include "Navigator/Mesh/MeshData.h"
#include "Navigator/Mesh/RectanMesh.h"
#include "AccelOutputData.h"
namespace Navigator {
namespace Accel {


class TrajectoryDetection
{
private: //============Fields
    std::shared_ptr<Mesh::RectanMesh> rMesh;
    double minX;
    double minY;
    double maxX;
    double maxY;
    double ksi;

    double posX;
    double posY;
    double vX = 0.0;
    double vY = 0.0;

    static constexpr double adjCoef = 3;
    static constexpr double maxV = 3.5;
    static constexpr double globG = 9.8066;

public:

    double getVX(){
        return vX;
    }
    double getVY(){
        return vY;
    }

    TrajectoryDetection(const std::shared_ptr<Mesh::RectanMesh> &rMesh,  double posX,  double posY):
        rMesh(rMesh),
        posX(posX),
        posY(posY){

        const Mesh::MeshData & mesh = rMesh->getMesh();
        ksi = std::fmin( mesh.dx/2, mesh.dy/2);
        minX = mesh.x0;
        minY = mesh.y0;
        maxX = mesh.x0 + (mesh.nx - 1) * mesh.dx;
        maxY = mesh.y0 + (mesh.ny - 1) * mesh.dy;
    }

    Math::Position3D process(const Accel::AccelOutputData &data);

    /// The algorithm calculates the speed taking into account the static and dynamic stages of the user's movement.
    double algorithmZUPT (double axAy, double velocityXY0, bool isStationary, double timeDiff);

    /// Correct posX or posY if (maxX < posX < minX) or (maxY < posY < minY)
    double checkXY( double pos, double max,  double min);

    /// True if the line (x0,y0) -> (x,y) crosses a wall (obstacle)
    bool checkWall(double x1, double y1, double x2, double y2);

    /// True if black nearest mesh node
    bool checkBlack(double x, double y);

};

}
}
