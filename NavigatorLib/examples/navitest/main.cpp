//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <iomanip>
#include <cmath>
#include <vector>

// This includes everything you need
#include "Navigator.h"

// There are a few namespaces in the librrary
using namespace std;
using namespace Navigator::Beacons;
using namespace Navigator::Beacons::Factory;
using namespace Navigator::Math::Trilat;
using namespace Navigator::Math::Kalman;
using namespace Navigator::Mesh;
using Navigator::Math::Position3D;

static void fatal(const string &s) {
    cerr << s << endl;
    exit(1);
}

static vector<Beacon> parseBeacons() {
    vector<Beacon> beacons;

    ifstream in("in/beacons.txt");
    string uuid;
    int major, minor;
    double txpower, damp, x, y, z;
    for (;;) {
        in >> uuid >> major >> minor >> txpower >> damp >> x >> y >> z;
        if (!in)
            break;
        else
            beacons.emplace_back(BeaconUID(uuid, major, minor), txpower, damp, Position3D(x, y, z));
    }

    return beacons;
}

//===========================================================
static bool parseBRD(istream &in, BeaconReceivedData &brd, unsigned long long &ts0, unsigned long long &tsull) {
    string line;
    getline(in, line);
    if (!in) {
        return false;
    }

    stringstream sLine(line);
//    cout << "line = " << line << endl;

    string uuid;
    int major, minor;
    double temp, rssi;

    sLine >> tsull >> uuid >> major >> minor >> temp >> rssi;

    if (!sLine)
        return false;

    BeaconUID uid(uuid, major, minor);

    if (0 == ts0) {
        ts0 = tsull;
    }
    double ts = 1.0 * (tsull - ts0) / 1000;  // Double timestamp

    brd = BeaconReceivedData(ts, uid, rssi);

    return true;
}
//===========================================================

int main() {

    cout << "Mega Flare !!!" << endl;

//    StandardBeaconNavigator navigator(nullptr, false);

    shared_ptr<KalmanBeaconNavigator> nav = make_shared<KalmanBeaconNavigator>();
    KalmanBeaconNavigator & navigator = *nav;

    vector<Beacon> beacons = parseBeacons();

//    for (const auto & b : beacons)
//        cout << b.getUid() << endl;

    navigator.addBeacons(beacons);

   /* vector<shared_ptr<BeaconProcessor>> processors;
    for (const Beacon &b : beacons) {
        processors.push_back(navigator.findProcessorByUid(b.getUid()));
    }

    ofstream beFile("beacons.out");
    for (int i = 0; i < processors.size(); ++i) {
        const Beacon &b = processors[i]->getBeacon();
        beFile << setw(3) << i + 1 << "  " << b.getUid() << "  " << b.getTxPower() << " " << b.getDamp() << " "
               << b.getPos() << endl;
    }
    beFile.close();*/

    // Create wrapper navigator
    KalmanXYBeaconNavigator navigator2(nav);

    ifstream in("in/ble.txt");
    if (!in)
        fatal("Can't open in/ble.txt");
    vector<BeaconReceivedData> brds;
    unsigned long long ts0 = 0;
    unsigned long long tsull = 0;
    double lastTs = nan("");
    FILE *filePos = fopen("pos.out", "w");
    BeaconReceivedData brd;
    bool eof = false;
    for (;;) {
        if (!parseBRD(in, brd, ts0, tsull)) // End Of File
            eof = true;

        //    cout << brd.timestamp << " " << brd.rssi << " " << brd.uid << endl;
        if (isnan(lastTs))
            lastTs = brd.timestamp;

        if (fabs(brd.timestamp - lastTs) < 2.0e-3 && !eof) {
            brds.push_back(brd);
        } else {
            // Process the whole bunch of data in a single process() call
            Position3D outPos = navigator.process(brds);
            // Log the output pos
            fprintf(filePos, "%13.8lf ", brds.at(0).timestamp);
            fprintf(filePos, "%13.8lf %13.8lf", outPos.x, outPos.y);
            fprintf(filePos, "\n");
//            cout << brds[0].timestamp << " " << outPos << endl;

            if (eof)
                break;
            brds.clear();
            brds.push_back(brd);
        }
        lastTs = brd.timestamp;
    }
    fclose(filePos);

    return 0;
}
