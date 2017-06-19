//
// Created by Igor Maschikevich on 6/8/2017.
//

#include <cmath>
#include "Navigator/Accel/TrajectoryDetection.h"

namespace Navigator {
namespace Accel {
Math::Position3D TrajectoryDetection::process(const Accel::AccelOutputData &data )
{
    using namespace Math;
    using namespace Mesh;
    double dt = data.timeDiff;
    vX = algorithmZUPT(data.ax, vX, data.isStationary, dt);
    vY = algorithmZUPT(data.ay, vY, data.isStationary, dt);

    double posX0 = posX;
    double posY0 = posY;

    posX += adjCoef * vX * dt;
    posY += adjCoef * vY * dt;

    posX = checkXY(posX, maxX, minX);
    posY = checkXY(posY, maxY, minY);

    if (checkWall(posX0, posY0, posX, posY)) {

        if (!checkWall(posX0, posY0, posX0, posY))
            posX = posX0;
        else if (!checkWall(posX0, posY0, posX, posY0))
            posY = posY0;
    }

    Position3D positionAfter(posX, posY, 0.0);

    return rMesh->process(positionAfter);
}

double TrajectoryDetection::algorithmZUPT (double axAy, double satrtVelocity, bool isStationary, double timeDiff){
    double velocity;
    if (isStationary == false){
        velocity = satrtVelocity + globG * axAy * timeDiff;
    }
    else{
        velocity = 0;
    }
    if ( velocity > maxV){
        velocity = maxV;
    }
    return velocity;
}

double TrajectoryDetection::checkXY( double pos, double max,  double min){
    if (pos < min)
        pos = min;
    else if (pos > max)
        pos = max;
    return pos;
}

bool TrajectoryDetection::checkBlack(double x, double y)
{
    bool res;
    const Mesh::MeshData & mesh = rMesh->getMesh();
    // Find the mesh node nearest to inPos (iX = 0 .. nx-1, iY = 0..ny-1)
    int iX = mesh.x2ix(x);
    int iY = mesh.y2iy(y);
    // Calculate the single value index (ind == 0 .. size-1)
    int ind = iX * mesh.ny + iY;

    if(ind == rMesh->getMaskTable()[ind]){
        res = false;
    }
    else if(ind != rMesh->getMaskTable()[ind]){
        res = true;
    }
    return res;
}

bool TrajectoryDetection::checkWall(double x1, double y1, double x2, double y2)
{
    double length = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));

    double t = 0;
    double inPosX, inPosY;

    for (int ksiP = 0; ; ++ksiP) {
        t = (ksiP * ksi) / length;
        inPosX = x1 + (x2 - x1) * t;
        inPosY = y1 + (y2 - y1) * t;

        if (t >= 1.0)
            return checkBlack(x2, y2);

        else if(checkBlack(inPosX, inPosY))
            return true;
    }
}
}
}
