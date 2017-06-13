//
// Created by Igor Maschikevich on 6/8/2017.
//
#include "Navigator/Math/Position3D.h"
#include "Navigator/Mesh/MeshData.h"
#include "AccelOutputData.h"
#include "AlgorithmZUPT.h"
#pragma once
namespace Navigator {
namespace Accel {


class TrajectoryDetection
{
public:
    TrajectoryDetection(){}
//    Math::Position3D process(const Math::Position3D &velocity, Mesh::RectanMesh &mesh);
    Math::Position3D process(const Math::Position3D &velocity);

    float posX = 0;
    float posY = 0;
    const float adjCoef = 3;
    float samplePeriod = 0.33;

    //The function checks whether a given point within the map
    int  ChechX(int posX,int Xmax, int Xmin){
        if (posX < Xmin)
            posX = Xmin;
        else if (posX > Xmax)
            posX = Xmax;
        return posX;
    }
    //The function checks whether a given point within the map
    int ChechY(int posY,int Ymax, int Ymin){
        if (posY < Ymin)
            posY = Ymin;
        else if (posY > Ymax)
            posY = Ymax;
        return  posY;
    }

    //The function checks if the given point crosses the wall
    //if yes return 1, else return 0.
    int ChechWall_XY(int posX, int posY, int Xmax, int Xmin, int Ymax, int Ymin){
        int res;
        if (posY == Ymin || posY == Ymax && posX >= Xmin && posX <= Xmax) {
            res = 1;
        }
        else if (posY >= Ymin && posY <= Ymax && posX == Xmin || posX == Xmax) {
            res = 1;
        } else {
            res = 0;
        }
        return res;
    }
};
}
}
