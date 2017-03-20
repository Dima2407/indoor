//
// Created by  Oleksiy Grechnyev on 3/20/2017.
//

#pragma once


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace NaviTest {
    namespace Beacons {

        /// Unit tests for BeaconProcessor
        class BeaconProcessorTest : public CPPUNIT_NS::TestFixture {
        CPPUNIT_TEST_SUITE(BeaconProcessorTest);
                CPPUNIT_TEST(testNoNo);
            CPPUNIT_TEST_SUITE_END();

        public: //==== Methods ===

            /// Test BeaconProcessor with NoFilter + NoFilter
            void testNoNo();


        };

    }
}

