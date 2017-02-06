#ifndef AMATH_H
#define AMATH_H

#include "common_types.h"

/// Contains static method \ref sensor_navigation() (UNUSED)
class AMath {
    public:
        /// Update an ObjectState based on an acceleration measurement
        static ObjectState sensor_navigation(const ObjectState &prevState, const AccMeasurement &accMeasurement);
};

#endif // AMATH_H
