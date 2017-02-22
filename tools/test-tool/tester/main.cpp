#include <iostream>
#include <cassert>

#include "MyBeacon.h"
#include "MyBridge.h"
#include "Engine.h"
#include "Util.h"

int main() {
    using namespace std;
    using namespace tester;

    // Create tester engine
    Engine engine;

    if (! engine.readData(true)) return 1; // Read data (verbose = true)
    engine.runLocation();   // Run location
    engine.runDelta();   // Run delta
    engine.writeData();  // Write results

    return 0;
}