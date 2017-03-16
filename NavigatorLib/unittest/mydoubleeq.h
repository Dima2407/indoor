//
// Created by  Oleksiy Grechnyev on 3/13/2017.
//

#include <cmath>

#pragma once
namespace NaviTest {
    /// Check that abs(d1 - d2) < accuracy
    bool inline myDoubleEq(double d1, double d2, double accuracy) {
        return fabs(d1 - d2) < accuracy;
    }
}

