//
// Created by  Oleksiy Grechnyev on 4/21/2017.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

#include "./MeshData.h"
#include "./MaskData.h"
#include "./computeMaskTbl.h"

int main(){
    using namespace std;

    cout << "Mask Table Generator by Oleksiy Grechnyev \n";

    // Read the input mesh from file
    MeshData mesh("mesh.in");

    cout << "Rectangular mesh: \n";
    cout << "nx = " << mesh.nx << ", ny = " << mesh.ny << "\n";
    cout << "dx = " << mesh.dx << ", dy = " << mesh.dy << "\n";
    cout << "x0 = " << mesh.x0 << ", y0 = " << mesh.y0 << "\n";

    int size = mesh.nx * mesh.ny; // Mesh size

    // Read the mask from file
    MaskData mask(size, "mask.in");

    // Calculate the mask table from the mask
    vector<int> maskTbl = computeMaskTbl(mesh, mask);

    // Write the result
    ofstream out("masktable.out");
    cout << "Writing mask table to file masktable.out \n";
    for (int ix = 0; ix < mesh.nx; ++ix) {
        for (int iy = 0; iy < mesh.ny; ++iy) {
            out << setfill(' ') << setw(4) << maskTbl[mesh.index(ix, iy)] << " ";
        }
        out << endl;
    }
    out.close();

    return 0;
}