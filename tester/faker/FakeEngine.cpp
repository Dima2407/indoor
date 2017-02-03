//
// Created by  Oleksiy Grechnyev on 2/3/2017.
//

#include "FakeEngine.h"
#include "BeaconTime.h"

#include <iostream>
#include <fstream>

namespace faker {

    // Static data, this is SO STUPID !!!
    // Stupid stupid C++, no problems like that in Java !
    std::vector<tester::MyBeacon> FakeEngine::beacons;
    Vec3 FakeEngine::point1, FakeEngine::point2;
    double FakeEngine::t1, FakeEngine::t2;
    double FakeEngine::ticksPerTimeUnit;

    void FakeEngine::readBeacons() {
        using namespace std;
        using namespace tester;

        // Let's read beacons from the input file in_beacons.dat
        // Format:   x y z hash txPower damp

        // Open file
        const char * fileName = "in_beacons.dat";
        ifstream in(fileName);
        if (!in) {
            cerr << "ERROR: Cannot open input file : " << fileName << endl;
            exit(1);
        }

        // Read data
        double x, y, z, txPower, damp;
        long long hash;

        cout << "Reading beacons :" << endl << endl;

        // Read until EOF or broken line
        while (in >> x >> y >> z >> hash >> txPower >> damp) {
            cout << "Beacon : " << x << " " << y << " " << z << " " << hash << " " << txPower << " " << damp << endl;
            beacons.push_back(MyBeacon(x, y, z, hash, txPower, damp));
        }

        in.close();

        //  Check that there are at least 3 beacons
        if (beacons.size() < 3) {
            cerr << "ERROR: Need at least 3 beacons !" << endl;
            exit(1);
        }
    }

    void FakeEngine::readInput() {
        using namespace std;
        using namespace tester;

        // Open file
        const char * fileName = "in_faker.dat";
        ifstream in(fileName);
        if (!in) {
            cerr << "ERROR: Cannot open input file : " << fileName << endl;
            exit(1);
        }

        // Read the data
        cout << endl << "Reading configuration :" << endl << endl;

        in >> t1 >> t2 >> ticksPerTimeUnit;
        cout << "t1 = " << t1 << ", t2 = " << t2 << ", ticksPerTimeUnit = " << ticksPerTimeUnit << endl;

        in >> point1 >> point2;
        cout << "point1 = " << point1 << endl;
        cout << "point2 = " << point2 << endl;

        if (!in) {
            cerr << "ERROR: Corrupt file : " << fileName << endl;
            exit(1);
        }

        cout << endl << "Reading beacon time data :" << endl << endl;

        BeaconTime bt;

        while (in >> bt) {
            cout << bt << endl;
        }

        in.close();
    }
}