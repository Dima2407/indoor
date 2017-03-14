#ifndef AMATH_H
#define AMATH_H

#include "common_types.h"


class AMath {
    public:
        static ObjectState sensor_navigation(const ObjectState &prevState, const AccMeasurement &accMeasurement);
};

#endif // AMATH_H
