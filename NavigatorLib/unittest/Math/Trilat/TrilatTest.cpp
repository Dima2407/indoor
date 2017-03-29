//
// Created by  Oleksiy Grechnyev on 3/14/2017.
//

#include <vector>
#include <iostream>

#include "Navigator.h"

#include "../../mydoubleeq.h"

#include "TrilatTest.h"


namespace NaviTest {
    namespace Math {
        namespace Trilat {


            // Register this suite !
            CPPUNIT_TEST_SUITE_REGISTRATION(TrilatTest);

            void TrilatTest::testTrilat2D_1()
            {
                using namespace std;
                using namespace Navigator;
                using namespace Navigator::Math;
                using namespace Navigator::Math::Trilat;

                // 3 points
                const Position3D points[] = {
                        Position3D(0.3, 0.5, 0.0),
                        Position3D(9.7, 0.4, 0.0),
                        Position3D(-0.2, 10.6, 0.0)
                };

                // Reference point
                Position3D refPoint(5.6, 2.7, 0.0);

                // Vector of trilat records
                vector<TrilatRecord> records;

                for (const Position3D & p : points) {
                    records.push_back(TrilatRecord(p, p.distance(refPoint)));
                }

                // Result point
                //Position3D resultPoint;
                //Navigator::Math::Trilat::trilatLocation2d(points, distances, resultPoint);
	            Position3D resultPoint = trilatLocation2d(records);
	            
                // Check if results are reasionable
                constexpr double accuracy = 1.0e-5;

                CPPUNIT_ASSERT(myDoubleEq(refPoint.x, resultPoint.x, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(refPoint.y, resultPoint.y, accuracy));

            }

            void TrilatTest::testTrilat3D_1() {
                using namespace std;
                using namespace Navigator;
                using namespace Navigator::Math;
                using namespace Navigator::Math::Trilat;

                //  4 points
                const Position3D points[] = {
                        Position3D(0.3, 0.5, 0.0),
                        Position3D(9.7, 0.4, 0.0),
                        Position3D(-0.2, 10.6, 0.0),
                        Position3D(0.1, 0.2, 8.4)
                };

                // Reference point
                Position3D refPoint(2.3, 4.1, 3.9);

                // Vector of trilat records
                vector<TrilatRecord> records;

                for (const Position3D & p : points) {
                    records.push_back(TrilatRecord(p, p.distance(refPoint)));
                }

                // Result point
//                Position3D resultPoint;
//                Navigator::Math::Trilat::trilatLocation3d(points, distances, resultPoint);
                Position3D resultPoint = trilatLocation3d(records);

//                cout << resultPoint.x << "  " << resultPoint.y << "  " << resultPoint.z << endl;

                // Check if results are reasionable
                constexpr double accuracy = 1.0e-5;

                CPPUNIT_ASSERT(myDoubleEq(refPoint.x, resultPoint.x, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(refPoint.y, resultPoint.y, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(refPoint.z, resultPoint.z, accuracy));
            }
        }
    }
}