//
// Created by  Oleksiy Grechnyev on 2/17/2017.
//

#ifndef TESTTOOL_UNITENGINE_H
#define TESTTOOL_UNITENGINE_H

#include <string>
#include <vector>

#include <cppunit/TestCaller.h>

#include "TestClass.h"

namespace unit {

    /// Unit testing framework for unit
    class UnitEngine {
    public:
        /** Constructor
         *
         * @param testDir          The directory with unit tests
         * @param deltaAllowance   The maximally allowed delta
         */
        UnitEngine(const std::string &testDir, double deltaAllowance) : testDir(testDir),
                                                                        deltaAllowance(deltaAllowance) {}

        /**\brief Run all unit tests from the directory testDir
         *
         * @return                    true if all test successful
         */
        bool run();
    private:
        /// The directory with unit tests
        std::string testDir;
        /// The maximally allowed delta
        double deltaAllowance;

        /// Run the tests with a list of directory names
        bool runTests(std::vector<std::string> names);

    };
}

#endif //TESTTOOL_UNITENGINE_H
