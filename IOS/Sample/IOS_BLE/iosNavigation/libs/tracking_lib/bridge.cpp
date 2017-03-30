//
// Created by ivank on 30.06.2016.
//

#include "bridge.h"
#include "navigator.h"
#include "bmath.h"

#if defined(BRIDGE_LIBRARY)
//#   if defined(DEBUG_MODE)
#       include "defines.h"
//#   endif
#endif

void init() {
}

void initTrilatMap() {
    Navigator::instance()->beacon().clear();
    Navigator::instance()->accelerometer().clear();
}

void onNewBeaconCoords(int macHash, double tx_power, double damp, double x, double y, double z) {
#if defined(DEBUG_MODE)
#   if defined(ASTUDIO)
    //setting calibration coefficients for beacons
    switch (macHash)
    {
        case 0: {
            tx_power = -58;
            damp = 3;
            break;
        }

        case 1: {
            tx_power = -62;
            damp = 3.5;
            break;
        }

        case 2:  {
            tx_power = -58;
            damp = 4.5;
            break;
        }

        case 3:  {
            tx_power = -62;
            damp = 4;
            break;
        }

        case 4:  {
            tx_power = -64;
            damp = 3.5;
            break;
        }

        default: {
            tx_power = -64;
            damp = 3.5;
            break;
        }
    }
#   endif
#endif
    Sensors::Hardware::Beacon b((unsigned int)macHash, damp, tx_power);
    Point p;
    p.x = x;
    p.y = y;
    p.z = z;
    b.setPosition(p);
    b.setFilterWinSize(10);
#if defined(DEBUG_MODE)
#   if defined(ASTUDIO)
    b.setUseTxPowerFromMeasurements(false);
#   endif
#endif
    if (Navigator::instance().notNull()) {
        Navigator::instance()->beacon().addBeacon(b);
    } else {
        LOGE("BridgeLOG", "Navigator::instance() is NULL");
    }
}
void releaseTrilatMap() {
}

void onStartNewBeaconSession() {
}

void onNewBeacon( int macHash, double txPower, double rssi, long long timestamp) {
    if (Navigator::instance().notNull()) {
        Navigator::instance()->addBeaconMeasurement((unsigned int)macHash, txPower, rssi, timestamp);
    } else {
        LOGE("BridgeLOG", "Navigator::instance() is NULL");
    }
}

void onEndNewBeaconSession() {

}

double calcDistance(double txPower, double rssi, double damp, int hash) {
    double dist = Navigator::smoothedDistanceToBeacon((unsigned int)hash, 1);
    if (dist < 0) {
        if (damp == 0) {
            damp = Sensors::Hardware::Beacon::DEFAULT_DAMP; // "Magic" default value for damp factor. Used for beacons with unknown damp (they are absent in Navigator)
        }
        dist = BMath::get_distance(rssi, txPower, damp);
    }
    return dist;
}

void onNewAccelerometerData(double ax,double ay, double az, long long timestamp) {
}

int getAccelerometerSamplingPeriod() {
    return 2; // SENSOR_DELAY_UI
}

void onNewGyroscopeData(double rx, double ry, double rz, long long timestamp) {
}

int getGyroscopeSamplingPeriod() {
    return 2; // SENSOR_DELAY_UI
}
void onNewOrientationData(double anglex, double angley, double anglez, long long timestamp) {
}

int getOrientationSamplingPeriod() {
    return 2; // SENSOR_DELAY_UI
}

void onNewGyroscopeUncalibratedData(double rux, double ruy, double ruz, double edx,double edy, double edz,long long timestamp) {
}

int getGyroscopeUncalibratedSamplingPeriod() {
    return 2;
}

void onNewLinearAccelerationSensor(double ax, double ay, double az,long long timestamp) {
    Navigator::instance()->addAccelerometerMeasurement(ax, ay, az, timestamp);
}

int getLinearAccelerationSamplingPeriod() {
    return 2; // SENSOR_DELAY_UI
}

double getTrilatX() {
    return 9;//Navigator::instance()->beacon().lastState().position().x;
}

double getTrilatY() {
    return 7;//Navigator::instance()->beacon().lastState().position().y;
}

double getTrilatZ() {
    return Navigator::instance()->beacon().lastState().position().z;
}

long long getTrilatTimestamp() {
    return Navigator::instance()->beacon().lastState().timestamp();
}

double getX() {
    return Navigator::instance()->lastState().position().x;
}

double getY() {
    return Navigator::instance()->lastState().position().y;
}

double getZ() {
    return Navigator::instance()->lastState().position().z;
}

double getAccelY() {
    return Navigator::instance()->accelerometer().lastState().position().y;
}

double getAccelZ() {
    return Navigator::instance()->accelerometer().lastState().position().z;
}

int getLibraryVersionCode() {
    return 0;
}

int getUiUpdateInterval() {
    return 700;
}

void release() {
    Navigator::instance()->beacon().clear();
    Navigator::instance()->accelerometer().clear();
}

#if defined(DEBUG_MODE)
    void   printLastState(std::ofstream& stream) {
        stream << Navigator::instance()->lastState();
    }

    void   printBeaconLastState(std::ofstream& stream) {
        stream << Navigator::instance()->beacon().lastState();
    }

    void   printAccelerometerLastState(std::ofstream& stream) {
        stream << Navigator::instance()->accelerometer().lastState();
    }

#endif

bool calibrate(int hash, double *rssi_array, double *distance_array, size_t data_count, double *tx_power, double *damp) {
    // can works faster if we will use std::vector instead of std::list as a CalibrationDataContainer
    Sensors::Hardware::Beacon::CalibrationDataContainer calibration_data;
    for (size_t i=0; i<data_count; ++i) {
        Sensors::Hardware::Beacon::CalibrationData data;
        data.distance = *distance_array++;
        data.rssi     = *rssi_array++;
        data.tx_power = 1.0;
        calibration_data.push_back(data);
    }

    bool r = Navigator::instance()->beacon().calibrateBeacon((unsigned int)hash, calibration_data); // Calibrating beacon
    Sensors::Hardware::Beacon b = Navigator::instance()->beacon().beacon((unsigned int)hash);       // To get calibrated values of tx_power and damp
    if (tx_power) {
        *tx_power = b.valid() ? b.txPower() : 1.0;
    }
    if (damp) {
        *damp = b.valid() ? b.damp() : 0.0;
    }
    return r;
}
