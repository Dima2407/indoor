//
// Created by Igor Maschikevich on 6/8/2017.
//

//#pragma once

#include "Navigator/Accel/TrajectoryDetection.h"
#include "Navigator/Mesh/RectanMesh.h"

namespace Navigator {
namespace Accel {
Math::Position3D TrajectoryDetection::process(const Math::Position3D &velocity )
//Math::Position3D TrajectoryDetection::process(const Math::Position3D &velocity, Mesh::RectanMesh &mesh)
{
    using namespace Math;
    posX = posX + adjCoef * velocity.x * samplePeriod;
    posY = posY + adjCoef * velocity.y * samplePeriod;

//    constexpr double nx = 5, ny = 4;
//    constexpr double dx = 2.0, dy = 3.0;
//    constexpr double x0 = 1, y0 = 1;


//    Mesh::RectanMesh rectanmesh(nx, ny, dx, dy, x0, y0);
//    rectanmesh.getMesh();
    int Xmin = mesh.getMesh().x0;
    int Ymin = mesh.getMesh().y0;
    int Xmax = mesh.getMesh().x0 + (mesh.getMesh().nx - 1) * mesh.getMesh().dx;
    int Ymax = mesh.getMesh().y0 + (mesh.getMesh().ny - 1) * mesh.getMesh().dy;



    Position3D positionAfter(ChechX(posX, Xmax, Xmin), ChechY(posY, Ymax, Ymin), 0.0);
    return rectanmesh.process(positionAfter);
}

}
}
