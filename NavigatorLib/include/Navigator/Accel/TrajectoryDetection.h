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
#include "AlgorithmZUPT.h"
namespace Navigator {
namespace Accel {


class TrajectoryDetection
{
private:
    std::shared_ptr<Mesh::RectanMesh> rMesh;

    double minX;
    double minY;
    double maxX;
    double maxY;
    double ksi;

public:

    TrajectoryDetection(const std::shared_ptr<Mesh::RectanMesh> &rMesh,  double posX,  double posY):
        rMesh(rMesh),
        posX(posX),
        posY(posY){

        const Mesh::MeshData & mesh = rMesh->getMesh();
        ksi =  std::fmin( mesh.nx/2, mesh.ny/2);
        minX = mesh.x0;
        minY = mesh.y0;
        maxX = mesh.x0 + (mesh.nx - 1) * mesh.dx;
        maxY = mesh.y0 + (mesh.ny - 1) * mesh.dy;

    }

    Math::Position3D process(const Math::Position3D &velocity, const Accel::AccelOutputData &data);
    double checkXY( double pos, double max,  double min);

    double posX;
    double posY;
    static constexpr double adjCoef = 3;

    /// True if the line (x0,y0) -> (x,y) crosses a wall (obstacle)
    bool checkWall(double x1, double y1, double x2, double y2);

    /// True if black nearest mesh node
    bool checkBlack(double x, double y);

};

}
}
