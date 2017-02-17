//
// Created by  Oleksiy Grechnyev on 2/17/2017.
//
#include <iostream>

#include "UnitEngine.h"

int main(){
    using namespace std;
    using namespace unit;

    // Create an engine
    UnitEngine engine("TESTS", 0.05);

    // Run tests
    bool result = engine.run();

    return result ? 0 : 1;
}