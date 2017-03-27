//
// Created by ivank on 30.06.2016.
//

#ifndef INDORNAVIGATION_BRIDGE_H
#define INDORNAVIGATION_BRIDGE_H
#include "bridge_global.h"

#if defined(DEBUG_MODE)
#  include "common_types.h"
#endif

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif
    BRIDGE_LIBRARY_EXPORT void init();
    BRIDGE_LIBRARY_EXPORT void initTrilatMap();
    BRIDGE_LIBRARY_EXPORT void onNewBeaconCoords(int macHash, double tx_power, double damp, double x, double y, double z);
    BRIDGE_LIBRARY_EXPORT void releaseTrilatMap();

    BRIDGE_LIBRARY_EXPORT void onStartNewBeaconSession();
    BRIDGE_LIBRARY_EXPORT void onNewBeacon(int macHash, double txPower, double rssi, long long timestamp);
    BRIDGE_LIBRARY_EXPORT void onEndNewBeaconSession();

    BRIDGE_LIBRARY_EXPORT double calcDistance(double txPower, double rssi, double damp, int hash);
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

    BRIDGE_LIBRARY_EXPORT double getX();
    BRIDGE_LIBRARY_EXPORT double getY();
//    BRIDGE_LIBRARY_EXPORT double getZ();

    BRIDGE_LIBRARY_EXPORT int    getLibraryVersionCode();
    BRIDGE_LIBRARY_EXPORT int    getUiUpdateInterval();
    BRIDGE_LIBRARY_EXPORT void   release();

#if defined(DEBUG_MODE)
    BRIDGE_LIBRARY_EXPORT void   printLastState(std::ofstream& stream);
    BRIDGE_LIBRARY_EXPORT void   printBeaconLastState(std::ofstream& stream);
    BRIDGE_LIBRARY_EXPORT void   printAccelerometerLastState(std::ofstream& stream);
#endif
#ifdef __cplusplus
}
#endif


#endif //INDORNAVIGATION_BRIDGE_H
