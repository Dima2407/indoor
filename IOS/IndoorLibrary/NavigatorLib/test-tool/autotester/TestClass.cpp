//
// Created by  Oleksiy Grechnyev on 2/17/2017.
//

#include "TestClass.h"

#include <fstream>

#include "Engine.h"

namespace autotester {

    void TestClass::test1() {
        using namespace std;
        using namespace tester;

        // Create a tester Engine
        Engine engine;

        // Run the engine silently
        // Read data (verbose = false), must return true for a successful test
        CPPUNIT_ASSERT(engine.readData(false));

        engine.runLocation();   // Run location
        engine.runDelta();   // Run delta
        // Note: no engine->writeData() !

        double maxDelta = engine.getMaxDelta();

        // Write actual maxDelta of a test to a file in the test's dir
        ofstream out("autotester_maxdelta.txt");
        out << "maxDelta = " << maxDelta << endl;
        //cout << "maxDelta = " << maxDelta << endl;
        out.close();

        // The fateful assert: see that maxDelta is small enough

        CPPUNIT_ASSERT(maxDelta < global::deltaAllowance);
    }
}