#include <iostream>
#include <fstream>
#include <vector>

#include "MyBeacon.h"
#include "MyBridge.h"

int main() {
    using namespace std;
    using namespace tester;

    // List of beacons
    vector<MyBeacon> beacons;

    // Let's read beacons from the input file in_beacons.dat
    // Format:   x y z hash txPower damp
    ifstream in("in_beacons.dat");
    // in.open("in_beacons.dat");

    if (!in) {
        cerr << "Cannot open input file !" << endl;
        exit(1);
    }

    double x, y, z, txPower, damp;
    long long hash;

    // Read until EOF or broken line
    while (in >> x >> y >> z >> hash >> txPower >> damp) {
        cout << "Beacon : " << x << " " << y << " " << z << " " << hash << " " << txPower << " " << damp << endl;
        beacons.push_back(MyBeacon(x, y, z, hash, txPower, damp));
    }

    in.close();

    // Let's send them to the bridge
    MyBridge::init();
    for (MyBeacon b: beacons) MyBridge::newBeacon(b);

    // My funny location
    double x0 = 0.314, y0 = 0.455;

    // Let's add some measurements, 1/beacon
    for (MyBeacon b: beacons) {
        // I use a fake timestamp=1 for now
        MyBridge::newMeasurement(b.hash, b.txPower, b.calcRssiPos(x0, y0, 0), 1);
    }

    // Print the result
    cout << "x = " << MyBridge::getX() << endl;
    cout << "y = " << MyBridge::getY() << endl;
    cout << "z = " << MyBridge::getZ() << endl;

    return 0;
}