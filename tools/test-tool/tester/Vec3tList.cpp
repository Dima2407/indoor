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
            out << point << endl;
        }

        if (!out) {
            cerr << "ERROR: Cannot write output file : " << fileName << endl;
            return false;
        }

        out.close();

        return true;
    }
}
