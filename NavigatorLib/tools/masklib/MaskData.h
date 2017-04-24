//
// Created by  Oleksiy Grechnyev on 4/21/2017.
//

#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

/** @brief A black-and--white mask as a vector of int
 *
 *  Mask : 0 = white (allowed), 1 = black (forbidden)
 *  size = nx*ny
 *  index = ix * ny + iy
 *  ix = 0, ... nx-1
 *  iy = 0, ... ny-1
 *  index = 0, ..., size-1
 */
struct MaskData {
    MaskData() {}

    /// Read a mask of size size from the file fileName
    MaskData(int size, const std::string &fileName) :
            data(size) {
        using namespace std;

        cout << "Reading mask from file " << fileName << "\n";

        // Open file
        ifstream in(fileName);
        if (!in) {
            cerr << "Error: Cannot open file " << fileName << endl;
            exit(1);
        }

        // Read data
        for (int i=0; i < size; i++) {
            int val;
            in >> val;
            if (!in || val < 0 || val > 1) {
                std::cerr << "Error reading data from file " << fileName << endl;
                exit(1);
            } else
                data[i] = val;
        }

        // Close file
        in.close();
    }

    /// For each index: 0 = white (allowed), 1 = black (forbidden)
    std::vector<int> data;
};



