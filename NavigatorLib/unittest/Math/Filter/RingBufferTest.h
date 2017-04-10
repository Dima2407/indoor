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
                    CPPUNIT_TEST(testsize1);
                    CPPUNIT_TEST(testPeek);
                    CPPUNIT_TEST(testValue);
                CPPUNIT_TEST_SUITE_END();
            public:
                /// Test push, pop, size
                void test1();

                /// Test size 1 buffer
                void testsize1();

                /// Test peek
                void testPeek();

                // Test with the IFilter::Value
                void testValue();
            };
        }

    }
}
