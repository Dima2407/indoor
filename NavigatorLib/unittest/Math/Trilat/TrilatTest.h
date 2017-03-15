//
// Created by  Oleksiy Grechnyev on 3/14/2017.
//

#pragma once


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


namespace NaviTest {
    namespace Math {
        namespace Trilat {

            class TrilatTest : public CPPUNIT_NS::TestFixture
            {
                CPPUNIT_TEST_SUITE(TrilatTest);
                CPPUNIT_TEST(testTrilat);
                CPPUNIT_TEST_SUITE_END();
            public:
                void testTrilat();
            };
        }
    }
}
