//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>


// This includes everything you need
#include "Navigator.h"

// There are a few namespaces in the librrary

int main()
{
    using namespace std;
    using Navigator::Math::Position3D;
    using namespace Navigator::Mesh;
    using namespace Navigator::Accel;

    // Some mesh, no walls at present
    constexpr double nx = 201, ny = 201;
    constexpr double dx = 0.1, dy = 0.1;
    constexpr double x0 = -10.0, y0 = -10.0;
    shared_ptr<RectanMesh> rMesh = make_shared<RectanMesh>(nx, ny, dx, dy, x0, y0);

//   if( rMesh == nullptr){
//      } else if (rMesh != nullptr){};
    // Create a mask table
    vector<int> mTable(nx*ny);

    // Fill the table with the "identity" operation (all white)
    for (int i = 0; i < nx*ny; i++)
        mTable[i] = i;

    // Do we need black nodes here
    // Make a few changes: exclude nodes 6, 10, 14
    // This means (3, 7), (5, 7), (7, 7)
//    mTable[6] = 2;
//    mTable[10] = 9;
//    mTable[14] = 18;

    // Load the table into the mesh
    rMesh->setMaskTable(mTable);

    // Configuration
    AccelConfig config;
    config.mapOrientationAngle = 0; // Map orientation angle in degrees from the server
    config.useFilter = false; // Should be true for real cases

    double startX = 0, startY = 0; // Start coordinates

    StandardAccelNavigator standardAccelNavigator(rMesh, startX, startY, config);

    for (int i = 0; i < 10; ++i){
        // Uniform acceleration in the -x direction
        AccelReceivedData ard{i*0.1, -1.0, 0.0, -1.0, 0.0, 0.0, 0.0};

        Position3D p = standardAccelNavigator.process(ard);

        cout << p.x << " "  << p.y << " "  << p.z << " "  << endl;
    }

    return 0;
}
