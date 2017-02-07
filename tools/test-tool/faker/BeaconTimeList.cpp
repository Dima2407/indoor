//
// Created by  Oleksiy Grechnyev on 2/7/2017.
//

#include "BeaconTimeList.h"

#include <iostream>
#include <fstream>

namespace faker {


    bool BeaconTimeList::readDAT(std::string const &fileName) {
        using namespace std;

        cout << endl << "Reading beacon time data from DAT file " << fileName << endl << endl;

        ifstream in(fileName);

        if (!in) {
            cerr << "ERROR: Cannot open input file : " << fileName << endl;
            exit(1);
        }

        BeaconTime bt;

        beaconTimes.clear(); // Just in case
        while (in >> bt) {
            beaconTimes.push_back(bt); // Add to list
            cout << bt << endl;
        }

        return true;
    }

    bool BeaconTimeList::readAuto(std::string const &fileName) {
        return readDAT(fileName);
    }
}