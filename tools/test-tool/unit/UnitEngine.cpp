//
// Created by  Oleksiy Grechnyev on 2/17/2017.
//

#include <iostream>


#include <cppunit/TestResult.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/CompilerOutputter.h>
#include <cassert>

#include "UnitEngine.h"

// Choose the dirent.h file + header for chdir
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
        assert(! chdir(testDir.c_str()));

        // Scan the directory structure
        DIR *dir;
        struct dirent *ent;
        string prefix;

        assert(dir = opendir ("."));

        closedir (dir);

        return runTests(dirNames);
    }

    bool UnitEngine::runTests(std::vector<std::string> names) {

        using namespace CppUnit;
        using namespace std;

        TestResult result;

        // Add progress listener
        BriefTestProgressListener progress;
        result.addListener(&progress);

        // Add result collector
        TestResultCollector collector;
        result.addListener(&collector);

        // Runner has to be declared outside of the for loop scope
        // Some funny destructor ???

        // TestCaller<TestClass> caller("Brianna", &TestClass::test1);


        vector<TestCaller<TestClass> *> callers;

        // Run tests
        for (int i = 0; i < 10; i++) {

            stringstream name;
            name << "Brianna" << i;

            global::value = i == 4 ? 3 : 2;
            //global::value =  2;

            // Create a test
            callers.push_back(new TestCaller<TestClass>(name.str(), &TestClass::test1));

            // Run the test
            //callers[i]->run(&result);
            callers.back()->run(&result);

        }
        // Output results
        CompilerOutputter compilerOutputter(&collector, cout);
        compilerOutputter.write();

        // Store the true/false result
        bool boolResult = collector.wasSuccessful();

        // Now we can delete the callers
        for (auto c: callers) {
            delete c;
        }

        return boolResult;
    }


}