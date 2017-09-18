//
// Created by  Victor Draban on 6/9/2017.
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <regex>

#include "Navigator/Math/KalmanXY/KalmanXYConfig.h"
#include "Navigator/Math/KalmanXY/KalmanXYFilter.h"

using namespace std;
using namespace Navigator;
using namespace Math;

// Test KalmanXYFilter
int main() {

    vector<Position2D> vecXY;
    vector<vector<Position2D>> vecPosition3Beacon;
    vector<Position2D> vecResult;

    string line;
    cout << fixed << setprecision(6);
    regex regExp("(\\d+\.\\d+)(\\s*)(\\d+\.\\d+)");
    cmatch resRegExp;

// ------------- read coordsINPUT.txt
    ifstream fin("C:/QtProjects/testLogFiles/coordsINPUT.txt");
    getline(fin, line);

    while (getline(fin, line)) {
        regex_search(line.c_str(), resRegExp, regExp);
        vecXY.push_back(Math::Position2D(stod(resRegExp[1]), stod(resRegExp[3])));
    }
    fin.close();
// ------------- end read coordsINPUT.txt

// ------------- check vecXY ----------
//    cout << " vecXY containce : " << endl;
//    for (Math::Position2D &iter : vecXY) {
//        cout << iter.x << " " << iter.y << endl;
//    }
// ------------- end check vecXY ----------


// ------------- read beaconsINPUT.txt
    ifstream finBeacons("C:/QtProjects/testLogFiles/beaconsINPUT.txt");
    getline(finBeacons, line);

    while (getline(finBeacons, line)) {
        vector<Math::Position2D> tempVec;
        tempVec.reserve(3);
        sregex_iterator next(line.begin(), line.end(), regExp);
        sregex_iterator end;
        while(next != end) {
            smatch match = *next;
            tempVec.push_back(Math::Position2D(stod(match[1].str()), stod(match[3].str())));
            next++;
        }
        vecPosition3Beacon.push_back(tempVec);
    }
    finBeacons.close();
// ------------- end read beaconsINPUT ----------

// ------------- check vecPosition3Beacon ----------
//        cout << " vecPosition3Beacon containce : " << endl;
//        for (vector<Math::Position2D> &iter : vecPosition3Beacon) {
//            for (Math::Position2D innerIter : iter) {
//                cout << innerIter.x << " " << innerIter.y << "\t";
//            }
//            cout << endl;
//        }
// ------------- end check vecPosition3Beacon ----------

// ------------- read coordsOUTPUT.txt
    ifstream finOut("C:/QtProjects/testLogFiles/coordsOUTPUT.txt");
    getline(finOut, line);

    while (getline(finOut, line)) {
        regex_search(line.c_str(), resRegExp, regExp);
        vecResult.push_back(Math::Position2D(stod(resRegExp[1]), stod(resRegExp[3])));
    }
    finOut.close();
// ------------- end read coordsINPUT.txt

// ------------- check vecResult ----------
//    cout << " vecResult containce : " << endl;
//    for (Math::Position2D &iter : vecResult) {
//        cout << iter.x << " " << iter.y << endl;
//    }
// ------------- end vecResult vecXY ----------


// ------------- start testing KalmanXYFilter -----------
    KalmanXY::KalmanXYFilter filter;

    for (int i = 0; i < vecXY.size(); ++i) {
        Math::Position2D result = filter.process(vecXY[i], vecPosition3Beacon[i]);
        cout << "result: X = " << result.x << ", Y = " << result.y <<
                " :: expected: X = " << vecResult[i].x << ", Y = " << vecResult[i].y << endl;
    }
// ------------- end testing KalmanXYFilter -----------
    return 0;
}
