//
// Created by Igor Maschikevich on 6/15/2017.
//

#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Navigator/Accel/TrajectoryDetection.h"


namespace NaviTest {
namespace Accel{
class TrajectoryDetectionTest  : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(TrajectoryDetectionTest);
    CPPUNIT_TEST(testAlgorithmZUPT);
    CPPUNIT_TEST_SUITE_END();
public:

    void testAlgorithmZUPT();
    void setUp() override;
    bool myDouble(double x, double y, double accuracy);
private:
    std::shared_ptr<Navigator::Accel::TrajectoryDetection> spTD;
};

}
}
