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
                CPPUNIT_TEST(testTrilat2D_1);
                CPPUNIT_TEST(testTrilat3D_1);
                CPPUNIT_TEST_SUITE_END();
            public:
                /// A single-point 2D test
                void testTrilat2D_1();

                /// A single-point 3D test
                void testTrilat3D_1();
            };
        }
    }
}
