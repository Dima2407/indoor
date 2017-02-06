//
// Created by  Oleksiy Grechnyev on 2/6/2017.
//

#include "MyBeaconList.h"

#include <iostream>
#include <fstream>
#include <cassert>

namespace tester {

    bool MyBeaconList::readDAT(const char * fileName) {
        using namespace std;

        // Let's read beacons from the input file in_beacons.dat
        // Format:   x y z hash txPower damp
        ifstream in(fileName);

        if (!in) {
            cerr << "ERROR: Cannot open input file : " << fileName << endl;
            return false;
        }

        double x, y, z, txPower, damp;
        long long hash;


        beacons.clear(); // Just in case
        cout << "Reading beacons from DAT file : " << fileName << endl << endl;

        // Read until EOF or broken line
        while (in >> x >> y >> z >> hash >> txPower >> damp) {
            cout << "Beacon : " << x << " " << y << " " << z << " " << hash << " " << txPower << " " << damp << endl;
            beacons.push_back(MyBeacon(x, y, z, hash, txPower, damp));
        }

        in.close();

        return true;
    }

    bool MyBeaconList::readJSON(const char * fileName) {

    }

    bool MyBeaconList::beaconExists(long long hash) {
        using namespace std;

        for (MyBeacon const &b: beacons) {
            if (b.hash == hash) return true;
        }

        return false;
    }

    const MyBeacon &MyBeaconList::findBeacon(long long hash) {
        using namespace std;

        // Beacon hash must exist
        assert(beaconExists(hash));

        for (MyBeacon const &b: beacons) {
            if (b.hash == hash) return b;
        }

        exit(2); // Not found: this shouldn't happen
    }
}