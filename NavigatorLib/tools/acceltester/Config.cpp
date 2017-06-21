//
// Created by Igor Maschikevich on 6/20/2017.
//

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include <iostream>
#include <fstream>

#include "Config.h"
#include "Myjson.h"

namespace ecceltester {


bool Config::readJSON(std::string fileName, bool verbose) {

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
    if (!Myjson::readString(d, "angles", angles)) return false;
    if (!Myjson::readString(d, "accelerometer", accelerometer)) return false;


    return true;
}
}
