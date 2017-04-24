//
// Created by  Oleksiy Grechnyev on 4/21/2017.
//

#include <iostream>
#include <vector>

#include "Navigator.h"

// Test the post-processing of a Position3D using a mesh and a mask table
int main(){
    using namespace std;
    using namespace Navigator::Mesh;
    using namespace Navigator::Math;

    // Create a simple 5x4 rect mesh
    // x -coords: 1, 3, 5, 7, 9
    // y -coords: 1, 4, 7, 10
    constexpr double nx = 5, ny = 4;
    constexpr double dx = 2.0, dy = 3.0;
    constexpr double x0 = 1, y0 = 1;
    RectanMesh mesh(nx, ny, dx, dy, x0, y0);

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
    mesh.setMaskTable(mTable);

    cout << "Guess the mesh ! Enter x, y :\n";
    double x,y;


    cin >> x >> y;

    Position3D result = mesh.process(Position3D(x, y, 0));

    cout << "Result = (" << result.x << ", " << result.y << ")\n";

    return 0;
}
