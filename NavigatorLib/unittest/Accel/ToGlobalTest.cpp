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
            Eigen::Quaternion<double> quaternion = createQuaternion();

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
            // CPPUNIT_ASSERT_EQUAL(0.0 , testHelpProcess1().ax);
            // CPPUNIT_ASSERT_EQUAL(0.0 , testHelpProcess1().ay);
            // CPPUNIT_ASSERT_EQUAL(0.0 , testHelpProcess1().az);
            CPPUNIT_ASSERT(testHelpProcess1().timestamp == 1.1);

            CPPUNIT_ASSERT(testHelpProcess2().isStationary == true);
            // CPPUNIT_ASSERT_EQUAL(0.0 , testHelpProcess2().ax);
            // CPPUNIT_ASSERT_EQUAL(0.0 , testHelpProcess2().ay);
            // CPPUNIT_ASSERT_EQUAL(0.0 , testHelpProcess2().az);
            CPPUNIT_ASSERT(testHelpProcess2().timestamp == 1.8);

            CPPUNIT_ASSERT(testHelpProcess3().isStationary == false);
            CPPUNIT_ASSERT(testHelpProcess3().ax != 0 || testHelpProcess3().ay != 0 || testHelpProcess3().az != 0);
            CPPUNIT_ASSERT(testHelpProcess3().timestamp == 1.3);

            CPPUNIT_ASSERT(testHelpProcess4().isStationary == false);
            CPPUNIT_ASSERT(testHelpProcess3().ax != 0 || testHelpProcess3().ay != 0 || testHelpProcess3().az != 0);
            CPPUNIT_ASSERT(testHelpProcess4().timestamp == 2.2);
        }

        void ToGlobalTest::testLengthVectors() {
            constexpr double accuracy = 1.0e-10;
            Navigator::Accel::ToGlobal global;
            Navigator::Accel::AccelReceivedData in = testHelpCreateReceivedData(3, 4, 5, 17, 85, 129, 0.5);
            Navigator::Accel::AccelOutputData out = global.process(in);
            double lengthIn = std::sqrt(in.ax*in.ax + in.ay*in.ay + in.az*in.az);
            // double lengthOut = std::sqrt(out.ax*out.ax + out.ay*out.ay + (out.az+1)*(out.az+1));
            double lengthOut = std::sqrt(out.ax*out.ax + out.ay*out.ay + out.az*out.az);
            CPPUNIT_ASSERT(std::fabs(lengthIn - lengthOut) < accuracy);

            in = testHelpCreateReceivedData(7, 12, 1, 41, 16, 7, 2.9);
            out = global.process(in);
            lengthIn = std::sqrt(in.ax*in.ax + in.ay*in.ay + in.az*in.az);
            // lengthOut = std::sqrt(out.ax*out.ax + out.ay*out.ay + (out.az+1)*(out.az+1));
            lengthOut = std::sqrt(out.ax*out.ax + out.ay*out.ay + out.az*out.az);
            CPPUNIT_ASSERT(std::fabs(lengthIn - lengthOut) < accuracy);

            in = testHelpCreateReceivedData(15, 15, 9, 2, 2, 1, 1.9);
            out = global.process(in);
            lengthIn = std::sqrt(in.ax*in.ax + in.ay*in.ay + in.az*in.az);
            // lengthOut = std::sqrt(out.ax*out.ax + out.ay*out.ay + (out.az+1)*(out.az+1));
            lengthOut = std::sqrt(out.ax*out.ax + out.ay*out.ay + out.az*out.az);
            CPPUNIT_ASSERT(std::fabs(lengthIn - lengthOut) < accuracy);
        }

        // ------------ private methods ------------------

        Navigator::Accel::AccelOutputData ToGlobalTest::testHelpProcess1() {
            Navigator::Accel::ToGlobal global;
            Navigator::Accel::AccelReceivedData in = testHelpCreateReceivedData(-0.1, 0, 0, 0, 0, 0, 1.1);
            Navigator::Accel::AccelOutputData out = global.process(in);
            return out;
        }

        Navigator::Accel::AccelOutputData ToGlobalTest::testHelpProcess2() {
            Navigator::Accel::ToGlobal global;
            Navigator::Accel::AccelReceivedData in = testHelpCreateReceivedData(0, 0, 0, 10, 20, 70, 1.8);
            Navigator::Accel::AccelOutputData out = global.process(in);
            return out;
        }

        Navigator::Accel::AccelOutputData ToGlobalTest::testHelpProcess3() {
            Navigator::Accel::ToGlobal global;
            Navigator::Accel::AccelReceivedData in = testHelpCreateReceivedData(2, 2, 2, 10, 20, 70, 1.3);
            Navigator::Accel::AccelOutputData out = global.process(in);
            return out;
        }

        Navigator::Accel::AccelOutputData ToGlobalTest::testHelpProcess4() {
            Navigator::Accel::ToGlobal global;
            Navigator::Accel::AccelReceivedData in = testHelpCreateReceivedData(15, 15, 9, 10, 20, 70, 2.2);
            Navigator::Accel::AccelOutputData out = global.process(in);
            return out;
        }

        Navigator::Accel::AccelReceivedData ToGlobalTest::testHelpCreateReceivedData(double x, double y, double z,
                                                                                     double pitch, double roll, double yaw,
                                                                                     double timestamp) {
            Navigator::Accel::AccelReceivedData result;
            result.ax = x;
            result.ay = y;
            result.az = z;
            result.pitch = pitch;
            result.roll = roll;
            result.yaw = yaw;
            result.timestamp = timestamp;
            return result;
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

        double ToGlobalTest::myRandom() {
            return (1.0*(rand()%1000)/1000)*2*M_PI;
        }

        double ToGlobalTest::initQuaternion() {
            Navigator::Accel::ToGlobal global;
            Eigen::Quaternion<double> result = global.initQuaternion(myRandom(), myRandom(), myRandom());
            return fabs(result.norm() - 1);
        }

        Eigen::Quaternion<double> ToGlobalTest::createQuaternion() {
            Navigator::Accel::ToGlobal global;
            Eigen::Quaternion<double> result = global.initQuaternion(myRandom(), myRandom(), myRandom());
            return result;
        }
    }
}
