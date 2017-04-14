//
// Created by  Oleksiy Grechnyev on 3/13/2017.
//


#include <random>
#include <chrono>
#include <ctime>

#include "../../mydoubleeq.h"

#include "./MovingAverageFilterTest.h"


namespace NaviTest {
    namespace Math {
        namespace Filter {
            // Register this suite !
            CPPUNIT_TEST_SUITE_REGISTRATION(MovingAverageFilterTest);


            void MovingAverageFilterTest::testAvg() {
                using namespace Navigator::Math::Filter;

                MovingAverageFilter filter(4); // The filter to test, window size = 4

                constexpr double accuracy = 1.0e-10;

                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 1.0), 1.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 2.0), 1.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 3.0), 2.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 4.0), 2.5, accuracy));
                // Now the buffer is full
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, -1.0), 2.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 2.0), 2.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, -1.0), 1.0, accuracy));

                // Reset the filter
                filter.reset();

                // And try again with different data
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 0.0), 0.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 1.0), 0.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 1.0), 2.0 / 3, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 1.0), 0.75, accuracy));
                // Now the buffer is full
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 1.0), 1.0, accuracy));
                // With window size 4 the history is forgotten
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 1.0), 1.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 1.0), 1.0, accuracy));
                // And go down to 0
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 0.0), 0.75, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 0.0), 0.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 0.0), 0.25, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 0.0), 0.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 0.0), 0.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 0.0), 0.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 0.0), 0.0, accuracy));

            }
//--------------------------------------------------------------
            void MovingAverageFilterTest::test1() {

                using namespace Navigator::Math::Filter;

                MovingAverageFilter filter(1); // The filter to test, window size = 1

                constexpr double accuracy = 1.0e-10;

                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 15.9), 15.9, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, -15.9), -15.9, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 3.14), 3.14, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 83.14), 83.14, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 93.14), 93.14, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, -73.14), -73.14, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 4.56), 4.56, accuracy));

                filter.reset();

                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 15.8), 15.8, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 3.5), 3.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 100500.9), 100500.9, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, -3.5), -3.5, accuracy));

                filter.reset();

                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 3.14), 3.14, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 83.14), 83.14, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 93.14), 93.14, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, -73.14), -73.14, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runMA(filter, 4.56), 4.56, accuracy));
            }

            void MovingAverageFilterTest::testMax1() {

                using namespace std;

                using namespace Navigator::Math::Filter;

                MovingAverageFilter filter(1); // The filter to test, window size = 1

                constexpr double accuracy = 1.0e-10;

                // Seed with time the old-fashioned way (MinGW friendly)
                mt19937 randomEngine(time(nullptr));

                uniform_real_distribution<double> uRand(-100.0, -50.0);

                for (int i = 0; i < 10000; ++i) {
                    double rssi = uRand(randomEngine);

                    // Reset with a probability of about 1/50
                    double tmp  = uRand(randomEngine);
                    if (-50.0 > tmp && tmp > -51.0) {
//                        cout << "RESET !!! \n";
                        filter.reset();
                    }

                    double result = runMA(filter, rssi);
                    CPPUNIT_ASSERT(myDoubleEq(rssi, result, accuracy));

                }
            }
//--------------------------------------------------------------


        }
    }
}