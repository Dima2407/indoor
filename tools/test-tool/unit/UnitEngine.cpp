//
// Created by  Oleksiy Grechnyev on 2/17/2017.
//

#include <iostream>


#include <cppunit/TestResult.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/CompilerOutputter.h>
#include <cassert>
#include <cstring>

#include "UnitEngine.h"
#include "teamcity_cppunit.h"

// Choose the dirent.h file + header for chdir()
// Unix uses POSIX dirent.h (+ unistd.h for chdir() )
// Windows should use windirent.h, including MinGW, because
// dirent.h in MinGW does not have d_type, not good!
// That's why I use windirent.h for MinGW and not dirent.h
#if defined(_WIN32) || defined(WIN32)

#include "windirent.h"
// #include <direct.h>

#else

#include <dirent.h>
#include <unistd.h>

#endif

namespace unit {

    bool UnitEngine::run() {
        using namespace std;

        // Names of all test directories
        std::vector<std::string> dirNames;

        // CD to the directory with tests
        if (chdir(testDir.c_str())) {
            cerr << "ERROR : cannot chdir() to directory " << testDir << endl;
            exit(1);
        }

        // Scan the directory structure
        DIR *dir;
        struct dirent *ent;
        string prefix;

        dir = opendir(".");

        while (ent = readdir(dir)) {
//            prefix = (ent->d_type == DT_DIR) ? "DIR : " : "FILE : ";
//            cout << prefix << ent->d_name << endl;

            // Check if the entry is a proper directory name (files and dirs starting with '.' excluded)
            if (strlen(ent->d_name) && ent->d_name[0] != '.' && ent->d_type == DT_DIR) {
                // Add the entry to the list
                dirNames.push_back(string(ent->d_name));
            }
        }

        closedir(dir);

        return runTests(dirNames);
    }

    bool UnitEngine::runTests(const std::vector<std::string> &names) {

        // Here I used CppUnit in a rather perverse way:
        // Rather than writing a bunch of test in the program,
        // I generated them at runtime from subdirectory names
        // Don't do that if you just want some test with CppUnit

        using namespace CppUnit;
        using namespace std;

        TestResult result;

        // Add one progress listener
        BriefTestProgressListener progress;
        JetBrains::TeamcityProgressListener teamProgress;

        // Use special output format under TeamCity
        if (JetBrains::underTeamcity()) {
            result.addListener(&teamProgress);

        } else {
            result.addListener(&progress);
        }

        // Add result collector
        TestResultCollector collector;
        result.addListener(&collector);

        // TestCaller has to be declared outside of the for loop scope
        // And should not be destoryed before all tests are finished
        // Some funny destructor ???
        // Also I can't make a vector of TestCaller<TestClass> for some strange reason

        vector<TestCaller<TestClass> *> callers;

        // Run tests. name = name of subdir and also of the test
        for (const string &name : names) {

            // Set the delta allowance: the global variable and the test parameter
            global::deltaAllowance = deltaAllowance;

            // Create a test. I don't delete them until ALL tests are done.
            callers.push_back(new TestCaller<TestClass>(name, &TestClass::test1));

            // Go to the test dir
            assert(!chdir(name.c_str()));

            // Run the test
            callers.back()->run(&result);

            // Leave the test dir: Go back up one level
            assert(!chdir(".."));

        }

        if (! JetBrains::underTeamcity()) {
            // Output results
            CompilerOutputter compilerOutputter(&collector, cout);
            compilerOutputter.write();
        }

        // Store the true/false result
        bool boolResult = collector.wasSuccessful();

        // Now we can delete the callers
        for (auto c: callers) {
            delete c;
        }

        return boolResult;
    }


}