//
// Created by  Oleksiy Grechnyev on 2/7/2017.
//

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include <iostream>
#include <fstream>

#include "TesterConfig.h"
#include "myjson.h"

namespace tester {


    bool TesterConfig::readJSON(std::string fileName, bool verbose) {

        using namespace std;
        using namespace rapidjson;

        ifstream in(fileName);

        if (!in) {
            cerr << "ERROR: Cannot open input file : " << fileName << endl;
            return false;
        }

        if (verbose) cout << "Reading Tester configuration from JSON file : " << fileName << endl << endl;

        // Parse JSON from input file
        // Note: accoding to rapidjson docs it's faster to use C FILE
        // instead of C++ ifstream/ofstream
        // But for small JSON I don't care
        IStreamWrapper isw(in);
        Document d; // DOM document
        d.ParseStream(isw);
        in.close(); // Close stream in ,work with Document d

        // Parse all data using myjson utils
        if (!myjson::readString(d, "inBeaconsFile", inBeaconsFile)) return false;
        if (!myjson::readString(d, "inEventsFile", inEventsFile)) return false;
        if (!myjson::readString(d, "inRouteFile", inRouteFile)) return false;


        if (!myjson::readDouble(d, "ticks", ticks)) return false;
        if (verbose) cout << "ticks = " << ticks << endl;

        if (!myjson::readInt(d, "skipEvents", skipEvents)) return false;
        if (verbose) cout << "skipEvents = " << skipEvents << endl;

        if (!myjson::readBool(d, "txFromBeacons", txFromBeacons)) return false;
        if (verbose) cout << "txFromBeacons = " << (txFromBeacons ? "true" : "false") << endl;

        return true;
    }
}