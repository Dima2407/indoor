//
// Created by  Oleksiy Grechnyev on 4/4/2017.
//

#pragma once


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Navigator/Math/Filter/AlphaTrimmedFilter.h"

namespace Navigator {
    namespace Math {
        namespace Filter {
            class AlphaTrimmedFilterTest : public CPPUNIT_NS::TestFixture {

            CPPUNIT_TEST_SUITE(AlphaTrimmedFilterTest);
                    CPPUNIT_TEST(test1);
                CPPUNIT_TEST_SUITE_END();

                /// Test size-1 filter,
                void test1();
            };
        }
    }
}

