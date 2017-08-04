//
// Created by  Oleksiy Grechnyev
//

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>

// This includes everything you need
#include "Navigator.h"

static bool isZero(double d){
    return fabs(d) < 1.0e-10;
}

int main()
{
    using namespace std;
    using Navigator::Math::Position3D;
    using namespace Navigator::Math::Kalman;
    using Navigator::Math::Filter::IFilter;

    cout << "Kalman Filter Test !" << endl;

    KalmanFilter filter;
    IFilter::Value result;

/*    result = filter.process(IFilter::Value(80.0, 10.0));
    cout << result.val << endl;
    result = filter.process(IFilter::Value(77.3, 11.3));
    cout << result.val << endl;
    result = filter.process(IFilter::Value(90.1, 11.5));
    cout << result.val << endl;*/

    ifstream fileIn("input_output.dat");
    ofstream fileOut("out.dat");
    fileOut.precision(10);
    ofstream filePred("pred.dat");
    filePred.precision(10);

    for (;;){
        double t, r1, r2;
        fileIn >> t >> r1 >> r2;  // Read timestamp, rawRSSI, processedRSSI
        if (!fileIn)
            break;

        if (isZero(r1))  // Zero means No RSSI
            result = filter.processOnlyPredict(t);
        else   // Regular RSSI
            result = filter.process(IFilter::Value(r1, t));

        fileOut << fixed << setw(15) << result.timeStamp  << setw(15) << r1  << setw(15) << result.val  << setw(15) << r2 << endl;

        // Predictions
        const auto & predX = filter.getTempX();
        const auto & predP = filter.getTempP();
        filePred <<  fixed << setw(15) << result.timeStamp  << setw(15) << predX(0)  << setw(15) << predX(1);
        filePred <<  fixed  << setw(15) << predP(0, 0)  << setw(15) << predP(0, 1);
        filePred <<  fixed  << setw(15) << predP(1, 0)  << setw(15) << predP(1, 1) << endl;
    }

    return 0;
}
