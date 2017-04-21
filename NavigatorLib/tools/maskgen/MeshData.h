//
// Created by  Oleksiy Grechnyev on 4/21/2017.
//

#pragma once

#include <cmath>
#include <iostream>
#include <fstream>

/** @brief Mesh configuration for maskgen
 *
 * Can be read from a file
 */
struct MeshData {
public: // === Constructors
    MeshData() {}

    MeshData(const std::string &fileName) {
        using namespace std;

        cout << "Reading mesh from file " << fileName << "\n";

        ifstream in(fileName);
        if (!in) {
            cerr << "Error: Cannot open file " << fileName << endl;
            exit(1);
        }
        in >> nx >> ny >> dx >> dy >> x0 >> y0;
        if (!in) {
            std::cerr << "Error reading data from file " << fileName << endl;
            exit(1);
        }
        in.close();
    }

public: //======= Methods
    /// The mesh index 0 .. nx*ny
    int index(int ix, int iy) const {
        return ix*ny + iy;
    }

public: // ======= Data

    /// Mesh size : X
    int nx = 0;
    /// Mesh size : Y
    int ny = 0;
    /// Mesh step : X
    double dx = std::nan("");
    /// Mesh step : Y
    double dy = std::nan("");
    /// Mesh origin: X
    double x0 = std::nan("");
    /// Mesh origin: Y
    double y0 = std::nan("");
};



