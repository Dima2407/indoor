//
// Created by  Oleksiy Grechnyev on 3/1/2017.
//

#ifndef TESTTOOL_POINTMEASUREMENT_H
#define TESTTOOL_POINTMEASUREMENT_H

#include "Point.h"
#include "common_defs.h"

/** \brief A point measurement: Point + timestamp */
struct PointMeasurement {
    Point       position;
    timestamp_t timestamp;

    PointMeasurement& operator +=(const PointMeasurement &rhs);
};

PointMeasurement operator+(const PointMeasurement &p1, const PointMeasurement &v2);
PointMeasurement operator*(const PointMeasurement &p1, const double &val);

typedef std::list<PointMeasurement>  CoordinateMeasurementsContainer;
typedef CoordinateMeasurementsContainer             CoordinateHistoryContainer;


#endif //TESTTOOL_POINTMEASUREMENT_H
