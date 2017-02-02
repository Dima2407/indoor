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

typedef Point Vector3;

/** \brief A point measurement: Point + timestamp */
struct PointMeasurement {
    Point       position;
    timestamp_t timestamp;

    PointMeasurement& operator +=(const PointMeasurement &rhs);
};

/** \brief Simple beacon data (hash, txPower, damp, position) (UNUSED?)
  * 
  * WARNING !!! Do not confuse this with Sensors::Hardware::Beacon in beacon.h !
  */
struct Beacon {
    /// Beacon unique ID (MAC address hash ?)
    int    hash; 
    /// Beacon unique ID (MAC address hash ?)
    double tx_power;
    /// Dampening coefficient, unitless
    double damp;
    /// Beacon XYZ position
    Point  position;
};

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

/** \brief Gyroscope measurement with a timestamp */
struct GyroMeasurement {
    Vector3 values;
    timestamp_t    timestamp;
};

/// UNUSED
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

/** \brief Session structure (all 3 types of measurements) (UNUSED).
 *
 * Contains containers for 3 types of measurements ,
 * plus "begin" and "end" timestamp.
 *
 * (UNUSED) This struct is unused as yet apparently.
 */
struct Session {
    /// Beacon measurements
    BeaconMeasurementsContainer          beaconMeasurements;
    /// Accelerator measurements
    AccelerationMeasurementsContainer    accMeasurements;               // received data from acceleration unit (ax, ay, az)
    /// Gyroscope measurements
    GyroscopeMeasurementsContainer       gyroMeausrements;              // received data from gyroscope unit unit (gx, gy, gz)
    // Begin timestamp
    time_t timestamp_beg;
    // End timestamp
    time_t timestamp_end;

    /// Remove all measurements
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

/// List of all sessions (UNUSED).
typedef std::list<Session>         SessionContainer;

/** \brief Position, velocity etc. of your object (smartphone) (Probably UNUSED)
  * 
  * Contains timestamp.
  * This is apparently a result of successful navigation (iincluding trilateration).
  *
  * WARNING !!! Do not confuse this with Types::ObjectState in objectstate.h !
  */

struct ObjectState {
    ObjectState() : position(Point()), velocity(Point()), acceleration(Point()), rotation(Point()), timestamp(-1) {}
    time_t timestamp;
    Point position;
    Point velocity;
    Point acceleration;
    Point rotation; // x - azimuth; y - elevation; z - anticlockwise angle around bottom-to-top device line (horizontal, sceen up);
    bool valid () const {return timestamp >= 0;}
};

/** \brief  Object (smartphone) pposition from different sources (UNUSED).
 *
 * Apparently the idea here is to get device position from different source and the average of some kind.
 * This is UNUSED.
 */
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
