#define _USE_MATH_DEFINES

//#define NDEBUG 0

#include <iostream>
#include <cmath>
#include <vector>

#include <jni.h>
#include <string>
#include <android/log.h>
#include <Navigator.h>

#define  LOG_TAG    "ILMNative"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
using namespace std;
using namespace Navigator::Beacons;
using namespace Navigator::Beacons::Factory;
using namespace Navigator::Dijkstra;
using namespace Navigator::Math::Trilat;
using Navigator::Math::Position3D;
using namespace Navigator::Mesh;
using namespace Navigator::Accel;

shared_ptr<StandardBeaconNavigator> navigator;
shared_ptr<StandardAccelNavigator> sensorNavigator;
shared_ptr<PointGraph> pointGraph;
shared_ptr<RectanMesh> mesh;

typedef struct IndoorSdkApi {
    jclass kSpaceBeaconClass;
    jmethodID kSpaceBeaconGetPositionMethod;
    jmethodID kSpaceBeaconGetIdMethod;
    jmethodID kSpaceBeaconGetValuesMethod;

    jclass kMeasurementEventClass;
    jfieldID kMeasurementEventTypeField;
    jfieldID kMeasurementEventTimestampField;
    jfieldID kMeasurementEventDataField;
    jfieldID kMeasurementEventUUIDField;

    jclass kMeasurementTypeEnum;
    jmethodID kMeasurementTypeGetCodeMethod;

    jclass kConfigMapClass;
    jfieldID kMeshConfigNXField;
    jfieldID kMeshConfigNYField;
    jfieldID kMeshConfigDXField;
    jfieldID kMeshConfigDYField;
    jfieldID kMeshConfigX0Field;
    jfieldID kMeshConfigY0Field;
    jfieldID kMaskField;
    jfieldID kMapAngleField;
    jfieldID kUseMaskField;
    jfieldID kUseBeaconsField;
    jfieldID kUseSensorsField;
    jfieldID kInitXField;
    jfieldID kInitYField;
    jfieldID kBeaconsField;
    jmethodID kGetFloatMethod;
    jmethodID kGetIntMethod;
    jmethodID kGetDoubleMethod;
    jmethodID kGetBooleanMethod;
    jmethodID kGetObjectMethod;

} IndoorSdkApi;

typedef struct IndoorSdkConfigs{
    bool useBeacons;
    bool useSensors;
    bool useMask;

    int mapAngle;

    float startX = std::nan("");
    float startY = std::nan("");

    bool sensorsActive;
} IndoorSdkConfigs;

double timeS = 0;

IndoorSdkApi api;
IndoorSdkConfigs configs;

extern "C" {

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_providers_AndroidMeasurementTransfer_nativeDeliver(
        JNIEnv *env, jobject, jobject obj);

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeInit(
        JNIEnv *, jobject, jobject);

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeRelease(
        JNIEnv *, jobject );

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeTakeLastPosition(JNIEnv *, jobject, jfloatArray);

JNIEXPORT jdoubleArray JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_getNativeRoute(JNIEnv *env, jobject instance,
                                                           jdouble x1, jdouble y1, jdouble x2,
                                                           jdouble y2);

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_setGraphArraysFromFile(JNIEnv *env, jobject instance,
                                                                   jstring file_, jdouble scale);
}

//endregion

void prepare_sdk(JNIEnv *env) {
    api.kSpaceBeaconClass = env->FindClass("pro/i_it/indoor/region/SpaceBeacon");
    api.kSpaceBeaconGetPositionMethod = env->GetMethodID(api.kSpaceBeaconClass, "getPosition",
                                                         "()[F");
    api.kSpaceBeaconGetIdMethod = env->GetMethodID(api.kSpaceBeaconClass, "getId",
                                                   "()Ljava/lang/String;");
    api.kSpaceBeaconGetValuesMethod = env->GetMethodID(api.kSpaceBeaconClass, "getValues", "()[F");


    api.kMeasurementEventClass = env->FindClass("pro/i_it/indoor/events/MeasurementEvent");
    api.kMeasurementEventTypeField = env->GetFieldID(api.kMeasurementEventClass, "type",
                                                     "Lpro/i_it/indoor/events/MeasurementType;");
    api.kMeasurementEventTimestampField = env->GetFieldID(api.kMeasurementEventClass, "timestamp",
                                                          "J");
    api.kMeasurementEventDataField = env->GetFieldID(api.kMeasurementEventClass, "data", "[D");
    api.kMeasurementEventUUIDField = env->GetFieldID(api.kMeasurementEventClass, "uuid",
                                                     "Ljava/lang/String;");

    api.kMeasurementTypeEnum = env->FindClass("pro/i_it/indoor/events/MeasurementType");
    api.kMeasurementTypeGetCodeMethod = env->GetMethodID(api.kMeasurementTypeEnum, "getCode",
                                                         "()I");

    api.kConfigMapClass = env->FindClass("pro/i_it/indoor/config/NativeConfigMap");
    api.kGetFloatMethod = env->GetMethodID(api.kConfigMapClass, "getFloat", "(Ljava/lang/String;)F");
    api.kGetIntMethod = env->GetMethodID(api.kConfigMapClass, "getInt", "(Ljava/lang/String;)I");
    api.kGetBooleanMethod = env->GetMethodID(api.kConfigMapClass, "getBoolean", "(Ljava/lang/String;)Z");
    api.kGetDoubleMethod = env->GetMethodID(api.kConfigMapClass, "getDouble", "(Ljava/lang/String;)D");
    api.kGetObjectMethod = env->GetMethodID(api.kConfigMapClass, "getObject", "(Ljava/lang/String;)Ljava/lang/Object;");

    api.kMeshConfigNXField = env->GetStaticFieldID(api.kConfigMapClass, "KEY_MESH_N_X", "Ljava/lang/String;");
    api.kMeshConfigNYField = env->GetStaticFieldID(api.kConfigMapClass, "KEY_MESH_N_Y", "Ljava/lang/String;");
    api.kMeshConfigDXField = env->GetStaticFieldID(api.kConfigMapClass, "KEY_MESH_D_X", "Ljava/lang/String;");
    api.kMeshConfigDYField = env->GetStaticFieldID(api.kConfigMapClass, "KEY_MESH_D_Y", "Ljava/lang/String;");
    api.kMeshConfigX0Field = env->GetStaticFieldID(api.kConfigMapClass, "KEY_MESH_X_0", "Ljava/lang/String;");
    api.kMeshConfigY0Field = env->GetStaticFieldID(api.kConfigMapClass, "KEY_MESH_Y_0", "Ljava/lang/String;");
    api.kMaskField = env->GetStaticFieldID(api.kConfigMapClass, "KEY_MASK", "Ljava/lang/String;");
    api.kMapAngleField = env->GetStaticFieldID(api.kConfigMapClass, "KEY_MAP_ANGLE", "Ljava/lang/String;");
    api.kUseMaskField = env->GetStaticFieldID(api.kConfigMapClass, "KEY_USE_MASK", "Ljava/lang/String;");
    api.kUseBeaconsField = env->GetStaticFieldID(api.kConfigMapClass, "KEY_USE_BEACONS", "Ljava/lang/String;");
    api.kUseSensorsField = env->GetStaticFieldID(api.kConfigMapClass, "KEY_USE_SENSORS", "Ljava/lang/String;");
    api.kInitXField = env->GetStaticFieldID(api.kConfigMapClass, "KEY_INIT_X", "Ljava/lang/String;");
    api.kInitYField = env->GetStaticFieldID(api.kConfigMapClass, "KEY_INIT_Y", "Ljava/lang/String;");
    api.kBeaconsField = env->GetStaticFieldID(api.kConfigMapClass, "KEY_BEACONS", "Ljava/lang/String;");
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_providers_AndroidMeasurementTransfer_nativeDeliver(
        JNIEnv *env, jobject, jobject obj) {
    jobject typeObj = env->GetObjectField(obj, api.kMeasurementEventTypeField);
    jlong timeStamp = env->GetLongField(obj, api.kMeasurementEventTimestampField);
    jdoubleArray dataArray = (jdoubleArray) env->GetObjectField(obj,
                                                                api.kMeasurementEventDataField);
    double *data = env->GetDoubleArrayElements(dataArray, NULL);

    jint eventTypeCode = env->CallIntMethod(typeObj, api.kMeasurementTypeGetCodeMethod);
    double eventTime = (1.0 * ((timeStamp - timeS) / 1000));
    if (eventTypeCode == 2 && configs.useBeacons) {
        jstring uuidString = (jstring) env->GetObjectField(obj, api.kMeasurementEventUUIDField);

        const char *uuid = env->GetStringUTFChars(uuidString, 0);

        BeaconUID uid(uuid, (int) data[0], (int) data[1]);

        LOGD("beacon %s, major ( %d ), minor ( %d ), rssi ( %f ), tx ( %f ) ", uuid, (int) data[0],
             (int) data[1], data[3], data[2]);

        BeaconReceivedData brd(eventTime, uid, data[3], data[2]);
        Position3D outPos = navigator->process(brd);
        LOGD("position from beacons ( %f , %f , %f )", outPos.x, outPos.y, outPos.z);
        env->ReleaseStringUTFChars(uuidString, uuid);
    } else if (eventTypeCode == 1 && configs.useSensors && configs.sensorsActive) {
        double ax = data[0];
        double ay = data[1];
        double az = data[2];
        double azimut = data[3];
        double pitch = data[4];
        double roll = data[5];
        azimut = azimut - configs.mapAngle;
        if(azimut > 180){
            azimut = - 360 + azimut;
        }else if(azimut < -180){
            azimut = 360 + azimut;
        }
        LOGD("sensor ax ( %f ), ay ( %f ), az ( %f ), azimut ( %f ) , pitch ( %f ) , roll ( %f ) ",
             ax, ay, az, azimut, pitch, roll);

        AccelReceivedData ard{
                .timestamp = eventTime,
                .ax = ax,
                .ay = ay,
                .az = az,
                .pitch = pitch,
                .roll = roll,
                .yaw = azimut};
            Position3D outPos = sensorNavigator->process(ard);
            LOGD("position from sensors (%f,%f,%f)", outPos.x, outPos.y, outPos.z);
    }
    env->ReleaseDoubleArrayElements(dataArray, data, 0);
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeInit(
        JNIEnv *env, jobject instance, jobject config) {
        LOGD("IndoorLocationManager_nativeInit");
    prepare_sdk(env);

    configs = {};
    jstring keyUseBeacons = (jstring)env->GetStaticObjectField(api.kConfigMapClass, api.kUseBeaconsField);
    configs.useBeacons = env->CallBooleanMethod(config, api.kGetBooleanMethod, keyUseBeacons);

    jstring keyUseSensors = (jstring)env->GetStaticObjectField(api.kConfigMapClass, api.kUseSensorsField);
    configs.useSensors = env->CallBooleanMethod(config, api.kGetBooleanMethod, keyUseSensors);

    jstring keyUseMask = (jstring)env->GetStaticObjectField(api.kConfigMapClass, api.kUseMaskField);
    configs.useMask = env->CallBooleanMethod(config, api.kGetBooleanMethod, keyUseMask);

    jstring keyMapAngle = (jstring)env->GetStaticObjectField(api.kConfigMapClass, api.kMapAngleField);
    configs.mapAngle = env->CallIntMethod(config, api.kGetIntMethod, keyMapAngle);

    jstring keyStartX = (jstring)env->GetStaticObjectField(api.kConfigMapClass, api.kInitXField);
    configs.startX = env->CallFloatMethod(config, api.kGetFloatMethod, keyStartX);

    jstring keyStartY = (jstring)env->GetStaticObjectField(api.kConfigMapClass, api.kInitYField);
    configs.startY = env->CallFloatMethod(config, api.kGetFloatMethod, keyStartY);

    if(configs.useMask){
        jstring keyMaskArray = (jstring)env->GetStaticObjectField(api.kConfigMapClass, api.kMaskField);
        jintArray maskArray = (jintArray)env->CallObjectMethod(config, api.kGetObjectMethod, keyMaskArray);
        const jsize length = env->GetArrayLength(maskArray);
        jint *mask = env->GetIntArrayElements(maskArray, 0);

        vector<int> table(length);
        memcpy(&table[0], mask, length * sizeof(int));

        env->ReleaseIntArrayElements(maskArray, mask, 0);

        jstring keyNX = (jstring)env->GetStaticObjectField(api.kConfigMapClass, api.kMeshConfigNXField);
        const double nx = env->CallDoubleMethod(config, api.kGetDoubleMethod, keyNX);
        jstring keyNY = (jstring)env->GetStaticObjectField(api.kConfigMapClass, api.kMeshConfigNYField);
        const double ny = env->CallDoubleMethod(config, api.kGetDoubleMethod, keyNY);
        jstring keyDX = (jstring)env->GetStaticObjectField(api.kConfigMapClass, api.kMeshConfigDXField);
        const double dx = env->CallDoubleMethod(config, api.kGetDoubleMethod, keyDX);
        jstring keyDY = (jstring)env->GetStaticObjectField(api.kConfigMapClass, api.kMeshConfigDYField);
        const double dy = env->CallDoubleMethod(config, api.kGetDoubleMethod, keyDY);
        jstring keyX0 = (jstring)env->GetStaticObjectField(api.kConfigMapClass, api.kMeshConfigX0Field);
        const double x0 = env->CallDoubleMethod(config, api.kGetDoubleMethod, keyX0);
        jstring keyY0 = (jstring)env->GetStaticObjectField(api.kConfigMapClass, api.kMeshConfigY0Field);
        const double y0 = env->CallDoubleMethod(config, api.kGetDoubleMethod, keyY0);

        mesh = make_shared<RectanMesh>(nx, ny, dx, dy, x0, y0);

        mesh->setMaskTable(table);
    }
    if(configs.useBeacons){
        navigator = make_shared<StandardBeaconNavigator>(mesh, false);

        jstring keyBeacons = (jstring)env->GetStaticObjectField(api.kConfigMapClass, api.kBeaconsField);
        jobjectArray beacons = (jobjectArray)env->CallObjectMethod(config, api.kGetObjectMethod, keyBeacons);

        jint size = env->GetArrayLength(beacons);

        for (int i = 0; i < size; i++) {
            jobject beacon = env->GetObjectArrayElement(beacons, i);
            jfloatArray position = (jfloatArray) env->CallObjectMethod(beacon, api.kSpaceBeaconGetPositionMethod);
            jstring id = (jstring) env->CallObjectMethod(beacon, api.kSpaceBeaconGetIdMethod);
            jfloatArray values = (jfloatArray) env->CallObjectMethod(beacon, api.kSpaceBeaconGetValuesMethod);

            jfloat *elements = env->GetFloatArrayElements(values, 0);
            jfloat *elementsPos = env->GetFloatArrayElements(position, 0);
            const char *uuid = env->GetStringUTFChars(id, 0);

            BeaconUID uid(uuid, (int) elements[0], (int) elements[1]);
            navigator->addBeacon(Beacon(uid, elements[2], elements[3],
                                        Position3D(elementsPos[0], elementsPos[1], elementsPos[2]),
                                        ""));

            env->ReleaseFloatArrayElements(values, elements, 0);
            env->ReleaseStringUTFChars(id, uuid);
        }
    }
    LOGD("IndoorLocationManager_nativeInit -");
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeRelease(
        JNIEnv *env, jobject instance) {
    LOGD("IndoorLocationManager_nativeRelease");
    LOGD("IndoorLocationManager_nativeRelease -");
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeTakeLastPosition(JNIEnv *env, jobject instance,
                                                                   jfloatArray positionArray) {
    LOGD("IndoorLocationManager_nativeTakeLastPosition");

    Position3D outPos(configs.startX, configs.startY, 0.0f);

    if(configs.useBeacons){
        if(!navigator->isInitFinished()){
            return;
        }
        outPos = navigator->getLastPosition();
    }

    if(std::isnan(outPos.x) || std::isnan(outPos.y)){
        return;
    }

    if (configs.useSensors && !configs.sensorsActive) {
        AccelConfig config;
        config.mapOrientationAngle = configs.mapAngle;
        config.useFilter = false;
        LOGD("init position  at (%f %f)", outPos.x, outPos.y);

        double startX = outPos.x, startY = outPos.y;

        sensorNavigator = make_shared<StandardAccelNavigator>(mesh, startX, startY, config);
        configs.sensorsActive = true;
    }

    if (configs.useSensors) {
        outPos = sensorNavigator->getLastPositon();
    }

    LOGD("last position (%f,%f,%f)", outPos.x, outPos.y, outPos.z);

    float *data = env->GetFloatArrayElements(positionArray, NULL);
    data[0] = (float) outPos.x;
    data[1] = (float) outPos.y;
    data[2] = (float) outPos.z;

    env->ReleaseFloatArrayElements(positionArray, data, 0);
    LOGD("IndoorLocationManager_nativeTakeLastPosition -");

}

JNIEXPORT jdoubleArray JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_getNativeRoute(JNIEnv *env, jobject instance,
                                                           jdouble x1, jdouble y1, jdouble x2,
                                                           jdouble y2) {

    LOGD("IndoorLocationManager_getNativeRoute");

    Position3D pos1(x1, y1, 0.0);
    Position3D pos2(x2, y2, 0.0);
    int startNode = pointGraph->findNearestVertex(pos1);
    int endNode = pointGraph->findNearestVertex(pos2);
    vector<Position3D> route;
    double distance = pointGraph->dijkstraP(startNode, endNode, route);
    jdoubleArray output = env->NewDoubleArray(route.size() * 2 + 1);  // first element = distance
    jdouble *destArrayElems = env->GetDoubleArrayElements(output, NULL);
    destArrayElems[0] = distance;
    int j = 1;
    for (int i = 0; i < route.size(); i++) {
        destArrayElems[j++] = route[i].x;
        destArrayElems[j++] = route[i].y;
    }

    env->ReleaseDoubleArrayElements(output, destArrayElems, NULL);
    LOGD("IndoorLocationManager_getNativeRoute - ");

    return output;
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_setGraphArraysFromFile(JNIEnv *env, jobject instance,
                                                                   jstring file_, jdouble scale) {
    LOGD("IndoorLocationManager_setGraphArraysFromFile");
    const char *file = env->GetStringUTFChars(file_, 0);

    std::string data(file);

    pointGraph = make_shared<PointGraph>(data, scale);

    env->ReleaseStringUTFChars(file_, file);
    LOGD("IndoorLocationManager_setGraphArraysFromFile -");
}