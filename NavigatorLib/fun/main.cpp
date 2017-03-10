//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#define _USE_MATH_DEFINES

#include <iostream>
#include <array>
#include <random>
#include <chrono>
#include <ctime>
#include <cmath>

#include "NoFilter.h"

int main()
{

    using namespace std;
    using namespace navi_beacon;

    // Let's have some fun with the filters

    // Seed the random generator, MinGW-friendly version
    mt19937 randomEngine(time(nullptr));

    // double random distribution
    uniform_real_distribution<double> uDouble(-1.0, 1.0);

    // Input and output data
    const int SIZE = 100;

    const double dt = 1.0;

    array <double, SIZE> inData, outData;

    // Create the in data

    for (int i=0; i<SIZE; i++)
    {
        // inData[i] = i*0.5 + 0.7; // Some linear function
        inData[i] = 2.0*sin(M_PI*i/20);
        inData[i] +=  1.0 * uDouble(randomEngine); // Add random noise
    }

    // Define a filter
    NoFilter noFilter;
    IFilter & filter = noFilter;

//    IFilter && filter = NoFilter();

    // Run the data through the filter
    for (int i=0; i<SIZE; i++)
    {
        outData[i] = filter.run(inData[i]);
    }

    // Write the result
    for (int i=0; i<SIZE; i++)
    {
        cout << i << "    " << inData[i]  << "    " << outData[i] << endl;
    }

    return 0;
}