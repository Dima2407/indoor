#define _USE_MATH_DEFINES
//#define NDEBUG

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

AbstractBeaconNavigator *navigator;
StandardAccelNavigator *sensorNavigator;
PointGraph *pointGraph;
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

    jclass kMeshConfigClass;
    jfieldID kMeshConfigNXField;
    jfieldID kMeshConfigNYField;
    jfieldID kMeshConfigDXField;
    jfieldID kMeshConfigDYField;
    jfieldID kMeshConfigX0Field;
    jfieldID kMeshConfigY0Field;

} IndoorSdkApi;

double timeS = 0;

enum Mode {
    TRILATERATION_BEACON_NAVIGATOR = 0,
    STANDARD_BEACON_NAVIGATOR = 1,
    SENSOR_BEACON_NAVIGATOR = 2
};

vector<int> mGraphs(2000);
vector<double> mEdges(2000);

IndoorSdkApi api;
Mode currentMode;

extern "C" {

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_providers_AndroidMeasurementTransfer_deliver(
        JNIEnv *env, jobject, jobject obj);

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeInit(
        JNIEnv *, jobject, jint, jintArray, jobject);

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeRelease(
        JNIEnv *env, jobject instance);

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeSetBeacons(
        JNIEnv *env, jobject instance, jobjectArray beacons);

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeTakeLastPosition(JNIEnv *, jobject , jfloatArray);

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_setNativeGraphArray(JNIEnv *env, jobject instance,
                                                                jintArray graphs_);

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_setNativeEdgesArray(JNIEnv *env, jobject instance,
                                                                jdoubleArray edges_);

JNIEXPORT jdoubleArray JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_getNativeRoute(JNIEnv *env, jobject instance,
                                                           jdouble x1, jdouble y1, jdouble x2,
                                                           jdouble y2);

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_setGraphArraysFromFile(JNIEnv *env, jobject instance,
                                                                   jstring file_, jdouble scale);
}

//endregion

void prepare_sdk(JNIEnv *env)
{
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

    api.kMeshConfigClass = env->FindClass("pro/i_it/indoor/mesh/MeshConfig");
    api.kMeshConfigNXField = env->GetFieldID(api.kMeshConfigClass, "nx", "D");
    api.kMeshConfigNYField = env->GetFieldID(api.kMeshConfigClass, "ny", "D");
    api.kMeshConfigDXField = env->GetFieldID(api.kMeshConfigClass, "dx", "D");
    api.kMeshConfigDYField = env->GetFieldID(api.kMeshConfigClass, "dy", "D");
    api.kMeshConfigX0Field = env->GetFieldID(api.kMeshConfigClass, "x0", "D");
    api.kMeshConfigY0Field = env->GetFieldID(api.kMeshConfigClass, "y0", "D");
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_providers_AndroidMeasurementTransfer_deliver(
        JNIEnv *env, jobject, jobject obj) {

    jobject typeObj = env->GetObjectField(obj, api.kMeasurementEventTypeField);
    jlong timeStamp = env->GetLongField(obj, api.kMeasurementEventTimestampField);
    jdoubleArray dataArray = (jdoubleArray) env->GetObjectField(obj,
                                                                api.kMeasurementEventDataField);
    double *data = env->GetDoubleArrayElements(dataArray, NULL);

    jint eventTypeCode = env->CallIntMethod(typeObj, api.kMeasurementTypeGetCodeMethod);
    double eventTime = (1.0 * ((timeStamp - timeS) / 1000));
    if (eventTypeCode == 2) {
        jstring uuidString = (jstring) env->GetObjectField(obj, api.kMeasurementEventUUIDField);

        const char *uuid = env->GetStringUTFChars(uuidString, 0);

        BeaconUID uid(uuid, (int) data[0], (int) data[1]);

        BeaconReceivedData brd(eventTime, uid, data[3], data[2]);

        Position3D outPos = navigator->process(brd);
        LOGD("position from beacons (%f,%f,%f)", outPos.x, outPos.y, outPos.z);

        env->ReleaseStringUTFChars(uuidString, uuid);
    } else if (eventTypeCode == 1 && currentMode == SENSOR_BEACON_NAVIGATOR && sensorNavigator != NULL) {

        AccelReceivedData ard{eventTime, data[0], data[1], data[2], data[3], data[4], data[5]};

        Position3D outPos = sensorNavigator->process(ard);
        LOGD("position from sensors (%f,%f,%f)", outPos.x, outPos.y, outPos.z);
    }
    env->ReleaseDoubleArrayElements(dataArray, data, 0);

}

void initTracking() {
    vector<vector<Edge>> edges;
    int j = 0;
    int k = 0;
    vector<Edge> vEdge;
    for (int i = 0; i < sizeof(mEdges); i++) {
        if ((i + 1) % 3 == 0) {
            Edge edge(int(mEdges[i - 1]), mEdges[i]);
            vEdge[k++] = edge;
            if (k == 2) {
                edges[j++] = vEdge;
                k = 0;
            }
        }
    }
    edges[j] = vector<Edge>();

    vector<Position3D> vertices;
    int m = 0;
    for (int i = 0; i < sizeof(mGraphs); i++) {
        if (i % 2 != 0) {
            Position3D position3D(double(mGraphs[i - 1]), double(mGraphs[i]), 0.0);
            vertices[m++] = position3D;
        }
    }

    pointGraph = new PointGraph(edges, vertices);

}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeInit(
        JNIEnv *env, jobject instance, jint modeType, jintArray maskArray, jobject meshConfig) {
    prepare_sdk(env);

    currentMode = static_cast<Mode>(modeType);

    switch (currentMode) {

        case TRILATERATION_BEACON_NAVIGATOR : {
            auto rssiFact = make_shared<MovingAverageFilterFactory>(3);
            auto distFact = make_shared<NoFilterFactory>();
            navigator = new TrilatBeaconNavigator(rssiFact, distFact);
        }
            break;
        case SENSOR_BEACON_NAVIGATOR   :
        case STANDARD_BEACON_NAVIGATOR : {
            if (maskArray != NULL) {
                const jsize length = env->GetArrayLength(maskArray);
                jint *mask = env->GetIntArrayElements(maskArray, 0);

                vector<int> table(length);
                memcpy(&table[0], mask, length * sizeof(int));

                env->ReleaseIntArrayElements(maskArray, mask, 0);

                const double nx = env->GetDoubleField(meshConfig, api.kMeshConfigNXField);
                const double ny = env->GetDoubleField(meshConfig, api.kMeshConfigNYField);
                const double dx = env->GetDoubleField(meshConfig, api.kMeshConfigDXField);
                const double dy = env->GetDoubleField(meshConfig, api.kMeshConfigDYField);
                const double x0 = env->GetDoubleField(meshConfig, api.kMeshConfigX0Field);
                const double y0 = env->GetDoubleField(meshConfig, api.kMeshConfigY0Field);

                mesh = make_shared<RectanMesh>(nx, ny, dx, dy, x0, y0);

                mesh->setMaskTable(table);
                navigator = new StandardBeaconNavigator(mesh, false);
            }
        }
            break;
    }
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeRelease(
        JNIEnv *env, jobject instance) {
    delete [] navigator;
    navigator = NULL;
    delete [] pointGraph;
    pointGraph = NULL;
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeSetBeacons(
        JNIEnv *env, jobject instance, jobjectArray beacons) {
    jint size = env->GetArrayLength(beacons);

    jfloatArray position;
    jstring id;
    jfloatArray values;
    for (int i = 0; i < size; i++) {
        jobject beacon = env->GetObjectArrayElement(beacons, i);
        position = (jfloatArray) env->CallObjectMethod(beacon, api.kSpaceBeaconGetPositionMethod);
        id = (jstring) env->CallObjectMethod(beacon, api.kSpaceBeaconGetIdMethod);
        values = (jfloatArray) env->CallObjectMethod(beacon, api.kSpaceBeaconGetValuesMethod);

        jfloat *elements = env->GetFloatArrayElements(values, 0);
        jfloat *elementsPos = env->GetFloatArrayElements(position, 0);
        const char *uuid = env->GetStringUTFChars(id, 0);
        __android_log_print(ANDROID_LOG_DEBUG, "TAGTAG", "beacon %s, %f, %f", uuid, elements[0],
                            elements[1]);
        __android_log_print(ANDROID_LOG_DEBUG, "TAGTAG", "beacon %f, %f, %f", elementsPos[0],
                            elementsPos[1], elementsPos[2]);

        BeaconUID uid(uuid, (int) elements[0], (int) elements[1]);
        navigator->addBeacon(Beacon(uid, elements[2], elements[3],
                                    Position3D(elementsPos[0], elementsPos[1], elementsPos[2]),
                                    ""));

        env->ReleaseStringUTFChars(id, uuid);

    }
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeTakeLastPosition(JNIEnv *env, jobject instance, jfloatArray positionArray) {
    Position3D outPos = navigator->getLastPosition();

    if(currentMode == SENSOR_BEACON_NAVIGATOR && sensorNavigator == NULL){
        AccelConfig config;
        config.mapOrientationAngle = 0;
        config.useFilter = true;

        double startX = outPos.x, startY = outPos.y;

        sensorNavigator = new StandardAccelNavigator(mesh, startX, startY, config);
    }

    if(currentMode == SENSOR_BEACON_NAVIGATOR && sensorNavigator != NULL){
        //TODO: outPos = sensorNavigator->getLastPosition();
    }

    float *data = env->GetFloatArrayElements(positionArray, NULL);
    data[0] = (float) outPos.x;
    data[1] = (float) outPos.y;
    data[2] = (float) outPos.z;

    env->ReleaseFloatArrayElements(positionArray, data, 0);

}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_setNativeGraphArray(JNIEnv *env, jobject instance,
                                                                jintArray graphs_) {
    jint *graphs = env->GetIntArrayElements(graphs_, 0);

    const jsize graphsLenght = env->GetArrayLength(graphs_);

    mGraphs.clear();
    mGraphs.resize(graphsLenght);
    for (int i = 0; i < graphsLenght; i++) {
        mGraphs[i] = graphs[i];
    }

    env->ReleaseIntArrayElements(graphs_, graphs, 0);
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_setNativeEdgesArray(JNIEnv *env, jobject instance,
                                                                jdoubleArray edges_) {
    jdouble *edges = env->GetDoubleArrayElements(edges_, NULL);

    const jsize edgesLenght = env->GetArrayLength(edges_);

    mEdges.clear();
    mEdges.resize(edgesLenght);
    for (int i = 0; i < edgesLenght; i++) {
        mEdges[i] = edges[i];
    }

    env->ReleaseDoubleArrayElements(edges_, edges, 0);
}

JNIEXPORT jdoubleArray JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_getNativeRoute(JNIEnv *env, jobject instance,
                                                           jdouble x1, jdouble y1, jdouble x2,
                                                           jdouble y2) {

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

    return output;
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_setGraphArraysFromFile(JNIEnv *env, jobject instance,
                                                                   jstring file_, jdouble scale) {
    const char *file = env->GetStringUTFChars(file_, 0);

    std::string data(file);

    pointGraph = new PointGraph(data, scale);

    env->ReleaseStringUTFChars(file_, file);
}