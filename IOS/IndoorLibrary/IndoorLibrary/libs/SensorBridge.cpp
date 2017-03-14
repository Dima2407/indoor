//
// Created by ivank on 27.06.2016.
//

#include "SensorBridge.h"
#include "stdio.h"

extern "C" bool
SensorBridge_calibrate(int hash,
                                                    double * rssi, double * distance,
                                                    int n, double * txPower,
                                                    double * damp) {
    bool result = calibrate(hash, rssi, distance, (size_t) n, txPower, damp);

    return result;
}

extern "C"
void SensorBridge_init() {
    printf("SensorBridge_init()\n");
    init();
}

extern "C"
void SensorBridge_initTrilatMap() {
    printf("SensorBridge_initTrilatMap()\n");
    initTrilatMap();
}

extern "C"
void SensorBridge_onNewBeaconCoords(
                                                                 int macHash, double damp, double x,
                                                                 double y) {
    onNewBeaconCoords(macHash, 0, damp, x, y, 0);
}

extern "C"
void SensorBridge_releaseTrilatMap() {
    releaseTrilatMap();
}

extern "C"
void SensorBridge_onStartNewBeaconSession() {
    onStartNewBeaconSession();
}

extern "C"
void SensorBridge_onNewBeacon(int macHash,
                                                           double txPower, double rssi,
                                                           long long timestamp) {
//    printf("SensorBridge_onNewBeacon(%d, %f, %f, %llu)\n", macHash, txPower, rssi, timestamp);
    onNewBeacon(macHash, txPower, rssi, timestamp);
}

extern "C"
void SensorBridge_onEndNewBeaconSession() {
    onEndNewBeaconSession();
}

extern "C"
double SensorBridge_calcDistance(
                                                              double txPower, double rssi,
                                                              double damp, int hash) {
    return calcDistance(txPower, rssi, damp, hash);
}

extern "C"
void SensorBridge_onNewAccelerometerData(
                                                                      double gx, double gy,
                                                                      double gz,
                                                                      long long timestamp) {
    onNewAccelerometerData(gx, gy, gz, timestamp);
}

extern "C"
int SensorBridge_getAccelerometerSamplingPeriod() {
    return getAccelerometerSamplingPeriod();
}

extern "C"
void SensorBridge_onNewGyroscopeData(
                                                                  double rx, double ry, double rz,
                                                                  long long timestamp) {
    onNewGyroscopeData(rx, ry, rz, timestamp);
}

extern "C"
int SensorBridge_getGyroscopeSamplingPeriod() {
    return getGyroscopeSamplingPeriod();
}

extern "C"
void SensorBridge_onNewOrientationData(
                                                                    double anglex, double angley,
                                                                    double anglez,
                                                                    long long timestamp) {
    onNewOrientationData(anglex, angley, anglez, timestamp);
}

extern "C"
int SensorBridge_getOrientationSamplingPeriod() {
    return getOrientationSamplingPeriod();
}

extern "C"
void SensorBridge_onNewGyroscopeUncalibratedData(
                                                                              double rux,
                                                                              double ruy,
                                                                              double ruz,
                                                                              double edx,
                                                                              double edy,
                                                                              double edz,
                                                                              long long timestamp) {
    onNewGyroscopeUncalibratedData(rux, ruy, ruz, edx, edy, edz, timestamp);
}

extern "C"
int SensorBridge_getyroscopeUncalibratedSamplingPeriod() {
    return getGyroscopeUncalibratedSamplingPeriod();
}

extern "C"
void SensorBridge_onNewLinearAccelerationSensor(
                                                                             double ax, double ay,
                                                                             double az,
                                                                             long long timestamp) {
    onNewLinearAccelerationSensor(ax, ay, az, timestamp);
}

extern "C"
int SensorBridge_getLinearAccelerationSamplingPeriod() {
    return getLinearAccelerationSamplingPeriod();
}

extern "C"
double SensorBridge_getTrilatX() {
    return getTrilatX();
}

extern "C"
double SensorBridge_getTrilatY() {
    return getTrilatY();
}

extern "C"
double SensorBridge_getX() {
    return getX();
}

extern "C"
double SensorBridge_getY() {
    return getY();
}

extern "C"
int SensorBridge_getLibraryVersionCode() {
    return getLibraryVersionCode();
}

extern "C"
int SensorBridge_getUiUpdateInterval() {
    return getUiUpdateInterval();
}

extern "C" void SensorBridge_release() {
    release();
}
