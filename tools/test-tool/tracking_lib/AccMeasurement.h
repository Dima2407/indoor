//
// Created by  Oleksiy Grechnyev on 3/1/2017.
//

#ifndef TESTTOOL_ACCMEASUREMENT_H
#define TESTTOOL_ACCMEASUREMENT_H

#include "common_defs.h"
#include "Point.h"

/** \brief Accelerator measurement with a timestamp */
struct AccMeasurement {
    Vector3 values; // = 0
    timestamp_t    timestamp = -1;
};

typedef std::list<AccMeasurement>    AccelerationMeasurementsContainer;
typedef AccelerationMeasurementsContainer           AccelerationHistoryContainer;


#endif //TESTTOOL_ACCMEASUREMENT_H
