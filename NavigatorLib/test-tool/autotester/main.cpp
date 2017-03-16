//
// Created by  Oleksiy Grechnyev on 2/17/2017.
//
#include <iostream>
#include <string>
#include <cstdio>

#include "AutoTesterEngine.h"

namespace autotester{
    /// Print usage and exit(1)
    void printUsage(){
        using namespace std;

        cout << "AutoTester: Automatically run Tester Engine in all subdirectories of a directory." << endl;
        cout << "It uses CppUnit and is TeamCity-compatible." << endl << endl;
        cout << "Usage :" << endl;
        cout << "autotester <test-dir> <delta-allowance>" << endl << endl;
        cout << "<testdir>  = directory containing test subdirectories." << endl;
        cout << "<deta-allowance> = Max Delta allowance to pass the test." << endl << endl;
        cout << "Example: " << endl;
        cout << "autotester TESTS 0.1" << endl;

        exit(1);
    }
}

int main(int argc, char *argv[]){
    using namespace std;
    using namespace autotester;

    // Parse the command line parameters
    if (argc<3) printUsage(); // Must have 2 args

    string testDir(argv[1]); // Test directory
//    cout << "testDir = " << testDir << endl;

    double deltaAllowance = 17; // MaxDelta allowance in tests
    // Parse the double value
    if (sscanf(argv[2], "%lf", &deltaAllowance) != 1)  printUsage();
//    cout << "deltaAllowance = " << deltaAllowance << endl;

    // Create an AutoTesterEngine engine
    AutoTesterEngine engine(testDir, deltaAllowance);

    // Run tests
    bool result = engine.run();

    // Return 0 if all OK
    return result ? 0 : 1;
}