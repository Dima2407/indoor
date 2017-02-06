//
// Created by  Oleksiy Grechnyev on 2/6/2017.
//

#include "Vec3List.h"

#include <iostream>
#include <fstream>

namespace tester {

    bool Vec3List::writeDAT(const char *fileName) {
        using namespace std;

        // Write events to the file
        ofstream out(fileName);

        if (!out) {
            cerr << "ERROR: Cannot create/replace output file : " << fileName << endl;
            return false;
        }

        for (Vec3 const & point: points){
            out << fixed << point << endl;
        }

        if (!out) {
            cerr << "ERROR: Cannot write output file : " << fileName << endl;
            return false;
        }

        out.close();

        return true;
    }
}