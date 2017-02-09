//
// Created by  Oleksiy Grechnyev on 2/7/2017.
//

#include "BeaconTimeList.h"
#include "myjson.h"
#include "Util.h"

#include <iostream>
#include <fstream>

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

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
        using namespace std;
        using namespace tester;

        if (Util::hasExt(fileName, "JSON")) {
            return readJSON(fileName);
        } else {
            return readDAT(fileName);
        }
    }

    bool BeaconTimeList::readJSON(std::string const &fileName) {

        using namespace std;
        using namespace tester;
        using namespace rapidjson;

        ifstream in(fileName);

        if (!in) {
            cerr << "ERROR: Cannot open input file : " << fileName << endl;
            return false;
        }

        cout << endl << "Reading beacon time data from JSON file : " << fileName << endl << endl;

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
            cerr << "ERROR in " << fileName << ": JSON document must be Array. " << endl;
            return false;
        }


        beaconTimes.clear(); // Just in case

        // Loop over all beacons in the array C++11 style
        // b = beacon time DOM object
        for (auto &b: d.GetArray()) {
            BeaconTime bTime; // The  new object to create

            // Read "hash" OR "MACaddress"
            if (!myjson::readLL(b, "hash", bTime.hash, false)) {

                // If no "hash", try "MACaddress"
                string mac;
                if (!myjson::readString(b, "MACaddress", mac)) return false;

                if (!Util::parseMAC(mac, bTime.hash)) return false;
            }

            if (!myjson::readDouble(b, "t1", bTime.t1)) return false;
            if (!myjson::readDouble(b, "t2", bTime.t2)) return false;
            if (!myjson::readDouble(b, "period", bTime.period)) return false;

            cout << "beaconTime = " << bTime << endl;

            beaconTimes.push_back(bTime);
        }

        return true;
    }
}