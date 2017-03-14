//
// Created by  Oleksiy Grechnyev on 3/14/2017.
//

#include <vector>

#include "Math/Trilat/trilat.h"
#include "Math/Position3D.h"

#include "../../mydoubleeq.h"

#include "TrilatTest.h"


namespace NaviTest {
    namespace Math {
        namespace Trilat {


            // Register this suite !
            CPPUNIT_TEST_SUITE_REGISTRATION(TrilatTest);

            void TrilatTest::testTrilat() {
                using namespace std;
                using namespace Navi;
                using namespace Navi::Math;

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

                Navi::Math::Trilat::trilatLocation2d(points, distances, resultPoint);

                // Check if results are reasionable
                constexpr double accuracy = 1.0e-5;

                CPPUNIT_ASSERT(myDoubleEq(refPoint.x, resultPoint.x, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(refPoint.y, resultPoint.y, accuracy));

            }
        }
    }
}