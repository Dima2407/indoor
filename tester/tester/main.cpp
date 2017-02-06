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

    engine.readBeaconsDAT();
    engine.readMeasurementsDAT("out_measure.dat");
    engine.run();

    return 0;
}