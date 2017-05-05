//
// Created by  Oleksiy Grechnyev on 5/5/2017.
//

#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


namespace NaviTest {
    namespace Beacons {
        class GraphTest  : public CPPUNIT_NS::TestFixture {

        CPPUNIT_TEST_SUITE(GraphTest);
                CPPUNIT_TEST(testDijkstra);
            CPPUNIT_TEST_SUITE_END();

        public: //== Methods

            /// String UIDs
            void testDijkstra();
        };
    }
}



