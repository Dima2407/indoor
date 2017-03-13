//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>

#include "Math/Trilat/trilat.h"

using namespace std;
using namespace Navi;
using namespace Navi::Math;

int main()
{
    // Let's have some fun with trilateration

    // A distance between 2 points
    auto dist2Point = [](const Position3D &p1, const Position3D &p2) -> double {
        return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    };

    // Create vector of 4 points
    vector<Position3D> points;

    points.emplace_back(0.3, 0.5, 0.0);
    points.emplace_back(9.7, 0.4, 0.0);
    points.emplace_back(-0.2, 10.6, 0.0);

    // Reference point
    Position3D refPoint(5.6, 2.7, 0.0);

    // Vector of distances
    vector<double> distances;

    for (const Position3D & p : points)
        distances.push_back(dist2Point(p, refPoint));

    // Result point
    Position3D resultPoint;

    Trilat::trilatLocation2d(points, distances, resultPoint);

    cout << resultPoint.x << "  " << resultPoint.y << endl;

    return 0;
}