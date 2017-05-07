//
// Created by  Oleksiy Grechnyev on 5/7/2017.
//

#pragma once


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace NaviTest {
    namespace Dijkstra {
        class PointGraphTest  : public CPPUNIT_NS::TestFixture {

        CPPUNIT_TEST_SUITE(PointGraphTest);
                CPPUNIT_TEST(test1);
            CPPUNIT_TEST_SUITE_END();
        public:
            void test1();

        };

    }
}

