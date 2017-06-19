//
// Created by  Victor Draban on 6/12/2017.
//

#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Navigator/Accel/ToGlobal.h"

namespace NaviTest {
    namespace Accel {
        class ToGlobalTest : public CPPUNIT_NS::TestFixture {
            CPPUNIT_TEST_SUITE(ToGlobalTest);
                CPPUNIT_TEST(testQuaternion);
                CPPUNIT_TEST(testAngleCorrection);
                CPPUNIT_TEST(testIsStationary);
                CPPUNIT_TEST(testToGlobalProcess);
            CPPUNIT_TEST_SUITE_END();
        public:
            void testQuaternion();
            void testAngleCorrection();
            void testIsStationary();
            void testToGlobalProcess();
        private:
            double random();
            double initQuaternion();
            double testAngleCorrectionPitch175();
            double testAngleCorrectionRoll175();
            double testAngleCorrectionYaw175();
            double testAngleCorrectionPitch38();
            double testAngleCorrectionRoll38();
            double testAngleCorrectionYaw38();
            bool testHelpStationary(double x, double y, double z);
            Navigator::Accel::AccelOutputData testHelpProcess(Navigator::Accel::AccelReceivedData in);
        };
    }
}
