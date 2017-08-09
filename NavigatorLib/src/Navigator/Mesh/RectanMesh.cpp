//
// Created by  Oleksiy Grechnyev on 4/20/2017.
//

#include <cmath>

#include "Navigator/Mesh/RectanMesh.h"

namespace Navigator {
    namespace Mesh {
//=========================================================

        Math::Position3D RectanMesh::process(const Math::Position3D &inPos) const{

            // Find the mesh node nearest to inPos (iX = 0 .. nx-1, iY = 0..ny-1)
            int iX = mesh.x2ix(inPos.x);
            int iY = mesh.y2iy(inPos.y);

            // Calculate the single value index (ind == 0 .. size-1)
            int ind = iX*mesh.ny + iY;

            // Apply the mask table only if it is of the correct size (nx*ny)
            if (maskTable.size() == mesh.nx*mesh.ny)
                ind = maskTable[ind];

            // Return the node with index ind and z-coordinate from inPos
            double x = mesh.ix2x(ind / mesh.ny);
            double y = mesh.iy2y(ind % mesh.ny);
            return Math::Position3D(x, y, inPos.z);
        }
//=========================================================

        Math::Position3D RectanMesh::checkEdges(Math::Position3D inPos) const {
            if (inPos.x < minX)
                inPos.x = minX;
            else if (inPos.x > maxX)
                inPos.x = maxX;

            if (inPos.y < minY)
                inPos.y = minY;
            else if (inPos.y > maxY)
                inPos.y = maxY;

            return inPos;
        }
//=========================================================
        void RectanMesh::init() {
            xi = std::fmin(mesh.dx / 2, mesh.dy / 2);
            minX = mesh.x0;
            minY = mesh.y0;
            maxX = mesh.x0 + (mesh.nx - 1) * mesh.dx;
            maxY = mesh.y0 + (mesh.ny - 1) * mesh.dy;
        }
//=========================================================

        bool RectanMesh::checkWall(double x1, double y1, double x2, double y2)  const{
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
//=========================================================

        bool RectanMesh::checkBlack(double x, double y)  const{
            if (isOutsideMap(x, y))
                return true;

            // Find the mesh node nearest to inPos (iX = 0 .. nx-1, iY = 0..ny-1)
            int iX = mesh.x2ix(x);
            int iY = mesh.y2iy(y);
            // Calculate the single value index (ind == 0 .. size-1)
            int ind = iX * mesh.ny + iY;

            return !maskTable.empty() && ind!=maskTable[ind];  // true for black
        }
//=========================================================

        double RectanMesh::checkX(double x) const {
            if (x < minX)
                return minX;
            else if (x > maxX)
                return maxX;
            else
                return x;
        }
//=========================================================

        double RectanMesh::checkY(double y)  const{
            if (y < minY)
                return minY;
            else if (y > maxY)
                return maxY;
            else
                return y;
        }
//=========================================================

    }
}