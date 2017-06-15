//
// Created by Igor Maschikevich on 6/14/2017.
//
#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

namespace NaviTest {
namespace Accel {
class AlgorithmZUPTTest: public CPPUNIT_NS::TestFixture {


    CPPUNIT_TEST_SUITE(AlgorithmZUPTTest);
    CPPUNIT_TEST(test1);
    CPPUNIT_TEST_SUITE_END();

public: //===== Methods
    /// Test a simple mesh w/o mask
    void test1();

    // Test the same mesh with a mask table
    //    void testMask();

private: //==== Methods
   rand();


};
}
}
