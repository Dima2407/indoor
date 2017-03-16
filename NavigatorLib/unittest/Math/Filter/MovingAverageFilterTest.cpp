//
// Created by  Oleksiy Grechnyev on 3/13/2017.
//

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

                CPPUNIT_ASSERT(myDoubleEq(filter.process(1.0), 1.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(filter.process(2.0), 1.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(filter.process(3.0), 2.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(filter.process(4.0), 2.5, accuracy));
                // Now the buffer is full
                CPPUNIT_ASSERT(myDoubleEq(filter.process(-1.0), 2.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(filter.process(2.0), 2.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(filter.process(-1.0), 1.0, accuracy));

                // Reset the filter
                filter.reset();

                // And try again with different data
                CPPUNIT_ASSERT(myDoubleEq(filter.process(0.0), 0.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(filter.process(1.0), 0.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(filter.process(1.0), 2.0 / 3, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(filter.process(1.0), 0.75, accuracy));
                // Now the buffer is full
                CPPUNIT_ASSERT(myDoubleEq(filter.process(1.0), 1.0, accuracy));
                // With window size 4 the history is forgotten
                CPPUNIT_ASSERT(myDoubleEq(filter.process(1.0), 1.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(filter.process(1.0), 1.0, accuracy));
                // And go down to 0
                CPPUNIT_ASSERT(myDoubleEq(filter.process(0.0), 0.75, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(filter.process(0.0), 0.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(filter.process(0.0), 0.25, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(filter.process(0.0), 0.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(filter.process(0.0), 0.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(filter.process(0.0), 0.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(filter.process(0.0), 0.0, accuracy));

            }
        }
    }
}