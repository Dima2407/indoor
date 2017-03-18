//
// Created by  Oleksiy Grechnyev on 3/18/2017.
//

#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace NaviTest {
    namespace Beacons {
        class BeaconUIDTest : public CPPUNIT_NS::TestFixture {
        CPPUNIT_TEST_SUITE(BeaconUIDTest);
                CPPUNIT_TEST(testStringUID);
                CPPUNIT_TEST(testSmmUid);
                CPPUNIT_TEST(testLlUid);
            CPPUNIT_TEST_SUITE_END();

        public: //== Methods

            /// String UIDs
            void testStringUID();

            /// String Major Minor UID
            void testSmmUid();

            /// 8-byte long long
            void testLlUid();
        };
    }
}


