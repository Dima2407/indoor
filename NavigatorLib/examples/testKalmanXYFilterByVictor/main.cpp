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

    KalmanXY::KalmanXYFilter filter;
    Position2D loc(1, 1);
    Position2D loc2(3.1, 1.9);
    Position2D loc3(17.48, 7.4);
    Position2D loc4(0.0, 0.0);
    Position2D loc5(-10.2, 1);
    Position2D loc6(-10.2, -71.7);

    vector<Position2D> vec;
    Position2D dist1(7, 7);
    Position2D dist2(14, 1);
    Position2D dist3(9, 7);
    vec.push_back(dist1);
    vec.push_back(dist2);
    vec.push_back(dist3);

    Position2D answer = filter.process(loc, vec);
    cout << answer.x << " " << answer.y << endl;

    vector<Position2D> vec2;
    Position2D dist4(7, 7);
    Position2D dist5(14.9, 4.65);
    Position2D dist6(9, 7);
    vec2.push_back(dist4);
    vec2.push_back(dist5);
    vec2.push_back(dist6);

    Position2D answer2 = filter.process(loc2, vec2);
    cout << answer2.x << " " << answer2.y << endl;

    vector<Position2D> vec3;
    Position2D dist7(1.8, 7);
    Position2D dist8(12, 11.8);
    Position2D dist9(7.5, 4.4);
    vec3.push_back(dist7);
    vec3.push_back(dist8);
    vec3.push_back(dist9);

    Position2D answer3 = filter.process(loc3, vec3);
    cout << answer3.x << " " << answer3.y << endl;

    vector<Position2D> vec4;
    Position2D dist10(1.8, 7);
    Position2D dist11(12, 11.8);
    Position2D dist12(7.5, 4.4);
    vec4.push_back(dist10);
    vec4.push_back(dist11);
    vec4.push_back(dist12);

    Position2D answer4 = filter.process(loc4, vec4);
    cout << answer4.x << " " << answer4.y << endl;
    return 0;
}
