#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H


#include <list>
#include <vector>
#include <map>
#include <utility>
#include <limits>


typedef long long timestamp_t;
typedef long long hash_t;

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

typedef Point Vector3;

struct PointMeasurement {
    Point       position;
    timestamp_t timestamp;

    PointMeasurement& operator +=(const PointMeasurement &rhs);
};

struct Beacon {
    int    hash;
    double tx_power;
    double damp;
    Point  position;
};

struct BeaconMeasurement {
    BeaconMeasurement() : hash(-1), txPower(0), rssi(0), timestamp(-1) {}
    int    hash;
    double txPower;
    double rssi;
    timestamp_t   timestamp;
};

struct AccMeasurement {
    AccMeasurement() : timestamp(-1) {values.x = values.y = values.z = 0;}
    Vector3 values;
    timestamp_t    timestamp;
};

struct GyroMeasurement {
    Vector3 values;
    timestamp_t    timestamp;
};


typedef std::map<int, Beacon>        BeaconsContainer;

typedef std::list<AccMeasurement>    AccelerationMeasurementsContainer;
typedef std::list<GyroMeasurement>   GyroscopeMeasurementsContainer;
typedef std::list<BeaconMeasurement> BeaconMeasurementsContainer;
typedef std::list<PointMeasurement>  CoordinateMeasurementsContainer;

typedef AccelerationMeasurementsContainer           AccelerationHistoryContainer;
typedef GyroscopeMeasurementsContainer              GyroscopeHistoryContainer;
typedef std::map<int, BeaconMeasurementsContainer > BeaconHistoryContainer;
typedef CoordinateMeasurementsContainer             CoordinateHistoryContainer;

typedef std::list<Point> PointContainer;
typedef std::list<double>      DistancesContainer;


struct Session {
    BeaconMeasurementsContainer          beaconMeasurements;
    AccelerationMeasurementsContainer    accMeasurements;               // received data from acceleration unit (ax, ay, az)
    GyroscopeMeasurementsContainer       gyroMeausrements;              // received data from gyroscope unit unit (gx, gy, gz)
    time_t timestamp_beg;
    time_t timestamp_end;

    void clear() {
        beaconMeasurements.clear();
        accMeasurements.clear();
        gyroMeausrements.clear();
        timestamp_beg =  std::numeric_limits<timestamp_t>::max();
        timestamp_end = -std::numeric_limits<timestamp_t>::max();
    }

    bool ready () {
        return !(beaconMeasurements.empty() || accMeasurements.empty() || gyroMeausrements.empty());
    }
};

typedef std::list<Session>         SessionContainer;


struct ObjectState {
    ObjectState() : position(Point()), velocity(Point()), acceleration(Point()), rotation(Point()), timestamp(-1) {}
    time_t timestamp;
    Point position;
    Point velocity;
    Point acceleration;
    Point rotation; // x - azimuth; y - elevation; z - anticlockwise angle around bottom-to-top device line (horizontal, sceen up);
    bool valid () const {return timestamp >= 0;}
};

struct JointObjectState {
    ObjectState beaconData;
    ObjectState accelerometerData;
    ObjectState gyroscopeData;
    ObjectState magnitometerData;

    ObjectState jointData;
};

typedef std::list<JointObjectState> JointObjectStateContainer;
typedef JointObjectStateContainer   JointObjectStateHistory;

Point operator+(const Point &p1, const Point &v2);
Point operator-(const Point &p1, const Point &v2);
Point operator*(const Point &p1, const double &val);
Point operator/(const Point &p1, const double &val);
Point operator*(const double &val, const Point &p1);
Point operator/(const double &val, const Point &p1);
PointMeasurement operator+(const PointMeasurement &p1, const PointMeasurement &v2);
PointMeasurement operator*(const PointMeasurement &p1, const double &val);

namespace CommonConstants {
    extern const double time_multiplicator;

    template<typename T>
    T big_value() {
        return std::numeric_limits<T>::max();
    }

    template<>
    double big_value<double>();

} // CommonConstants

#if defined(BRIDGE_LIBRARY)
#   include "common_types_lib_dependence.h"
#endif

#endif // COMMON_TYPES_H
