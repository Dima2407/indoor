//
// Created by  Oleksiy Grechnyev on 4/20/2017.
//

#include <cmath>

#include "Navigator/Mesh/RectanMesh.h"

namespace Navigator {
    namespace Mesh {

        Math::Position3D RectanMesh::process(const Math::Position3D &inPos) {

            // Find the mesh node nearest to inPos (iX = 0 .. nx-1, iY = 0..ny-1)
            int iX = (int) lround((inPos.x - x0)/dx);
            int iY = (int) lround((inPos.y - y0)/dy);

            // Check the boundaries
            if (iX<0)
                iX=0;
            if (iY<0)
                iY=0;
            if (iX >= nx)
                iX = nx-1;
            if (iY >= ny)
                iY = ny-1;

            // Calculate the single value index (ind == 0 .. size-1)
            int ind = iX*ny + iY;

            // Apply the mask table only if it is of the correct size (nx*ny)
            if (maskTable.size() == nx*ny)
                ind = maskTable[ind];

            // Return the node with index ind and z-coordinate from inPos
            double x = (ind / ny) * dx + x0;
            double y = (ind % ny) * dy + y0;
            return Math::Position3D(x, y, inPos.z);
        }
    }
}