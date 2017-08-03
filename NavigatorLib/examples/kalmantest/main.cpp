//
// Created by  Oleksiy Grechnyev
//

#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>

// This includes everything you need
#include "Navigator.h"


int main()
{
    using namespace std;
    using Navigator::Math::Position3D;
    using namespace Navigator::Math::Kalman;
    using Navigator::Math::Filter::IFilter;

    cout << "Kalman Filter Test !" << endl;

    KalmanFilter filter;

    IFilter::Value result = filter.process(IFilter::Value(80.0, 10.0));
    cout << result.val << endl;

    result = filter.process(IFilter::Value(77.3, 11.3));
    cout << result.val << endl;

    result = filter.process(IFilter::Value(90.1, 11.5));
    cout << result.val << endl;

    
    return 0;
}
