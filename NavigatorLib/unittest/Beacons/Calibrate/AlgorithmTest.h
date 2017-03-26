//
// Created by  Oleksiy Grechnyev on 3/25/2017.
//

#pragma once


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace NaviTest {
    namespace Beacons {
        namespace Calibrate {

            /// Unit tests : calibration algorithms
            class AlgorithmTest : public CPPUNIT_NS::TestFixture {

            CPPUNIT_TEST_SUITE(AlgorithmTest);
                    CPPUNIT_TEST(testLeastSquares);
                    CPPUNIT_TEST(testCalibrateLeastSquares);
                    CPPUNIT_TEST(testCalibrateOnePointD);
                    CPPUNIT_TEST(testCalibrateOnePointT);
                    CPPUNIT_TEST(testCalibrateOnePointG);
                CPPUNIT_TEST_SUITE_END();
            public: // === Methods ===

                /// Test linear least squares
                void testLeastSquares();

                /// Test least squares calibration
                void testCalibrateLeastSquares();

                /// Test 1-point calibration (D)
                void testCalibrateOnePointD();

                // Test 1-point calibration (T)
                void testCalibrateOnePointT();

                // Test 1-point calibration (G)
                void testCalibrateOnePointG();

            };
        }
    }
}



