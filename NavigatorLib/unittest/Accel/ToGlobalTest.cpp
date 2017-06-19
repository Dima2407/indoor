//
// Created by  Victor Draban on 6/14/2017.
//

#include "ToGlobalTest.h"
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
        }

        void ToGlobalTest::testIsStationary() {
            CPPUNIT_ASSERT(testHelpStationary(1, 1, 1) == false);
            CPPUNIT_ASSERT(testHelpStationary(2, 2, 2) == false);
            CPPUNIT_ASSERT(testHelpStationary(15, 15, 9) == false);
            CPPUNIT_ASSERT(testHelpStationary(0, 0, 0) == true);
            CPPUNIT_ASSERT(testHelpStationary(-0.1, 0, 0) == true);
        }

        void ToGlobalTest::testAngleCorrection() {
            constexpr double accuracy = 1.0e-10;

            CPPUNIT_ASSERT(testAngleCorrectionPitch175() < accuracy);
            CPPUNIT_ASSERT(testAngleCorrectionRoll175() < accuracy);
            CPPUNIT_ASSERT(testAngleCorrectionYaw175() < accuracy);
            CPPUNIT_ASSERT(testAngleCorrectionPitch38() < accuracy);
            CPPUNIT_ASSERT(testAngleCorrectionRoll38() < accuracy);
            CPPUNIT_ASSERT(testAngleCorrectionYaw38() < accuracy);
        }

        void ToGlobalTest::testToGlobalProcess() {
            CPPUNIT_ASSERT(testHelpProcess1().isStationary == true);
            CPPUNIT_ASSERT_EQUAL(0.0 , testHelpProcess1().ax);
            CPPUNIT_ASSERT_EQUAL(0.0 , testHelpProcess1().ay);
            CPPUNIT_ASSERT_EQUAL(0.0 , testHelpProcess1().az);
            CPPUNIT_ASSERT(testHelpProcess1().timestamp == 1.1);

            CPPUNIT_ASSERT(testHelpProcess2().isStationary == true);
            CPPUNIT_ASSERT_EQUAL(0.0 , testHelpProcess2().ax);
            CPPUNIT_ASSERT_EQUAL(0.0 , testHelpProcess2().ay);
            CPPUNIT_ASSERT_EQUAL(0.0 , testHelpProcess2().az);
            CPPUNIT_ASSERT(testHelpProcess2().timestamp == 1.8);
        }

        // ------------ private methods ------------------

        Navigator::Accel::AccelOutputData ToGlobalTest::testHelpProcess1() {
            Navigator::Accel::ToGlobal global;
            Navigator::Accel::AccelReceivedData in;
            Navigator::Accel::AccelOutputData out;
            in.ax = -0.1;
            in.ay = 0;
            in.az = 0;
            in.pitch = 0;
            in.roll = 0;
            in.yaw = 0;
            in.timestamp = 1.1;
            out = global.process(in);
            return out;
        }

        Navigator::Accel::AccelOutputData ToGlobalTest::testHelpProcess2() {
            Navigator::Accel::ToGlobal global;
            Navigator::Accel::AccelReceivedData in;
            Navigator::Accel::AccelOutputData out;
            in.ax = 0;
            in.ay = 0;
            in.az = 0;
            in.pitch = 10;
            in.roll = 20;
            in.yaw = 70;
            in.timestamp = 1.8;
            out = global.process(in);
            return out;
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

        bool ToGlobalTest::testHelpStationary(double x, double y, double z) {
            double ACC_TH = 1.035;
            auto a_norm = sqrt(x*x + y*y + z*z);
            return a_norm < ACC_TH ? true : false;
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
