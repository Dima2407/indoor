//
// Created by  Oleksiy Grechnyev on 3/13/2017.
//

#pragma once


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Math/Filter/MovingAverageFilter.h"

namespace NaviTest {

    /// Test the Filter Class MovingAverageFilter
    class MovingAverageFilterTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(MovingAverageFilterTest);
            CPPUNIT_TEST(testAvg);
        CPPUNIT_TEST_SUITE_END();
    public:
        void testAvg();

    };
}


