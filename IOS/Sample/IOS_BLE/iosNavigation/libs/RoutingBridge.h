#ifndef INDORNAVIIGATION_ROUTINGBRIDGE_H
#define INDORNAVIIGATION_ROUTINGBRIDGE_H

//#include <jni.h>
//#include <android/log.h>
#include "RoutingBridge.h"

#ifdef __cplusplus
extern "C"
#endif
void RoutingBridge_init(char *path, double pixelSize);

#ifdef __cplusplus
extern "C"
#endif
bool RoutingBridge_hasRoute();

#ifdef __cplusplus
extern "C"
#endif
double* RoutingBridge_getRoute();

#ifdef __cplusplus
extern "C"
#endif
void RoutingBridge_setDestinationPoint(int x, int y);
#endif //INDORNAVIIGATION_ROUTINGBRIDGE_H
