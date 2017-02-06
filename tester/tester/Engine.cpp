//
// Created by  Oleksiy Grechnyev on 2/4/2017.
//

#include "Engine.h"
#include "MyBridge.h"

#include <iostream>
#include <fstream>

namespace tester {

    void Engine::readBeaconsDAT() {
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


        beacons.clear(); // Just in case
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

    void Engine::readMeasurementsDAT(const char *fileName) {
        using namespace std;


        /*  // For now: just something trivial
          // My funny location
          double x0 = 0.1717, y0 = 0.314159;

          events.clear(); // Just in case
          // Let's add some measurements, 1/beacon
          for (MyBeacon b: beacons) {
              // I use a fake timestamp=1 for now
              events.push_back(Event(b.hash, b.txPower, b.calcRssiPos(x0, y0, 0), 1));
          }*/

        ifstream in(fileName);

        if (!in) {
            cerr << "Cannot open input file : " << fileName << endl;
            exit(1);
        }

        Event e;

        while (in >> e) events.push_back(e);

        in.close();
    }

    void Engine::run() {
        using namespace std;

        // Send beacons to the bridge
        MyBridge::init();
        for (MyBeacon const & b: beacons) MyBridge::newBeacon(b);

        // Send measurements to the bridge
        for (Event const & e: events) {
            MyBridge::newMeasurement(e.hash, e.txPower, e.rssi, e.timestamp);
            // Print position after each measurement
            cout << e.timestamp << " : " << MyBridge::getX() << ", " << MyBridge::getY() << ", " << MyBridge::getZ() << endl;
        }

    }


}