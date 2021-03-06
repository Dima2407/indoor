//
// Created by Igor Maschikevich on 6/8/2017.
//

#include <cmath>
#include "Navigator/Accel/TrajectoryDetection.h"

namespace Navigator {
namespace Accel {
Math::Position3D TrajectoryDetection::processZUPT(const Accel::AccelOutputData &data)
{
    using namespace Math;
    using namespace Mesh;
    double dt = data.timeDiff;
    //    calculation velocity for aX
    vX = algorithmZUPT(data.ax, vX, data.isStationary, dt);
    //    calculation velocity for aY
    vY = algorithmZUPT(data.ay, vY, data.isStationary, dt);

    double posX0 = posX;
    double posY0 = posY;

    posX += config.adjCoef * vX * dt;
    posY += config.adjCoef * vY * dt;

    if (rMesh !=nullptr){

        if (config.useMapEdges) {
            posX = checkXY(posX, maxX, minX);
            posY = checkXY(posY, maxY, minY);
        }

        if (config.useWalls) {
            if (checkWall(posX0, posY0, posX, posY)) {
                if (!checkWall(posX0, posY0, posX0, posY))
                    posX = posX0;
                else if (!checkWall(posX0, posY0, posX, posY0))
                    posY = posY0;
            }
        }
    }
    Position3D position(posX, posY, 0.0);
    if(rMesh != nullptr && config.useMeshMask)
        return rMesh->process(position);
    else
        return position;
}

//==============================================================================
Math::Position3D TrajectoryDetection::processDummy(const AccelOutputData &data)
{

    using namespace Math;
    using namespace Mesh;
    double dt = data.timeDiff;

    double posX0 = posX;
    double posY0 = posY;

    if (!data.isStationary) {
        posX += sin(data.yaw)*config.userAverageVelocity*dt;
        posY += cos(data.yaw)*config.userAverageVelocity*dt;

        if (rMesh !=nullptr){

            if (config.useMapEdges) {
                posX = checkXY(posX, maxX, minX);
                posY = checkXY(posY, maxY, minY);
            }

            if (config.useWalls) {
                if (checkWall(posX0, posY0, posX, posY)) {
                    if (!checkWall(posX0, posY0, posX0, posY))
                        posX = posX0;
                    else if (!checkWall(posX0, posY0, posX, posY0))
                        posY = posY0;
                }
            }
        }
    }

    Position3D position(posX, posY, 0.0);
    if(rMesh != nullptr && config.useMeshMask)
        return rMesh->process(position);
    else
        return position;
}
//==============================================================================

double TrajectoryDetection::algorithmZUPT (double aXaY, double startVelocity, bool isStationary, double timeDiff){
    double velocity;
    if (isStationary == false){
        velocity = startVelocity + config.globG * aXaY * timeDiff;
    }
    else{
        velocity = 0;
    }
    if ( velocity > config.maxV){
        velocity = config.maxV;

    }else if(velocity <- config.maxV){
        velocity = - config.maxV;
    }
    return velocity;
}
//The function checks whether a given point is within the map
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
        t = (ksiP * xi) / length;
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
