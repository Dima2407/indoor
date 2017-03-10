//
// Created by  Oleksiy Grechnyev on 3/1/2017.
//

#include "PointMeasurement.h"


PointMeasurement& PointMeasurement::operator +=(const PointMeasurement &rhs) {
    this->position += rhs.position;
    this->timestamp += rhs.timestamp;
    return *this;
}


PointMeasurement operator+(const PointMeasurement &p1, const PointMeasurement &p2) {
    PointMeasurement res;
    res.position = p1.position + p2.position;
    res.timestamp = p1.timestamp + p2.timestamp;
    return res;
}

PointMeasurement operator*(const PointMeasurement &p1, const double &val) {
    PointMeasurement res;
    res.position = p1.position * val;
    res.timestamp = p1.timestamp * val;
    return res;
}
