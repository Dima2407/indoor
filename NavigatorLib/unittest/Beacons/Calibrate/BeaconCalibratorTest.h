//
// Created by  Oleksiy Grechnyev on 3/26/2017.
//

#pragma once


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace NaviTest {
    namespace Beacons {
        namespace Calibrate {

            /// Test BeaconCalibrator
            class BeaconCalibratorTest : public CPPUNIT_NS::TestFixture {
            CPPUNIT_TEST_SUITE(BeaconCalibratorTest);
                    CPPUNIT_TEST(testCalibrate);
                    CPPUNIT_TEST(testCalibrate1p);
                CPPUNIT_TEST_SUITE_END();
            public:
                /// Test normal claibration
                void testCalibrate();

                /// Test 1-point calibration
                void testCalibrate1p();

            };
        }
    }
}


