//
// Created by  Oleksiy Grechnyev on 2/17/2017.
//

#include "TestClass.h"

#include <fstream>

#include "Engine.h"

namespace unit {
    void TestClass::test1() {
        using namespace std;
        using namespace tester;

        // Create a tester Engine
        Engine *engine = new Engine();

        // Run the engine silently
        engine->readData(false); // Read data (verbose = false)
        engine->runLocation();   // Run location
        engine->runDelta();   // Run delta
        // Note: no engine->writeData() !

        double maxDelta = engine->getMaxDelta();

        ofstream out("unit_maxdelta.txt");
        out << "maxDelta = " << maxDelta << endl;
        //cout << "maxDelta = " << maxDelta << endl;
        out.close();

        // The fateful assert: see that maxDelta is small enough

        CPPUNIT_ASSERT(maxDelta < global::deltaAllowance);

        delete engine;
    }
}