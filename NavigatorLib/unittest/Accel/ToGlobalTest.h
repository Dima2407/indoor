//
// Created by  Victor Draban on 6/12/2017.
//

#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace NaviTest {
    namespace Accel {
        class ToGlobalTest : public CPPUNIT_NS::TestFixture {
            CPPUNIT_TEST_SUITE(ToGlobalTest);
                CPPUNIT_TEST(testQuaternion);
            CPPUNIT_TEST_SUITE_END();
        public:
            void testQuaternion();
        private:
            double random();
        };
    }
}
