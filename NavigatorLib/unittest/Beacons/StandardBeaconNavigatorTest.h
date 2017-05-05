//
// Created by  Oleksiy Grechnyev on 5/4/2017.
//

#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Navigator.h"

namespace NaviTest {
    namespace Beacons {
        class StandardBeaconNavigatorTest : public CPPUNIT_NS::TestFixture {
        CPPUNIT_TEST_SUITE(StandardBeaconNavigatorTest);
                CPPUNIT_TEST(testInit);
            CPPUNIT_TEST_SUITE_END();
        public:
            /// Test the "INIT" feature, no mesh
            void testInit();
        };

    }
}

