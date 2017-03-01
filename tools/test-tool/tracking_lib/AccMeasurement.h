//
// Created by  Oleksiy Grechnyev on 3/1/2017.
//

#ifndef TESTTOOL_ACCMEASUREMENT_H
#define TESTTOOL_ACCMEASUREMENT_H

#include "common_defs.h"
#include "Point.h"

/** \brief Accelerator measurement with a timestamp */
struct AccMeasurement {
    AccMeasurement() : timestamp(-1) {values.x = values.y = values.z = 0;}
    Vector3 values;
    timestamp_t    timestamp;
};

typedef std::list<AccMeasurement>    AccelerationMeasurementsContainer;
typedef AccelerationMeasurementsContainer           AccelerationHistoryContainer;


#endif //TESTTOOL_ACCMEASUREMENT_H
