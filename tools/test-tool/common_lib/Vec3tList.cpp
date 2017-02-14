//
// Created by  Oleksiy Grechnyev on 2/8/2017.
//

#include "Vec3tList.h"

#include <iostream>
#include <fstream>

namespace tester {
    bool Vec3tList::writeDAT(std::string const &fileName) {

        using namespace std;

        cout << endl << "Writing trajectory r(t) to DAT file : " << fileName << endl << endl;

        // Write events to the file
        ofstream out(fileName);

        if (!out) {
            cerr << "ERROR: Cannot create/replace output file : " << fileName << endl;
            return false;
        }

        for (Vec3t const & point: points){
            out << fixed << point << endl;
        }

        if (!out) {
            cerr << "ERROR: Cannot write output file : " << fileName << endl;
            return false;
        }

        out.close();

        return true;
    }

    bool Vec3tList::readDAT(std::string const &fileName) {
        using namespace std;

        cout << endl << "Reading the (t,r) data from DAT file " << fileName << endl << endl;

        // Open file
        ifstream in(fileName);

        if (!in) {
            cerr << "ERROR: Cannot open input file : " << fileName << endl;
            return false;
        }

        Vec3t point;

        points.clear(); // Clear the list

        // Read data until EOF
        while (in >> point) {
            cout << "ppoint = " << point << endl;
            points.push_back(point); // Add to list
        }

        return true;
    }
}
