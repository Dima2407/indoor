//
// Created by  Oleksiy Grechnyev on 4/21/2017.
//

#include <iostream>
#include <fstream>
#include <vector>

#include "Navigator.h"

// Test the post-processing of a Position3D using a mesh and a mask table
// This version reads files mesh.in and masktable.out generated by maskgen
int main(){
    using namespace std;
    using namespace Navigator::Mesh;
    using namespace Navigator::Math;


    // Create the mesh struct (mesh + masktable) from files
    RectanMesh mesh("in/mesh.in", "in/masktable.out");

    //-------------------------------------------

    cout << "Guess the mesh ! Enter x, y :\n";
    double x,y;

    cin >> x >> y;

    Position3D result = mesh.process(Position3D(x, y, 0));

    cout << "Result = (" << result.x << ", " << result.y << ")\n";

    return 0;
}
