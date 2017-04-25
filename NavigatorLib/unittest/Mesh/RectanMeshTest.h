//
// Created by  Oleksiy Grechnyev on 4/20/2017.
//

#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


#include "Navigator.h"

#include "../mydoubleeq.h"


namespace NaviTest {
    namespace Mesh {
        class RectanMeshTest : public CPPUNIT_NS::TestFixture {
        CPPUNIT_TEST_SUITE(RectanMeshTest);
                CPPUNIT_TEST(test1);
                CPPUNIT_TEST(testMask);
            CPPUNIT_TEST_SUITE_END();
        public: //===== Methods

            /// Test a simple mesh w/o mask
            void test1();

            /// Test the same mesh with a mask table
            void testMask();

        private: //==== Methods
            /// Compare 2 Position3Ds for unit tests
            bool myPosEq(const Navigator::Math::Position3D p1, const Navigator::Math::Position3D p2, double accuracy){
                return myDoubleEq(p1.distance(p2), 0, accuracy);
            }

        };
    }
}


