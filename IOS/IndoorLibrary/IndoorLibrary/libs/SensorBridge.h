#ifndef BEACONDETECTOR_SENSORBRIDGE_H
#define BEACONDETECTOR_SENSORBRIDGE_H

//#include <jni.h>
//#include <android/log.h>
#include "tracking_lib/bridge.h"


//первая инициализация
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_init();

//начало добавления кординат биконов
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_initTrilatMap();
//новая коондината
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_onNewBeaconCoords(
                                                                            int macHash,
                                                                            double damp, double x,
                                                                            double y);
//освобождение карты
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_releaseTrilatMap();

//перед поступлением новой пачки биконов
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_onStartNewBeaconSession();
//сюда призодят биконы (этот метод вызовется несколько раз подряд, зависит от колличества биконов)
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_onNewBeacon(
                                                                      int macHash, double txPower,
                                                                      double rssi,
                                                                      long long timestamp);
// конет поступления данных о биконах
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_onEndNewBeaconSession();

#ifdef __cplusplus
extern "C"
#endif
double SensorBridge_calcDistance(
                                                                         double txPower,
                                                                         double rssi, double damp,
                                                                         int hash);
//SAMPLING PERIODS
/** get sensor data as fast as possible */
//SENSOR_DELAY_FASTEST = 0;
/** rate suitable for games */
//SENSOR_DELAY_GAME = 1;
/** rate suitable for the user interface  */
//SENSOR_DELAY_UI = 2;
/** rate (default) suitable for screen orientation changes */
//SENSOR_DELAY_NORMAL = 3;



// gz/gy/gz -   Acceleration force along the x/y/z axis (including gravity).   m/s2
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_onNewAccelerometerData(
                                                                                 double gx,
                                                                                 double gy,
                                                                                 double gz,
                                                                                 long long
                                                                                 timestamp);
#ifdef __cplusplus
extern "C"
#endif
int SensorBridge_getAccelerometerSamplingPeriod();

//rx/ry/rz - Rate of rotation around the x axis. rad/s
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_onNewGyroscopeData(
                                                                             double rx, double ry,
                                                                             double rz, long long
                                                                             timestamp);
#ifdef __cplusplus
extern "C"
#endif
int SensorBridge_getGyroscopeSamplingPeriod();

//rx/ry/rz - Rate of rotation around the x axis. rad/s
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_onNewOrientationData(
                                                                               double anglex,
                                                                               double angley, double
                                                                               anglez,
                                                                               long long timestamp);
#ifdef __cplusplus
extern "C"
#endif
int SensorBridge_getOrientationSamplingPeriod();

//rux/ruy/ruz - Rate of rotation (without drift compensation) around the x/y/z axis. rad/s
//edx/exy/edz - Estimated drift around the x axis. x/y/z axis. rad/s
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_onNewGyroscopeUncalibratedData(double rux, double ruy,
        double ruz, double edx, double edy, double edz, long long timestamp);
#ifdef __cplusplus
extern "C"
#endif
int SensorBridge_getGyroscopeUncalibratedSamplingPeriod();

//ax/ay/az - Acceleration force along the x/y/z axis (excluding gravity). m/s2
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_onNewLinearAccelerationSensor(
                                                                                        double ax,
                                                                                        double ay,
                                                                                        double az,
                                                                                        long long timestamp);
#ifdef __cplusplus
extern "C"
#endif
int SensorBridge_getLinearAccelerationSamplingPeriod();

//подучение данных трилатерации
#ifdef __cplusplus
extern "C"
#endif
double SensorBridge_getTrilatX();
#ifdef __cplusplus
extern "C"
#endif
double SensorBridge_getTrilatY();

// получение конечных координат
#ifdef __cplusplus
extern "C"
#endif
double SensorBridge_getX();
#ifdef __cplusplus
extern "C"
#endif
double SensorBridge_getY();

// версия библтотеки
#ifdef __cplusplus
extern "C"
#endif
int SensorBridge_getLibraryVersionCode();

//интервал обновлени UI
#ifdef __cplusplus
extern "C"
#endif
int SensorBridge_getUiUpdateInterval();

#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_release();
#ifdef __cplusplus
extern "C"
#endif
bool SensorBridge_calibrate(
                                                                    int hash,
                                                                    double* rssi,
                                                                    double* distance,
                                                                    int n, double* txPower,
                                                                    double* damp);

#endif //BEACONDETECTOR_SENSORBRIDGE_H
