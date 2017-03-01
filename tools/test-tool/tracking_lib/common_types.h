#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

/** \file common_types.h
 * \brief Contains a number of very important structures.
 *
 * Note: Some structures (Beacon, ObjectState) have namesakes in other files!
 */
 
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <limits>

typedef long long timestamp_t;
typedef long long hash_t;

/** \brief An (X, Y, Z) point in 3D space
 *
 * Defines trivial operators to work with Points
 */
struct Point {
    Point() : x(0), y(0), z(0) {}
    double x;
    double y;
    double z;

    Point& operator +=(const Point &rhs);
    Point& operator -=(const Point &rhs);
    Point& operator *=(const Point &rhs);
    Point& operator *=(const double &rhs);
    Point& operator /=(const double &rhs);
    Point& operator /=(const Point  &rhs);
    Point& operator  -();
};


Point operator+(const Point &p1, const Point &v2);
Point operator-(const Point &p1, const Point &v2);
Point operator*(const Point &p1, const double &val);
Point operator/(const Point &p1, const double &val);
Point operator*(const double &val, const Point &p1);
Point operator/(const double &val, const Point &p1);


typedef Point Vector3;



/** \brief A point measurement: Point + timestamp */
struct PointMeasurement {
    Point       position;
    timestamp_t timestamp;

    PointMeasurement& operator +=(const PointMeasurement &rhs);
};

PointMeasurement operator+(const PointMeasurement &p1, const PointMeasurement &v2);
PointMeasurement operator*(const PointMeasurement &p1, const double &val);

/** \brief %Beacon measurement data (hash, txPower, rssi, timestamp)*/
struct BeaconMeasurement {
    /// Default constructor with stupid values
    BeaconMeasurement() : hash(-1), txPower(0), rssi(0), timestamp(-1) {}
    /// Beacon unique ID (MAC address hash ?)
    int    hash;
    /// Beacon unique ID (MAC address hash ?)
    double txPower;
    /// Recieved signal strength, logarithmic
    double rssi;
    /// Time stamp of the measurement
    timestamp_t   timestamp;
};

/** \brief Accelerator measurement with a timestamp */
struct AccMeasurement {
    AccMeasurement() : timestamp(-1) {values.x = values.y = values.z = 0;}
    Vector3 values;
    timestamp_t    timestamp;
};

typedef std::list<AccMeasurement>    AccelerationMeasurementsContainer;
typedef std::list<BeaconMeasurement> BeaconMeasurementsContainer;
typedef std::list<PointMeasurement>  CoordinateMeasurementsContainer;

typedef AccelerationMeasurementsContainer           AccelerationHistoryContainer;
typedef std::map<int, BeaconMeasurementsContainer > BeaconHistoryContainer;
typedef CoordinateMeasurementsContainer             CoordinateHistoryContainer;

typedef std::list<Point> PointContainer;
typedef std::list<double>      DistancesContainer;


namespace CommonConstants {
    extern const double time_multiplicator;

    template<typename T>
    T big_value() {
        return std::numeric_limits<T>::max();
    }

    template<>
    double big_value<double>();

} // CommonConstants

// #if defined(BRIDGE_LIBRARY)
// This is was stupid, this include is needed in any case

#include "common_types_lib_dependence.h"

// #endif

#endif // COMMON_TYPES_H
