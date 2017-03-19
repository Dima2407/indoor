//
// Created by  Oleksiy Grechnyev on 2/17/2017.
//

#ifndef TESTTOOL_TESTCLASS_H
#define TESTTOOL_TESTCLASS_H

#include <cppunit/TestCase.h>

#include "global.h"

namespace autotester {
    /// Class used for the CppUnit testing: run Tester Engine in the current dir
    class TestClass : public CppUnit::TestCase {
    public:
        /// Run the tester Engine and check maxDelta
        void test1();
    };
}

#endif //TESTTOOL_TESTCLASS_H
