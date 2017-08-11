//
//  KalmanBridge.hpp
//  IndoorLibrary
//
//  Created by Lina Pischenko on 09.08.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#ifndef KalmanBridge_hpp
#define KalmanBridge_hpp

#include <stdio.h>
#include <memory>
#include <stdio.h>
#import "Navigator.h"
#import "MovingAverageFilter.h"
#import "NoFilter.h"

#endif /* KalmanBridge_hpp */
typedef struct kalmanPosition
{
    double x;
    double y;
    double z;
} kalmanPosition;


//init Navigator
#ifdef __cplusplus
extern "C"
#endif
void KalmanBridge_init();

//init beacon
#ifdef __cplusplus
extern "C"
#endif
void KalmanBridge_initBeacon(std::string uuidstr, int major, int minor, double txPower, double damp, double x, double y, double z);
//proces data
#ifdef __cplusplus
extern "C"
#endif
void KalmanBridge_process( const std::vector<Navigator::Beacons::BeaconReceivedData> beacons);
//get position
#ifdef __cplusplus
extern "C"
#endif
void KalmanBridge_getLastPosition(double * output);
//create mesh
#ifdef __cplusplus
extern "C"
#endif
void KalmanBridge_createMesh(int nx, int ny, double dx, double dy, double x0, double y0);
//set mask
#ifdef __cplusplus
extern "C"
#endif
void KalmanBridge_setMaskTable(const std::vector<int> &mTable);
//set destination
#ifdef __cplusplus
extern "C"
#endif
void KalmanBridge_setDestination(kalmanPosition p);
//realese mesh
#ifdef __cplusplus
extern "C"
#endif
void KalmanBridge_realeseMesh();
//read graph
#ifdef __cplusplus
extern "C"
#endif
void KalmanBridge_readGraph(std::string graph, double scale );
//get positions
#ifdef __cplusplus
extern "C"
#endif
void KalmanBridge_getPositionFromGraph(std::vector<kalmanPosition> &pos);
//get distance
#ifdef __cplusplus
extern "C"
#endif
double KalmanBridge_getDistance();
//return flag is  initialise
#ifdef __cplusplus
extern "C"
#endif
bool KalmanBridge_isInitialise();
//get initialise position
#ifdef __cplusplus
extern "C"
#endif
void KalmanBridge_getInitialisePosition(double * output);

#ifdef __cplusplus
extern "C"
#endif
void KalmanBridge_setConfig(bool useInit, bool use3DTrilat, bool useMapEdges, bool useMeshMask);
#ifdef __cplusplus
extern "C"
#endif
void KalmanBridge_stop();
