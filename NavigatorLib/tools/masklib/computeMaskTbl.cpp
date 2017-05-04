//
// Created by  Oleksiy Grechnyev on 4/21/2017.
//

#include <iostream>
#include <cmath>

#include "./findNearest.h"

#include "./computeMaskTbl.h"


std::vector<int> computeMaskTbl(const MeshData &mesh, const MaskData &mask) {
    using namespace std;

    int size = mesh.nx * mesh.ny;
    std::vector<int> result(size);

    // Check that the mask is not all-black
    {
        int tmp = 1;
        for (int i = 0; i < size; ++i)
            tmp = tmp && mask.data[i];

        if (tmp){
            cerr << "Error: The mask is all-black !\n";
            exit(1);
        }
    }

    // We start with an identity table
    for (int i = 0; i < size; ++i)
        result[i] = i;

    // Now we loop over all nodes of the mesh
    for (int ix = 0; ix < mesh.nx; ++ix) {
        // if (ix % 20 == 0)
            // cout << "ix = " << ix << endl;
        
        for (int iy = 0; iy < mesh.ny; ++iy) {
            
            //if (iy % 20 == 0)
               // cout << "iy = " << iy << endl;
            
            int currInd = mesh.index(ix, iy);
            if (mask.data[currInd]) {
                // The node is black
                result[currInd] = findNearest(mesh, mask, ix, iy);
            }
        }
    }


    return result;
}
