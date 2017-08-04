//
// Created by  Oleksiy Grechnyev on 4/20/2017.
//

#include <cmath>

#include "Navigator/Mesh/RectanMesh.h"

namespace Navigator {
    namespace Mesh {

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

        Math::Position3D RectanMesh::checkEdges(Math::Position3D inPos) const {
            double x2 = mesh.x0 + mesh.dx*(mesh.nx-1);
            double y2 = mesh.y0 + mesh.dy*(mesh.ny-1);

            if (inPos.x < mesh.x0)
                inPos.x = mesh.x0;
            else if (inPos.x > x2)
                inPos.x = x2;

            if (inPos.y < mesh.y0)
                inPos.y = mesh.y0;
            else if (inPos.y > y2)
                inPos.y = y2;

            return inPos;
        }
    }
}