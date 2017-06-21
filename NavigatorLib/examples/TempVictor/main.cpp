//
// Created by  Victor Draban on 6/9/2017.
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "Navigator/Accel/FilterImpl.h"

using namespace std;
using namespace Navigator;
using namespace Accel;

// Test Buttervord's filtr 8
int main(){
    vector<double> a;
    vector<double> b;
    double buff;
    cout << fixed << setprecision(15);
    ifstream finA("C:/QtProjects/to_victor/a.dat");
    ifstream finB("C:/QtProjects/to_victor/b.dat");

    while (finA >> buff) {
        a.push_back(buff);
    }
    while (finB >> buff) {
        b.push_back(buff);
    }
    finA.close();
    finB.close();

    FilterImpl filter(9, a, b);
    ifstream finX("C:/QtProjects/to_victor/tx.dat");
    ofstream foutY("C:/QtProjects/to_victor/myTy.dat");
    foutY << fixed << setprecision(15);
    vector<Math::Filter::IFilter::Value> res;
    while (finX >> buff) {
        double timestamp = buff;
        finX >> buff;
        double val = buff;
        Math::Filter::IFilter::Value myVal(val, timestamp);
        Math::Filter::IFilter::Value result = filter.process(myVal);
        foutY << "  " << result.timeStamp << "      " << result.val << endl;
    }
    foutY.close();
    finX.close();
    return 0;
}
