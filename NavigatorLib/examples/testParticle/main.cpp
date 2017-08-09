//
// Created by  Oleksiy Grechnyev on 8/7/2017.
//

#include <iostream>
#include <cmath>
#include <cstdio>
#include <memory>

#include "Navigator.h"

int main(){
    using namespace std;
    using namespace Navigator::Particles;
    using namespace Navigator::Math;
    using namespace Navigator::Mesh;

    cout << "Goblins WON !" << endl;

    // Some config for fun
    ParticleNavigatorConfig config;
    config.useWalls = false;
    config.useMeshMask = false;
    config.useMapEdges = false;

    // Set up a simple mesh
    // Create a simple 5x4 rect mesh
    // x -coords: 1, 3, 5, 7, 9
    // y -coords: 1, 4, 7, 10
    constexpr double nx = 5, ny = 4;
    constexpr double dx = 2.0, dy = 3.0;
    constexpr double x0 = 1, y0 = 1;
    std::unique_ptr<RectanMesh> rMesh = make_unique<RectanMesh>(nx, ny, dx, dy, x0, y0);
    // Create a mask table : 20 = nx*ny = 5*4
    vector<int> mTable(nx*ny);
    // Fill the table with the "identity" operation
    for (int i = 0; i < nx*ny; i++)
        mTable[i] = i;
    // Make a few changes: exclude nodes 6, 10, 14
    // This means (3, 7), (5, 7), (7, 7)
    mTable[6] = 2;
    mTable[10] = 9;
    mTable[14] = 18;
    // Load the table into the mesh
    rMesh->setMaskTable(mTable);

    // Now our lambda to test
    auto lam = [&rMesh, &config](const Position2D &p1,
                      const Position2D &p2) -> bool {
        if (rMesh==nullptr)
            return true; // Always allowed
        else if (config.useWalls)  // Check walls+mask (slower)
            return  !rMesh->checkWall(p1.x, p1.y, p2.x, p2.y);
        else if (config.useMeshMask)  // Check endpoints only (faster)
            return !rMesh->checkBlack(p1.x, p1.y) && !rMesh->checkBlack(p2.x, p2.y);
        else if (config.useMapEdges)  // Check map edges only
            return !rMesh->isOutsideMap(p1.x, p1.y) && !rMesh->isOutsideMap(p2.x, p2.y);
        else
            return true; // Always allowed
    };

    cout << "result = " << boolalpha << lam({5.0, 7.0}, {5.0, 10.01});

    return 0;
}