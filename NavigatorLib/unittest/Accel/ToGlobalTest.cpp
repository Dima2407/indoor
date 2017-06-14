//
// Created by  Victor Draban on 6/14/2017.
//

#include "ToGlobalTest.h"
#include "Navigator/Accel/ToGlobal.h"
#include <cmath>

namespace NaviTest {
    namespace Accel {

        CPPUNIT_TEST_SUITE_REGISTRATION(ToGlobalTest);

        void ToGlobalTest::testQuaternion() {
            constexpr double accuracy = 1.0e-10;

//            double pitch = 0.2;
//            double roll = 0.3;
//            double yaw = 0.4;
            Navigator::Accel::ToGlobal global;
//            Eigen::Quaternion<double> q1 = global.initQuaternion(pitch, roll, yaw);
            std::cout << " Hello world" << std::endl;
            std::cout << CPPUNIT_ASSERT(true) << std::endl;
            std::cout << CPPUNIT_ASSERT(false) << std::endl;
//            CPPUNIT_ASSERT(global.initQuaternion(random(), random(), random()).norm() - 1 < accuracy);
//            CPPUNIT_ASSERT(global.initQuaternion(random(), random(), random()).norm() - 1 < accuracy);
//            CPPUNIT_ASSERT(global.initQuaternion(random(), random(), random()).norm() - 1 < accuracy);
//            CPPUNIT_ASSERT(global.initQuaternion(random(), random(), random()).norm() - 1 < accuracy);
//            CPPUNIT_ASSERT(global.initQuaternion(random(), random(), random()).norm() - 1 < accuracy);
//            CPPUNIT_ASSERT(global.initQuaternion(random(), random(), random()).norm() - 1 < accuracy);
//            CPPUNIT_ASSERT(global.initQuaternion(random(), random(), random()).norm() - 1 < accuracy);
        }

        double ToGlobalTest::random() {
            return ((rand()%100)/100.0)*2*M_PI;
        }
    }
}
