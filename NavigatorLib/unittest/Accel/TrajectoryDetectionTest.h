//
// Created by Igor Maschikevich on 6/15/2017.
//

#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


namespace NaviTest {
namespace Accel{
class TrajectoryDetectionTest  : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(TrajectoryDetectionTest);
    CPPUNIT_TEST(test1);
    CPPUNIT_TEST_SUITE_END();
public:
    /// Test a simple mesh
    void test1();
};

}
}
