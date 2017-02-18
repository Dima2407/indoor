//
// Created by  Oleksiy Grechnyev on 2/17/2017.
//
#include <iostream>

#include "UnitEngine.h"

namespace unit{
    /// Print usage and exit(1)
    void printUsage(){
        using namespace std;

        cout << "Unit: Automatically run Tester Engine in all subdirectorues of a directory." << endl;
        cout << "It uses CppUnit and is TeamCity-compatible" << endl << endl;
        cout << "Usage :" << endl;
        cout << "unit <test-dir> <delta-allowance>" << endl << endl;

    }
}

int main(){
    using namespace std;
    using namespace unit;

    // Create an engine
    UnitEngine engine("TESTS", 0.05);

    // Run tests
    bool result = engine.run();

    return result ? 0 : 1;
}