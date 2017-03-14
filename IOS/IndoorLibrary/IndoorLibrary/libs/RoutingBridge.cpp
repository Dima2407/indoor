//
// Created by Alexander on 20.07.2016.
//

#include "SensorBridge.h"
#include <stdio.h>
#include <string.h>

int dx, dy;

extern "C" void RoutingBridge_init(char *path, double pixelSize) {
    //const char *str = env->GetStringUTFChars(path, 0);
    printf("RoutingBridge_init(%s, %f)\n", path, pixelSize);
    //__android_log_write(ANDROID_LOG_VERBOSE, "JNI", str);
    //env->ReleaseStringUTFChars(path, str);
}

extern "C" bool RoutingBridge_hasRoute() {
    return 1;
}

extern "C" double* RoutingBridge_getRoute() {

    double *result = new double[256];

    //jdoubleArray result;
    //int routLenght = 256;
    //result = env->NewDoubleArray(routLenght);
    //if (result == NULL) {
    //    return NULL; /* out of memory error thrown */
    //}
    //int i;
    // fill a temp structure to use to populate the java int array
    double fill[256] = { 349.0, 533.0, 351.0, 295.0, 389.0, 755.0,
                447.0, 533.0, 451.0, 295.0, 479.0, 755.0, 545.0, 297.0, 545.0, 535.0, 549.0,
                411.0, 549.0, 607.0, 577.0, 755.0, 581.0, 841.0, 581.0, 909.0, 599.0, 675.0,
                645.0, 751.0, 697.0, 821.0, 699.0, 611.0, 769.0, 605.0, 771.0, 355.0, 773.0,
                473.0, 783.0, 823.0, 869.0, 823.0, 891.0, 605.0, 895.0, 353.0, 947.0, 823.0,
                1025.0, 353.0, 1025.0, 473.0, 1025.0, 607.0, 1141.0, 607.0, 1251.0, 609.0,
                1253.0, 681.0, 1253.0, 767.0, 1255.0, 851.0, 1327.0, 425.0, 1327.0, 529.0,
                1331.0, 607.0, 1367.0, 851.0, 1499.0, 851.0 };
    //for (i = 0; i < routLenght; i++) {
    //    fill[i] = 0;
                //i%2==0?dx+i:dy+i; // put whatever logic you want to populate the values here.
    //}
    // move from the temp structure to the java structure

    //env->SetDoubleArrayRegion(result, 0, routLenght, fill);
    memcpy(result, fill, 256*sizeof(double));
    return result;
}

#include "RoutingBridge.h"

extern "C" void RoutingBridge_setDestinationPoint(int x, int y) {
    dx = x;
    dy = y;
}
