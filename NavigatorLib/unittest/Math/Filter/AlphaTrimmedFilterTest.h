//
// Created by  Oleksiy Grechnyev on 4/4/2017.
//

#pragma once


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Navigator/Math/Filter/AlphaTrimmedFilter.h"


namespace NaviTest {
    namespace Math {
        namespace Filter {
            class AlphaTrimmedFilterTest : public CPPUNIT_NS::TestFixture {

            CPPUNIT_TEST_SUITE(AlphaTrimmedFilterTest);
                    CPPUNIT_TEST(test1);
                    CPPUNIT_TEST(test4);
                CPPUNIT_TEST_SUITE_END();
            public:
                /// Test size-1 filters
                void test1();

                /// Test size-4 filters
                void test4();

            private:
                /// Run a double through the filter, addding unused zero timestamp
                double runAT(Navigator::Math::Filter::AlphaTrimmedFilter & filter, double in) {
                    return filter.process(
                            Navigator::Math::Filter::IFilter::Value(in, 0.0)
                    ).val;
                }
            };
        }
    }
}

