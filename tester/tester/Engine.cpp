//
// Created by  Oleksiy Grechnyev on 2/4/2017.
//

#include "Engine.h"

#include <iostream>
#include <fstream>

namespace tester {

    void Engine::readBeacons() {
        using namespace std;

        // Let's read beacons from the input file in_beacons.dat
        // Format:   x y z hash txPower damp
        ifstream in("in_beacons.dat");

        if (!in) {
            cerr << "Cannot open input file !" << endl;
            exit(1);
        }

        double x, y, z, txPower, damp;
        long long hash;


        cout << "Reading beacons :" << endl << endl;

        // Read until EOF or broken line
        while (in >> x >> y >> z >> hash >> txPower >> damp) {
            cout << "Beacon : " << x << " " << y << " " << z << " " << hash << " " << txPower << " " << damp << endl;
            beacons.push_back(MyBeacon(x, y, z, hash, txPower, damp));
        }

        //  Check that there are at least 3 beacons
        if (beacons.size() < 3) {
            cerr << "ERROR: Need at least 3 beacons !" << endl;
            exit(1);
        }

        in.close();
    }
}