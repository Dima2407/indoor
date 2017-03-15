//
// Created by  Oleksiy Grechnyev on 3/14/2017.
//

#include <vector>

#include "Navigator/Math/Trilat/trilat.h"
#include "Navigator/Math/Position3D.h"

#include "../../mydoubleeq.h"

#include "TrilatTest.h"


namespace NaviTest {
    namespace Math {
        namespace Trilat {


            // Register this suite !
            CPPUNIT_TEST_SUITE_REGISTRATION(TrilatTest);

            void TrilatTest::testTrilat()
            {
                using namespace std;
                using namespace Navigator;
                using Navigator::Math;

                // Create vector of 4 points
                vector<Position3D> points;// = { {0.3, 0.5, 0.0} };
                points.emplace_back(0.3, 0.5, 0.0);
                points.emplace_back(9.7, 0.4, 0.0);
                points.emplace_back(-0.2, 10.6, 0.0);

                // Reference point
                Position3D refPoint(5.6, 2.7, 0.0);

                // Vector of distances
                vector<double> distances;
                for (const Position3D & p : points)
                    distances.push_back(p.distance(refPoint));
				
                // Result point
                //Position3D resultPoint;
                //Navigator::Math::Trilat::trilatLocation2d(points, distances, resultPoint);
	            Position3D resultPoint = Navigator::Math::Trilat::trilatLocation2d(points, distances);
	            
                // Check if results are reasionable
                constexpr double accuracy = 1.0e-5;

                CPPUNIT_ASSERT(myDoubleEq(refPoint.x, resultPoint.x, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(refPoint.y, resultPoint.y, accuracy));

            }
        }
    }
}