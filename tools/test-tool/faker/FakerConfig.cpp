//
// Created by  Oleksiy Grechnyev on 2/7/2017.
//

#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

#include <iostream>
#include <fstream>

#include "FakerConfig.h"
#include "myjson.h"

namespace faker {


    bool FakerConfig::readJSON(std::string fileName) {
        using namespace std;
        using namespace tester;
        using namespace rapidjson;

        ifstream in(fileName);

        if (!in) {
            cerr << "ERROR: Cannot open input file : " << fileName << endl;
            return false;
        }

        cout << "Reading Faker configuration from JSON file : " << fileName << endl << endl;

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
        if (!myjson::readString(d, "inTimesFile", inTimesFile)) return false;
        if (!myjson::readString(d, "outEventsFile", outEventsFile)) return false;

        if (!myjson::readDouble(d, "t1", trajectory.t1)) return false;
        cout << "t1 = " << trajectory.t1 << endl;
        if (!myjson::readVec3(d, "point1", trajectory.point1)) return false;
        cout << "point1 = " << trajectory.point1 << endl;

        if (!myjson::readDouble(d, "t2", trajectory.t2)) return false;
        cout << "t2 = " << trajectory.t1 << endl;
        if (!myjson::readVec3(d, "point2", trajectory.point2)) return false;
        cout << "point2 = " << trajectory.point2 << endl;


        if (!myjson::readDouble(d, "ticks", ticks)) return false;
        cout << "ticks = " << ticks << endl;


        return true;
    }
}