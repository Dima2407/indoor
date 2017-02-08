#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "MyBeacon.h"
#include "MyBridge.h"
#include "Engine.h"
#include "Util.h"

int main() {
    using namespace std;
    using namespace tester;

    // Create tester engine
    Engine engine;

    engine.readData(); // Read data
    engine.runLocation();   // Run location
    engine.runDelta();   // Run delta
    engine.writeData();  // Write results

    return 0;
}