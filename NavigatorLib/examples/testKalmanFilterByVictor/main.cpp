//
// Created by  Victor Draban on 6/9/2017.
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "Navigator/Accel/FilterImpl.h"
#include "Navigator/Math/Kalman/KalmanFilter.h"

using namespace std;
using namespace Navigator;
using namespace Math;

// Test Kalman's filtr
int main() {
    std::vector<double> vecVal;
    std::vector<double> vecTimestamp;
    std::vector<double> vecValResult;
    double buff;
    cout << fixed << setprecision(6);
    ifstream fin("C:/QtProjects/KalmanTestData/input_output.txt");
    while (fin >> buff) {
        vecTimestamp.push_back(buff);
        fin >> buff;
        vecVal.push_back(buff);
        fin >> buff;
        vecValResult.push_back(buff);
    }
    fin.close();

    Kalman::KalmanFilter filter;
    for (int i = 0; i < vecVal.size(); ++i) {
        double rssi = vecVal[i];
        double timestamp = vecTimestamp[i];
        Filter::IFilter::Value result;
        if (rssi == 0.000000) {
            result = filter.processOnlyPredict(timestamp);
        } else {
            Filter::IFilter::Value val(rssi, timestamp);
            result = filter.process(val);
        }
//        cout << " result-rssi = " << result.val << " <-----> ";
//        cout << " vecValResult = " << vecValResult[i] << " <------> " ;
//        cout << vecValResult[i] - result.val << endl;
    }

    return 0;
}
