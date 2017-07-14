//
//  SensorBridge.h
//  IndoorLibrary
//
//  Created by Lina Pischenko on 03.07.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//


#ifndef BluetoothBridge_H
#define BluetoothBridge_H
#include <memory>
#include <stdio.h>
#import "Navigator.h"
#import "MovingAverageFilter.h"
#import "NoFilter.h"

#endif /* SensorBridge_hpp */
//init Navigator
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_init(double startX, double startY);

#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_proces(double timestamp ,double ax, double ay, double az, double pitch, double yaw, double roll);
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_getLastPosition(double * output);
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_createMesh(int nx, int ny, double dx, double dy, double x0, double y0);

#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_setMaskTable(const std::vector<int> &mTable);
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_setAccelConfig(int orientationAngle, bool useFilter);
