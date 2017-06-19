//
// Created by  Victor Draban on 6/15/2017.
//

#include "Navigator/Accel/FilterImpl.h"
#include <vector>
#include "FilterImplTest.h"


namespace NaviTest {
    namespace Accel {
        CPPUNIT_TEST_SUITE_REGISTRATION(FilterImplTest);

        void FilterImplTest::testClass() {
            CPPUNIT_ASSERT(workClass());
            CPPUNIT_ASSERT(doesNotWorkClass());
            CPPUNIT_ASSERT(testValues());
        }

        bool FilterImplTest::workClass() {
            Navigator::Math::Filter::IFilter::Value val(2,1);
            std::vector<double> a{1};
            std::vector<double> b{1};
            Navigator::Accel::FilterImpl myObj(10, a, b);
            return myObj.process(val) == val;
        }

        bool FilterImplTest::doesNotWorkClass() {
            using namespace Navigator::Math::Filter;
            using namespace Navigator::Accel;
            IFilter::Value val(2,1);
            IFilter::Value val2(1,2);
            std::vector<double> a{1};
            std::vector<double> b{1};
            FilterImpl myObj(10, a, b);
            return myObj.process(val) != val2;
        }

        bool FilterImplTest::testValues() {
            using namespace Navigator::Math::Filter;
            using namespace Navigator::Accel;
            bool result = true;
            std::vector<double> a{1};
            std::vector<double> b{1};
            FilterImpl myObj(10, a, b);
            IFilter::Value arr[] = {{1,1}, {2,3}, {3,7}, {4,19}, {5,31}, {6,118}};
            for (const auto & item : arr) {
                if (myObj.process(item) != item) {
                    result = false;
                    break;
                }
            }
            return result;
        }

    }
}
