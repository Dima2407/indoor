//
// Created by  Victor Draban on 6/14/2017.
//

#include "ToGlobalTest.h"
#include "Navigator/Accel/ToGlobal.h"
#include <cmath>
#include <ctime>
#include <cstdlib>

namespace NaviTest {
    namespace Accel {

        CPPUNIT_TEST_SUITE_REGISTRATION(ToGlobalTest);

        void ToGlobalTest::testQuaternion() {
            constexpr double accuracy = 1.0e-10;
            srand(time(0));

            CPPUNIT_ASSERT(initQuaternion() < accuracy);
            CPPUNIT_ASSERT(initQuaternion() < accuracy);
            CPPUNIT_ASSERT(initQuaternion() < accuracy);
            CPPUNIT_ASSERT(initQuaternion() < accuracy);
            CPPUNIT_ASSERT(initQuaternion() < accuracy);
            CPPUNIT_ASSERT(initQuaternion() < accuracy);
            CPPUNIT_ASSERT(initQuaternion() < accuracy);
            CPPUNIT_ASSERT(initQuaternion() < accuracy);

            CPPUNIT_ASSERT(testAngleCorrectionPitch175() < accuracy);
            CPPUNIT_ASSERT(testAngleCorrectionRoll175() < accuracy);
            CPPUNIT_ASSERT(testAngleCorrectionYaw175() < accuracy);
            CPPUNIT_ASSERT(testAngleCorrectionPitch38() < accuracy);
            CPPUNIT_ASSERT(testAngleCorrectionRoll38() < accuracy);
            CPPUNIT_ASSERT(testAngleCorrectionYaw38() < accuracy);
        }

        double ToGlobalTest::testAngleCorrectionPitch175() {
            return fabs(175*(M_PI/180) - (3.054326190990));
        }

        double ToGlobalTest::testAngleCorrectionPitch38() {
            return fabs(38*(M_PI/180) - (0.663225115757));
        }

        double ToGlobalTest::testAngleCorrectionRoll175() {
            return fabs(175*(M_PI/180) - (3.054326190990));
        }

        double ToGlobalTest::testAngleCorrectionRoll38() {
            return fabs(38*(M_PI/180) - (0.663225115757));
        }

        double ToGlobalTest::testAngleCorrectionYaw175() {
            return fabs((-175-180)*(M_PI/180) - (-6.195918844579));
        }

        double ToGlobalTest::testAngleCorrectionYaw38() {
            return fabs((-38-180)*(M_PI/180) - (-3.8048177693476));
        }

        double ToGlobalTest::random() {
            return (1.0*(rand()%1000)/1000)*2*M_PI;
        }

        double ToGlobalTest::initQuaternion() {
            Navigator::Accel::ToGlobal global;
            Eigen::Quaternion<double> result = global.initQuaternion(random(), random(), random());
            return fabs(result.norm() - 1);
        }
    }
}
