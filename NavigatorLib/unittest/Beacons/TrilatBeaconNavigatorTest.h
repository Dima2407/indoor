//
// Created by  Oleksiy Grechnyev on 3/20/2017.
//

#pragma once


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Navigator.h"


namespace NaviTest {
    namespace Beacons {

        /// Unit tests for TrilatBeaconNavigator
        class TrilatBeaconNavigatorTest : public CPPUNIT_NS::TestFixture {

        CPPUNIT_TEST_SUITE(TrilatBeaconNavigatorTest);
                CPPUNIT_TEST(testSimple);
            CPPUNIT_TEST_SUITE_END();

        public: //=== Methods ===

            void testSimple();

            void setUp() override;

            void tearDown() override;

        private: //=== Methods ===
            double fakeRSSI(const Navigator::Math::Position3D &p1, const Navigator::Math::Position3D &p2, double txPower, double damp);

        private: //=== Fields ===

            /// Yes, I know all about shared_ptr, here I use poiners on purpose as a test
            /// Uses No+No setup
            Navigator::Beacons::TrilatBeaconNavigator * navigator1;

        };

    }
}

