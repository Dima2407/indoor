//
// Created by  Oleksiy Grechnyev on 3/13/2017.
//

#pragma once


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Navigator/Math/Filter/RingBuffer.h"

namespace NaviTest {
    namespace Math {
        namespace Filter {
            /// RingBufffer tests
            class RingBufferTest : public CPPUNIT_NS::TestFixture {
            CPPUNIT_TEST_SUITE(RingBufferTest);
                    CPPUNIT_TEST(test1);
                CPPUNIT_TEST_SUITE_END();
            public:
                void test1();
            };
        }

    }
}