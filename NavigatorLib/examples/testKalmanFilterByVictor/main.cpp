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
    constexpr double accuracy = 1.0e-10;
    std::vector<double> vecVal;
    std::vector<double> vecTimestamp;
    std::vector<double> vecValResult;
    double buff;
    cout << fixed << setprecision(15);
    ifstream fin("C:/QtProjects/KalmanTestData/input_output.txt");

    while (fin >> buff) {
        vecTimestamp.push_back(buff);
        fin >> buff;
        vecVal.push_back(buff);
        fin >> buff;
        vecValResult.push_back(buff);
    }
    fin.close();

    Kalman::KalmanFilter filter();

    for (int i = 0; i < vecVal.size(); ++i) {
        double rssi = vecVal[i];
        double timestamp = vecTimestamp[i];
        Filter::IFilter::Value result;
        if (rssi == 0.00) {
//            result = filter().processOnlyPredict(timestamp);
        } else {
            Filter::IFilter::Value val(rssi, timestamp);
//            result = filter.process(val);
        }
    }
//    ifstream finX("C:/QtProjects/to_victor/tx.dat");
//    ofstream foutY("C:/QtProjects/to_victor/myTy.dat");
//    foutY << fixed << setprecision(15);
//    vector<Math::Filter::IFilter::Value> res;
//    while (finX >> buff) {
//        double timestamp = buff;
//        finX >> buff;
//        double val = buff;
//        Math::Filter::IFilter::Value myVal(val, timestamp);
//        Math::Filter::IFilter::Value result = filter.process(myVal);
//        foutY << "  " << result.timeStamp << "      " << result.val << endl;
//    }
//    foutY.close();
//    finX.close();
    return 0;
}
