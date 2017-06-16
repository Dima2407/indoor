//
// Created by  Victor Draban on 6/15/2017.
//

#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace NaviTest {
    namespace Accel {
        class FilterImplTest: public CPPUNIT_NS::TestFixture {
            CPPUNIT_TEST_SUITE(FilterImplTest);
                CPPUNIT_TEST(testClass);
            CPPUNIT_TEST_SUITE_END();
            public:
                void testClass();

            private:
                bool workClass();
                bool doesNotWorkClass();
                bool testValues();
        };
    }
}
