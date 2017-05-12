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


//init
#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_init();

//set position
#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_setPosition();

//make string

//init beacon
#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_initBeacon(std::string uuidstr, int major, int minor, double txPower, double damp, double x, double y, double z);

#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_proces(double timestamp, std::string uuidStr, int major, int minor, double rssi);

#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_getLastPosition(double * output);

#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_createMesh(int nx, int ny, double dx, double dy, double x0, double y0);

#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_setMaskTable(const std::vector<int> &mTable);
#ifdef __cplusplus
extern "C"
#endif
void BluetoothBridge_releseMesh();
