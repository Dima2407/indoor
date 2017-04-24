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

    MeshData(int nx, int ny, double dx, double dy, double x0, double y0) : nx(nx), ny(ny),
                                                                           dx(dx), dy(dy),
                                                                           x0(x0), y0(y0) {}


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
        return ix * ny + iy;
    }

    /// Distance between 2 mesh nodes
    double dist(int ix1, int iy1, int ix2, int iy2) const {
        // I don't use asserts anymore !
        if (ix1 < 0 || ix1 >= nx || iy1 < 0 || iy1 >= ny ||
            ix2 < 0 || ix2 >= nx || iy2 < 0 || iy2 >= ny)
            throw std::runtime_error("wrong index in MeshData::dist().");

        double lx = (ix2 - ix1) * dx;
        double ly = (iy2 - iy1) * dy;
        return std::sqrt(lx * lx + ly * ly);
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



