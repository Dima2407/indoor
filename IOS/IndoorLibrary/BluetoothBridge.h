//
//  BluetoothBridge.h
//  IndoorLibrary
//
//  Created by AppleFace on 19.03.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#ifndef BluetoothBridge_H
#define BluetoothBridge_H
#include <memory>
#include <stdio.h>
#import "Navigator.h"
#import "MovingAverageFilter.h"
#import "NoFilter.h"



#endif /* BluetoothBridge_hpp */
typedef struct position
{
    double x;
    double y;
    double z;
} position;


//init Navigator
#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_init();

//set position
#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_setPosition();



//init beacon
#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_initBeacon(std::string uuidstr, int major, int minor, double txPower, double damp, double x, double y, double z);
//proces data
#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_proces(double timestamp, std::string uuidStr, int major, int minor, double rssi);
//get position
#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_getLastPosition(double * output);
//create mesh
#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_createMesh(int nx, int ny, double dx, double dy, double x0, double y0);
//set mask
#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_setMaskTable(const std::vector<int> &mTable);
//set destination
#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_setDestination(struct position p );
//realese mesh
#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_realeseMesh();
//read graph
#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_readGraph(std::string graph, double scale );
//get positions
#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_getPositionFromGraph(std::vector<position> &position);
//get distance
#ifdef __cplusplus
extern "C"
#endif
double BluetoothBridge_getDistance();
