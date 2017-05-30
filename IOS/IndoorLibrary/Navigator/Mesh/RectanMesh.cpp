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
    }
}