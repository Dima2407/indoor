//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <array>
#include <random>
#include <chrono>
#include <ctime>
#include <cmath>

#include "Math/Filter/NoFilter.h"
#include "Math/Filter/AlphaBetaFilter.h"

int main()
{

    using namespace std;
    using namespace Navi::Math::Filter;

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
        inData[i] = 2.0 * sin(M_PI*i/20);
        inData[i] +=  1.0 * uDouble(randomEngine); // Add random noise
    }

    // Define a filter
//    NoFilter noFilter;
    AlphaBetaFilter aFilter(0.2, 0.2);
    IFilter & filter = aFilter;

//    IFilter && filter = NoFilter();

    // Run the data through the filter
    for (int i=0; i<SIZE; i++)
    {
        outData[i] = filter.process(inData[i]);
    }

    // Create a file
    ofstream out("fun_out.dat");

    // Write the result
    for (int i=0; i<SIZE; i++)
    {
        out << i << "    " << inData[i]  << "    " << outData[i] << endl;
    }

    out.close();

    return 0;
}