//
// Created by  Oleksiy Grechnyev on 2/17/2017.
//

#ifndef TESTTOOL_TESTCLASS_H
#define TESTTOOL_TESTCLASS_H

#include <cppunit/TestCase.h>

#include "global.h"

namespace unit {
    /// Class used for the CppUnit testing
    class TestClass : public CppUnit::TestCase {
    public:
        void test1() {
            CPPUNIT_ASSERT(2 == global::value);
        }
    };


}

#endif //TESTTOOL_TESTCLASS_H
