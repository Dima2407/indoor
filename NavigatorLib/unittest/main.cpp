//
// Created by  Oleksiy Grechnyev on 3/12/2017.
//

#include <iostream>

#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/CompilerOutputter.h>

#include "teamcity/teamcity_cppunit.h"


// Note: we DON'T include any test fixture classes here, cool !!

/** @brief Run all registered CppUnit tests
 *
 * This version uses either standard (brief+compiler) or TeamCity output
 *
 * @return   0    if success
 */
int main() {
    using namespace std;
    using namespace CPPUNIT_NS;


    // Force the teamcity-style output
    constexpr bool FORCE_TEAMCITY = false;

    // Do we use teamcity-style output ?
    bool useTeamcity = JetBrains::underTeamcity() || FORCE_TEAMCITY;

    // The test results
    TestResult result;

    // Add either Brief or TeamCity progress listener
    BriefTestProgressListener briefProgress;
    JetBrains::TeamcityProgressListener teamProgress;

    if (useTeamcity) {
        result.addListener(&teamProgress);
    } else {
        result.addListener(&briefProgress);
    }

    // Add the collector as a listener
    // I don't use collector here much, but it can be useful for various outputs, like XML
    TestResultCollector collector;
    result.addListener(&collector);

    // The runner
    TestRunner runner;

    // Add all registered tests
    runner.addTest(TestFactoryRegistry::getRegistry().makeTest());

    // RUN all tests here
    runner.run(result);

    // Output the result with an outputter
    if (!useTeamcity) {
        CompilerOutputter outputter(&collector, cerr);
        outputter.write();
    }

    // Return number of failures or 0 if successful
    return collector.testFailures();
}