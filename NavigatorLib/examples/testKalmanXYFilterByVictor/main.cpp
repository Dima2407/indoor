//
// Created by  Victor Draban on 6/9/2017.
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "Navigator/Math/KalmanXY/KalmanXYConfig.h"
#include "Navigator/Math/KalmanXY/KalmanXYFilter.h"

using namespace std;
using namespace Navigator;
using namespace Math;

// Test KalmanXYFilter
int main() {

    vector<Position2D> vecXY;
    vector<Position2D> vecPosition3Beacon;
    vector<Position2D> vecResult;

    double buff;
    cout << fixed << setprecision(6);

    ifstream fin("C:/QtProjects/testLogFiles/coordsINPUT.txt");
    while (fin >> buff) {
        vecTimestamp.push_back(buff);
        fin >> buff;
        vecVal.push_back(buff);
        fin >> buff;
        vecValResult.push_back(buff);
    }
    fin.close();

    KalmanXY::KalmanXYFilter filter;
//    Position2D loc(1, 1);
//    Position2D loc2(3.1, 1.9);
//    Position2D loc3(17.48, 7.4);
//    Position2D loc4(0.0, 0.0);
//    Position2D loc5(-10.2, 1);
//    Position2D loc6(-10.2, -71.7);

//    vector<Position2D> vec{{7,7},{14,1},{9,7}};

//    Position2D answer = filter.process(loc, vec);
//    cout << answer.x << " " << answer.y << endl;

//    Position2D answer2 = filter.process(loc2, vec);
//    cout << answer2.x << " " << answer2.y << endl;


//    Position2D answer3 = filter.process(loc3, vec);
//    cout << answer3.x << " " << answer3.y << endl;

//    Position2D answer4 = filter.process(loc4, vec);
//    cout << answer4.x << " " << answer4.y << endl;
    return 0;
}
