//
// Created by  Oleksiy Grechnyev on 3/25/2017.
//

#include <vector>
#include <iostream>
#include <cmath>

#include "Navigator.h"

#include "../../mydoubleeq.h"

#include "./AlgorithmTest.h"

namespace NaviTest {
    namespace Beacons {
        namespace Calibrate {

            // Register this suite !
            CPPUNIT_TEST_SUITE_REGISTRATION(AlgorithmTest);

//================================================================================
            void AlgorithmTest::testLeastSquares() {
                using namespace std;
                using namespace Navigator::Beacons::Calibrate::Algorithm;

                // Set the accuracy
                constexpr double accuracy = 1.0e-10;

                double a, b;

                // Test the normal operation
                vector<double> x{1.0, 2.0, 3.0, 4.0, 5.0};
                vector<double> y{1.0, 3.5, 3.0, 4.5, 3.0};

                leastSquares(x, y, a, b);

                CPPUNIT_ASSERT(myDoubleEq(a, 0.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(b, 1.5, accuracy));

                // Test 2 points
                x = {4.0, 7.0};
                y = {5.0, -1.0};

                leastSquares(x, y, a, b);

//                cout << "a = " << a << endl;
//                cout << "b = " << b << endl;

                CPPUNIT_ASSERT(myDoubleEq(a, -2.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(b, 13.0, accuracy));


                // Test bad cases
                x = {4.0, 4.0}; // All x coincide, a = infinity
                y = {5.0, -1.0};

                leastSquares(x, y, a, b);
                CPPUNIT_ASSERT(isnan(a) && isnan(b));

                x.clear(); // Zero points
                y.clear();

                leastSquares(x, y, a, b);
                CPPUNIT_ASSERT(isnan(a) && isnan(b));

                x = {1.0}; // One point
                y = {2.0};

                leastSquares(x, y, a, b);
                CPPUNIT_ASSERT(isnan(a) && isnan(b));


                x = {4.0, 5.0, 3.4}; // Different vector sizes
                y = {5.0, -1.0};

                leastSquares(x, y, a, b);
                CPPUNIT_ASSERT(isnan(a) && isnan(b));
            }
//================================================================================

            void AlgorithmTest::testCalibrateLeastSquares() {
                using namespace std;
                using namespace Navigator::Beacons::Calibrate::Algorithm;
                using namespace Navigator::Math::Trilat;

                double txPower, damp; // Result of calibration

                // The good case

                // The ideal TXPower, damp
                constexpr double txPower0 = -50.0, damp0 = 2.5;

                // A few distanced, does not matter
                const double distances[] = {0.5, 1.1, 2.7, 3.9, 4.68};

                // Create calibration table of pairs (dist, rssi) with fake RSSIs
                CalibrationTable table;
                for (double d : distances) {
                    table.push_back(make_pair(d, fakeRSSI(d, txPower0, damp0)));
                }

                // Run the calibration
                calibrateLeastSquares(table, txPower, damp);
//
//                cout << "txPower = " << txPower << endl;
//                cout << "damp = " << damp << endl;

                // Set the accuracy
                constexpr double accuracy = 1.0e-10;

                CPPUNIT_ASSERT(myDoubleEq(txPower, txPower0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(damp, damp0, accuracy));

                // Now the same for only 2 points, should work
                table = {make_pair(1.2, fakeRSSI(1.2, txPower0, damp0)),
                         make_pair(3.1, fakeRSSI(3.1, txPower0, damp0))
                };

                calibrateLeastSquares(table, txPower, damp);
                CPPUNIT_ASSERT(myDoubleEq(txPower, txPower0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(damp, damp0, accuracy));

                // The bad cases

                // Only one point (nan from LSQ)
                table = {make_pair(1.2, fakeRSSI(1.2, txPower0, damp0))};
                calibrateLeastSquares(table, txPower, damp);
                CPPUNIT_ASSERT(isnan(txPower) && isnan(damp));

                // Zero distance (nan from log10)
                table = {make_pair(0.0, fakeRSSI(1.2, txPower0, damp0)),
                         make_pair(3.1, fakeRSSI(3.1, txPower0, damp0))
                };
                calibrateLeastSquares(table, txPower, damp);
                CPPUNIT_ASSERT(isnan(txPower) && isnan(damp));

                // Negative distance (nan from log10)
                table = {make_pair(-1.2, fakeRSSI(1.2, txPower0, damp0)),
                         make_pair(3.1, fakeRSSI(3.1, txPower0, damp0))
                };
                calibrateLeastSquares(table, txPower, damp);
                CPPUNIT_ASSERT(isnan(txPower) && isnan(damp));

                // Distances coincide (nan from LSQ)
                table = {make_pair(3.1, fakeRSSI(1.2, txPower0, damp0)),
                         make_pair(3.1, fakeRSSI(3.1, txPower0, damp0))
                };
                calibrateLeastSquares(table, txPower, damp);
                CPPUNIT_ASSERT(isnan(txPower) && isnan(damp));
            }
//================================================================================

            void AlgorithmTest::testCalibrateOnePointD() {
                using namespace std;
                using namespace Navigator::Beacons::Calibrate::Algorithm;
                using namespace Navigator::Beacons::Calibrate;
                using namespace Navigator::Math::Trilat;

                // The ideal TXPower, damp; -70 is the default txPower from config
                constexpr double txPower0 = -70.0, damp0 = 2.6;

                double dist = 1.5;
                double rssi = fakeRSSI(dist, txPower0, damp0);

                double txPower, damp; // Result

                calibrateOnePointD(dist, rssi, CalibrationConfig(), txPower, damp);

//                cout << "txPower = " << txPower << endl;
//                cout << "damp = " << damp << endl;
                // Set the accuracy
                constexpr double accuracy = 1.0e-10;

                CPPUNIT_ASSERT(myDoubleEq(txPower, txPower0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(damp, damp0, accuracy));

                // The bad cases
                // dist == 1
                calibrateOnePointD(1.0, rssi, CalibrationConfig(), txPower, damp);
                CPPUNIT_ASSERT(isnan(txPower) && isnan(damp));

                // dist < 0
                calibrateOnePointD(-1.0, rssi, CalibrationConfig(), txPower, damp);
                CPPUNIT_ASSERT(isnan(txPower) && isnan(damp));


            }

//================================================================================

        }
    }
}