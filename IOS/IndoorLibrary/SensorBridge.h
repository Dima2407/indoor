//
//  SensorBridge.h
//  IndoorLibrary
//
//  Created by Lina Pischenko on 03.07.17.
//  Copyright © 2017 PischenkoL. All rights reserved.
//

#include <memory>
#include <stdio.h>
#import "Navigator.h"
#import "MovingAverageFilter.h"
#import "NoFilter.h"


struct position
{
    double x;
    double y;
    double z;
};


//init Navigator
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_init(double startX, double startY);

#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_process(double timestamp ,double ax, double ay, double az, double pitch, double yaw, double roll);
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_getLastPosition(double * output);
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_createMesh(double nx, double ny, double dx, double dy, double x0, double y0);

#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_setMaskTable(const std::vector<int> &mTable);
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_setAccelConfig(int orientationAngle, bool useFilter, bool useMapEdges,bool useWalls,bool useMeshMask);
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_readGraph(std::string graph, double scale );
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_getPositionFromGraph(std::vector<position> &way);
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_setDestination(struct position p );
#ifdef __cplusplus
extern "C"
#endif
void SensorBridge_stop();
