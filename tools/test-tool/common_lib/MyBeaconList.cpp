//
// Created by  Oleksiy Grechnyev on 2/6/2017.
//

#include "MyBeaconList.h"
#include "myjson.h"

#include <iostream>
#include <fstream>
#include <cassert>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

namespace tester {

    bool MyBeaconList::readDAT(std::string const &fileName) {
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

    bool MyBeaconList::readJSON(std::string const &fileName) {
        using namespace std;
        using namespace rapidjson;

        ifstream in(fileName);

        if (!in) {
            cerr << "ERROR: Cannot open input file : " << fileName << endl;
            return false;
        }

        cout << "Reading beacons from JSON file : " << fileName << endl << endl;

        // Parse JSON from input file
        // Note: accoding to rapidjson docs it's faster to use C FILE
        // instead of C++ ifstream/ofstream
        // But for small JSON I don't care
        IStreamWrapper isw(in);
        Document d; // DOM document
        d.ParseStream(isw);
        in.close(); // Close stream in ,work with Document d

        // static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };

        // cout << "document type = " << kTypeNames[d.GetType()] << endl;
        if (!d.IsArray()) {
            cerr << "ERROR in " << fileName<< ": JSON document must be Array. " << endl;
            return false;
        }


        beacons.clear(); // Just in case

        // Loop over all beacons in the array C++11 style
        // b = beacon DOM object
        for (auto & b: d.GetArray()){
            MyBeacon beacon; // The beacon object to create

            Vec3 vec3;
            if (!myjson::readVec3(b, "xyz", vec3)) return false;

            // cout << "xyz = " << vec3 << endl;

            beacon.x = vec3.x;
            beacon.y = vec3.y;
            beacon.z = vec3.z;

            if (!myjson::readLL(b, "hash", beacon.hash)) return false;
            if (!myjson::readDouble(b, "TXpower", beacon.txPower)) return false;
            if (!myjson::readDouble(b, "damp", beacon.damp)) return false;

            cout << "beacon = " << beacon << endl;

            beacons.push_back(beacon);
        }

        return true;
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

    bool MyBeaconList::readAuto(std::string const &fileName) {
        using namespace std;

        if (Util::hasExt(fileName, "JSON")) {
            return readJSON(fileName);
        } else {
            return readDAT(fileName);
        }
    }
}