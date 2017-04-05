//
// Created by  Oleksiy Grechnyev on 4/4/2017.
//

#include "../../mydoubleeq.h"


#include "AlphaTrimmedFilterTest.h"

namespace NaviTest {
    namespace Math {
        namespace Filter {
            // Register this suite !
            CPPUNIT_TEST_SUITE_REGISTRATION(AlphaTrimmedFilterTest);

            void AlphaTrimmedFilterTest::test1() {
                using namespace Navigator::Math::Filter;

                // AT filter with winsize=1 should be a no-filter regardless of alpha

                constexpr double accuracy = 1.0e-10;

                AlphaTrimmedFilter filter0(1, 0.0);
                AlphaTrimmedFilter filter2(1, 0.2);
                AlphaTrimmedFilter filter5(1, 0.5);

                CPPUNIT_ASSERT(myDoubleEq(runAT(filter0, 19.0), 19.0, accuracy) );
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter0, -2.0), -2.0, accuracy) );
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter0, 7.0), 7.0, accuracy) );
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter0, 4.0), 4.0, accuracy) );

                CPPUNIT_ASSERT(myDoubleEq(runAT(filter2, -4.0), -4.0, accuracy) );
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter2, -666.0), -666.0, accuracy) );
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter2, 13.5), 13.5, accuracy) );
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter2, 3.14159), 3.14159, accuracy) );

                CPPUNIT_ASSERT(myDoubleEq(runAT(filter5, 0.1), 0.1, accuracy) );
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter5, 0.2), 0.2, accuracy) );
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter5, -0.3), -0.3, accuracy) );
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter5, 0.7), 0.7, accuracy) );
            }
//--------------------------------------------------------------

            void AlphaTrimmedFilterTest::test4() {
                using namespace Navigator::Math::Filter;

                constexpr double accuracy = 1.0e-10;

                // AT filters with winsize=4

                //////////////////
                // These two should act as MovingAverageFilter(4)
                AlphaTrimmedFilter filter00(4, 0.00);
                AlphaTrimmedFilter filter24(4, 0.24);

                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, 1.0), 1.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, 2.0), 1.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, 3.0), 2.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, 4.0), 2.5, accuracy));
                // Now the buffer is full
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, -1.0), 2.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, 2.0), 2.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, -1.0), 1.0, accuracy));

                // Reset the filter00
                filter00.reset();

                // And try again with different data
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, 0.0), 0.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, 1.0), 0.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, 1.0), 2.0 / 3, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, 1.0), 0.75, accuracy));
                // Now the buffer is full
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, 1.0), 1.0, accuracy));
                // With window size 4 the history is forgotten
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, 1.0), 1.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, 1.0), 1.0, accuracy));
                // And go down to 0
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, 0.0), 0.75, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, 0.0), 0.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, 0.0), 0.25, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, 0.0), 0.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, 0.0), 0.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, 0.0), 0.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter00, 0.0), 0.0, accuracy));
                //--
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter24, 1.0), 1.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter24, 2.0), 1.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter24, 3.0), 2.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter24, 4.0), 2.5, accuracy));
                // Now the buffer is full
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter24, -1.0), 2.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter24, 2.0), 2.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter24, -1.0), 1.0, accuracy));
                //////////////////

                // Now two filters which discard 2 value out of 4
                AlphaTrimmedFilter filter26(4, 0.26);
                AlphaTrimmedFilter filter50(4, 0.50);

                CPPUNIT_ASSERT(myDoubleEq(runAT(filter26, -1.0), -1.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter26, 2.0), 0.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter26, 3.0), 4.0/3, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter26, 6.0), 2.5, accuracy));
                // Now the buffer is full
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter26, -1.0), 2.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter26, 2.0), 2.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter26, -1.0), 0.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter26, 0.0), -0.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter26, 3.0), 1.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter26, 3.0), 1.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter26, 3.0), 3.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter26, 3.0), 3.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter26, 0.0), 3.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter26, 0.0), 1.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter26, 0.0), 0.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter26, 0.0), 0.0, accuracy));
                
                // Filter50 is only different in line 3 with 3 values


                CPPUNIT_ASSERT(myDoubleEq(runAT(filter50, -1.0), -1.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter50, 2.0), 0.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter50, 3.0), 2.0, accuracy));  // DIFFERENT !
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter50, 6.0), 2.5, accuracy));
                // Now the buffer is full
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter50, -1.0), 2.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter50, 2.0), 2.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter50, -1.0), 0.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter50, 0.0), -0.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter50, 3.0), 1.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter50, 3.0), 1.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter50, 3.0), 3.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter50, 3.0), 3.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter50, 0.0), 3.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter50, 0.0), 1.5, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter50, 0.0), 0.0, accuracy));
                CPPUNIT_ASSERT(myDoubleEq(runAT(filter50, 0.0), 0.0, accuracy));
            }

//--------------------------------------------------------------


        }
    }
}