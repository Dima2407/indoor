//
// Created by  Oleksiy Grechnyev on 4/21/2017.
//

#include <cmath>
#include <algorithm>

#include "findNearest.h"

//--------------------------------------------------------------------------
// Check if 2 doubles are equal with accuracy
inline bool approxEq(double a, double b) {
    constexpr double ACCURACY = 1.0e-10;

    return fabs(a - b) < ACCURACY;
}
//--------------------------------------------------------------------------
int findNearest(const MeshData &mesh, const MaskData &mask, int ix0, int iy0) {
    using namespace std;
    // The algorithm is like this: search over the rectangular shell k
    // for k=1, 2, 3 .. until found

    if (ix0 < 0 || ix0 >= mesh.nx || iy0 < 0 || iy0 >= mesh.ny)
        throw std::runtime_error("wrong index in findNearest.");

    // Find the max k
//    cout << "ix0 = " << ix0 << " , iy0 = " << iy0 << endl;

    // The algorithm goes like this : first we define scale and search in distance ranges (circles)
    // 0..scale, then scale..2scale etc.
    double scale = fmax(mesh.dx, mesh.dy) * 5.1; // The scale is somewhat arbitrary

    // Now the maximum distance from ix0, iy0 to any site
    double maxDist = sqrt(pow(mesh.dx * max(ix0, mesh.nx - ix0 - 1), 2.0) +
                          pow(mesh.dy * max(iy0, mesh.ny - iy0 - 1), 2.0));

//    cout << "scale = " << scale << " , maxDist = " << maxDist << endl;

    int bestInd = 0; // Index of bestDist2
    double bestDist2 = nan(""); // Best distance^2
    bool found = false;

    // We loop over the rings, double the radius every time
    bool firstRing = true;
    for (double rad = scale; rad < 2*maxDist; rad *= 2, firstRing=false) {

//        cout << "rad = " << rad << endl;

        // Rad in the units of dx, dy
        int rx = (int) (rad / mesh.dx);
        int ry = (int) (rad / mesh.dy);

        // Boundaries from rx, ry and mesh size
        int x1 = max(0, ix0 - rx);
        int x2 = min(mesh.nx - 1, ix0 + rx);
        int y1 = max(0, iy0 - ry);
        int y2 = min(mesh.ny - 1, iy0 + ry);

        // Now we loop over all nodes of the mesh within rx, ry
        for (int ix = x1; ix <= x2; ++ix) {
            for (int iy = y1; iy <= y2; ++iy) {
                
                // Check if it's white, the cheapest check first
                int currInd = mesh.index(ix, iy);
                if (!mask.data[currInd]) {
                    
                    // White checking distance
                    
                    // Distance between (ix, iy) and (ix0, iy0) squared
                    // I tried to optimize here, no sqrt
                    double tx = (ix-ix0)*mesh.dx;
                    double ty = (iy-iy0)*mesh.dy;
                    double dist2 = tx*tx + ty*ty;
                    double rad2 = rad*rad;
                
                    // Check if the node ix, iy is in the ring
                    if (dist2 <= rad2 && (dist2 >= rad2/4 || firstRing)) {
                        // Node ix, iy = white and in the ring, processing

                        if (!found) {
                            // First white node found in this run of findNearest
                            found = true;
                            bestDist2 = dist2;
                            bestInd = currInd;
                        } else {
                            // Find the enarest white node
                            // But Ignore if the distance is approximately the same
                            if (dist2 < bestDist2 && !approxEq(dist2, bestDist2)) {
                                bestDist2 = dist2;
                                bestInd = currInd;
                            }
                        }
                    }
                } // if dist
            } // for iy
        } // for ix

        if (found)
            break;
    } // for rad

    if (!found)
        throw std::runtime_error("Not found in findNearest.");

    return bestInd;
}
