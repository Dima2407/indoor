//
// Created by  Oleksiy Grechnyev on 3/13/2017.
//

#pragma once


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include "Navigator/Math/Filter/MovingAverageFilter.h"

namespace NaviTest {
    namespace Math {
        namespace Filter {

            /// Test the Filter Class MovingAverageFilter
            class MovingAverageFilterTest : public CPPUNIT_NS::TestFixture
            {
                CPPUNIT_TEST_SUITE(MovingAverageFilterTest);
                CPPUNIT_TEST(testAvg);
                CPPUNIT_TEST_SUITE_END();
            public: // Methods
                void testAvg();

                /// Run a double through the filter, addding unused zero timestamp
                double runMA(Navigator::Math::Filter::MovingAverageFilter & filter, double in) {
                    return filter.process(
                            Navigator::Math::Filter::IFilter::Value(in, 0.0)
                    ).val;
                }

            };
        }
    }
}

