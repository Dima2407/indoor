#include <iostream>
#include <fstream>
#include <vector>

#include "../common_lib/MyBeacon.h"
#include "MyBridge.h"
#include "Engine.h"

int main() {
    using namespace std;
    using namespace tester;

    // Create tester engine
    Engine engine;

    engine.readData(); // Read data
    engine.run();   // Run
    engine.writeData();  // Write results

    return 0;
}