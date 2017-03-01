//
// Created by  Oleksiy Grechnyev on 2/28/2017.
/// This is the UNUSED part of the old common_types.h

#ifndef TESTTOOL_COMMON_TYPES2_H
#define TESTTOOL_COMMON_TYPES2_H

#include "common_defs.h"



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

/// UNUSED
typedef std::map<int, Beacon>        BeaconsContainer;

/** \brief Gyroscope measurement with a timestamp */
struct GyroMeasurement {
    Vector3 values;
    timestamp_t    timestamp;
};


typedef std::list<GyroMeasurement>   GyroscopeMeasurementsContainer;
typedef GyroscopeMeasurementsContainer              GyroscopeHistoryContainer;


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


// General methods to work with common types
std::vector<double> getRssiVectorFromMeasurements(const BeaconMeasurementsContainer &);
std::vector<double> getTxVectorFromMeasurements  (const BeaconMeasurementsContainer &);
std::vector<time_t>   getTimestampVectorFromMeasurements(const BeaconMeasurementsContainer &);


#endif //TESTTOOL_COMMON_TYPES2_H
