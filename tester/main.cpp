#include <iostream>
#include <vector>

#include "MyBeacon.h"
#include "MyBridge.h"

int main() {
    using namespace std;
    using namespace tester;

    // List of beacons
    vector<MyBeacon> beacons;

    // Let's create some beacons (x, y, z, hash, txPower, damp)
    beacons.push_back(MyBeacon(0.0, 0.0, 0.0, 1, 1.0, 1.0));
    beacons.push_back(MyBeacon(1.0, 0.0, 0.0, 2, 1.0, 1.0));
    beacons.push_back(MyBeacon(0.0, 1.0, 0.0, 3, 1.0, 1.0));
    beacons.push_back(MyBeacon(1.0, 1.0, 0.0, 4, 1.0, 1.0));

    // Let's send them to the bridge
    MyBridge::init();
    for (MyBeacon b: beacons) MyBridge::newBeacon(b);



    return 0;
}