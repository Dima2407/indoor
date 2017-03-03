//
// Created by ivank on 30.06.2016.
//

/** \file bridge.h
 * \brief The bridge between JNI and trackin_lib
 *
 * Note: This is not really a part of tracking_lib, since this file cannot be compiled
 * outside of Android environment, at least not without modifications
 *
 * At present it seems that only beacons work somehow, other sensors are disabled or not suppported.
 */

#ifndef INDORNAVIGATION_BRIDGE_H
#define INDORNAVIGATION_BRIDGE_H
#include "bridge_global.h"

#if defined(DEBUG_MODE)
#  include "common_types.h"
#endif

extern "C" {
    /// Init sensors::NativeSensorManager
    BRIDGE_LIBRARY_EXPORT void init();
    /// Clear all beacon and accelerator measurements in Navigator
    BRIDGE_LIBRARY_EXPORT void initTrilatMap();
    /** \brief Add a new beacon to Navigator
     *
     * Warning! Sets some dummy damp and txPower !
     */
    BRIDGE_LIBRARY_EXPORT void onNewBeaconCoords(int macHash, double tx_power, double damp, double x, double y, double z = 0);
    /// Does nothing
    BRIDGE_LIBRARY_EXPORT void releaseTrilatMap();

    /// Does nothing
    BRIDGE_LIBRARY_EXPORT void onStartNewBeaconSession();
    /// Add new beacon measurement to Navigator
    BRIDGE_LIBRARY_EXPORT void onNewBeacon(int macHash, double txPower, double rssi, long long timestamp);
    /// Does nothing
    BRIDGE_LIBRARY_EXPORT void onEndNewBeaconSession();

    /// Get either smoothed or raw distance to a beacon
    BRIDGE_LIBRARY_EXPORT double calcDistance(double txPower, double rssi, double damp, int hash);
    /// Calibrate a beacon
    BRIDGE_LIBRARY_EXPORT bool   calibrate(int hash, double* rssi_array, double* distance_array, size_t data_count, double *tx_power, double *damp);

    BRIDGE_LIBRARY_EXPORT void onNewAccelerometerData(double ax, double ay, double az, long long timestamp);
    BRIDGE_LIBRARY_EXPORT int  getAccelerometerSamplingPeriod();

    BRIDGE_LIBRARY_EXPORT void onNewGyroscopeData(double rx, double ry, double rz, long long timestamp);
    BRIDGE_LIBRARY_EXPORT int  getGyroscopeSamplingPeriod();

    BRIDGE_LIBRARY_EXPORT void onNewOrientationData(double anglex, double angley, double anglez, long long timestamp);
    BRIDGE_LIBRARY_EXPORT int  getOrientationSamplingPeriod();

    BRIDGE_LIBRARY_EXPORT void onNewGyroscopeUncalibratedData(double rux, double ruy, double ruz,
                                                              double edx, double edy, double edz,
                                                              long long timestamp);
    BRIDGE_LIBRARY_EXPORT int  getGyroscopeUncalibratedSamplingPeriod();

    BRIDGE_LIBRARY_EXPORT void onNewLinearAccelerationSensor(double ax, double ay, double az, long long timestamp);
    BRIDGE_LIBRARY_EXPORT int  getLinearAccelerationSamplingPeriod();

    /// Get device position from beacons only
    BRIDGE_LIBRARY_EXPORT double getTrilatX();
    BRIDGE_LIBRARY_EXPORT double getTrilatY();
    BRIDGE_LIBRARY_EXPORT double getTrilatZ();
    BRIDGE_LIBRARY_EXPORT long long   getTrilatTimestamp();

    BRIDGE_LIBRARY_EXPORT double getAccelX();
    BRIDGE_LIBRARY_EXPORT double getAccelY();
    BRIDGE_LIBRARY_EXPORT double getAccelZ();

//    BRIDGE_LIBRARY_EXPORT double getTrilatZ();
//    BRIDGE_LIBRARY_EXPORT long long   getTrilatTimestamp();

//    BRIDGE_LIBRARY_EXPORT double getAccelX();
//    BRIDGE_LIBRARY_EXPORT double getAccelY();
//    BRIDGE_LIBRARY_EXPORT double getAccelZ();

    ///  Get device position from all sensors
    BRIDGE_LIBRARY_EXPORT double getX();
    BRIDGE_LIBRARY_EXPORT double getY();
//    BRIDGE_LIBRARY_EXPORT double getZ();

    /// Returns 0
    BRIDGE_LIBRARY_EXPORT int    getLibraryVersionCode();
    /// Returns 700
    BRIDGE_LIBRARY_EXPORT int    getUiUpdateInterval();
    /// Clear all beacon and accelerator measurements in Navigator
    BRIDGE_LIBRARY_EXPORT void   release();
    /// Unregister sensors::NativeSensorManager callbacks
BRIDGE_LIBRARY_EXPORT void unregisterSensorCallbacks();

#if defined(DEBUG_MODE)
    BRIDGE_LIBRARY_EXPORT void   printLastState(std::ofstream& stream);
    BRIDGE_LIBRARY_EXPORT void   printBeaconLastState(std::ofstream& stream);
    BRIDGE_LIBRARY_EXPORT void   printAccelerometerLastState(std::ofstream& stream);
#endif
}


#endif //INDORNAVIGATION_BRIDGE_H
