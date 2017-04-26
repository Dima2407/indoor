//
// Created by  Oleksiy Grechnyev on 4/26/2017.
//

#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


namespace NaviTest {
    namespace Mesh {
        class MeshDataTest  : public CPPUNIT_NS::TestFixture {
        CPPUNIT_TEST_SUITE(MeshDataTest);
                CPPUNIT_TEST(test1);
            CPPUNIT_TEST_SUITE_END();
        public:
            /// Test a simple mesh
            void test1();
        };
    }
}

