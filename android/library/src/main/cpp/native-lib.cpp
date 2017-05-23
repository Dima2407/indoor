#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <vector>

#include <jni.h>
#include <string>
#include <android/log.h>
#include <Navigator.h>


using namespace std;
using namespace Navigator::Beacons;
using namespace Navigator::Beacons::Factory;
using namespace Navigator::Dijkstra;
using namespace Navigator::Math::Trilat;
using Navigator::Math::Position3D;
using namespace Navigator::Mesh;

jobject savedListenerInstance;
jmethodID listenerOnLocationChangedId;
AbstractBeaconNavigator *navigator;
PointGraph *pointGraph;

jclass beaconClass;
jmethodID getPositionId;
jmethodID getIdId;
jmethodID getValuesId;

jfieldID meTypeField;
jfieldID meTimestampField;
jfieldID meDataField;
jfieldID meUUIDField;
jmethodID mtCodeMethod;

double timeS = 0;
char * pathToDownload = "/storage/emulated/0/Download/loglog.txt";
FILE *f;

enum Mode {
    TRILAT_BEACON_NAVIGATOR,
    STANDARD_BEACON_NAVIGATOR
} nativeMode;

enum CurrentMap {
    KAA_OFFICE,
    IT_JIM
} currentMap;

vector<int> mTable(2000);
vector<int> mGraphs(2000);
vector<double> mEdges(2000);


extern "C" {

JNIEXPORT jstring JNICALL
        Java_pro_i_1it_indoor_providers_AndroidDebuggableMeasurementTransfer_stringFromJNI(
        JNIEnv *env, jobject);

JNIEXPORT void JNICALL
        Java_pro_i_1it_indoor_providers_AndroidMeasurementTransfer_deliver(
        JNIEnv *env, jobject, jobject obj);

JNIEXPORT void JNICALL
        Java_pro_i_1it_indoor_IndoorLocationManager_nativeInit(
        JNIEnv *env, jobject instance, jobject onUpdateListener);

JNIEXPORT void JNICALL
        Java_pro_i_1it_indoor_IndoorLocationManager_nativeRelease(
        JNIEnv *env, jobject instance);

JNIEXPORT void JNICALL
        Java_pro_i_1it_indoor_IndoorLocationManager_nativeSetBeacons(
        JNIEnv *env, jobject instance, jobjectArray beacons);

JNIEXPORT void JNICALL
        Java_pro_i_1it_indoor_IndoorLocationManager_callEvent(JNIEnv *env, jobject instance);

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_setNativeMode(JNIEnv *env, jobject instance,
                                                          jint mode);

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_setNativeCurrentMap(JNIEnv *env, jobject instance,
                                                                jint map);

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_setNativeMaskArray(JNIEnv *env, jobject instance,
                                                               jintArray mask_);

/*JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_setNativeGraphArrays(JNIEnv *env, jobject instance,
                                                                 jintArray graphs_,
                                                                 jfloatArray edges_);*/

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

JNIEXPORT jstring JNICALL
Java_pro_i_1it_indoor_providers_AndroidDebuggableMeasurementTransfer_stringFromJNI(
        JNIEnv *env, jobject) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_providers_AndroidMeasurementTransfer_deliver(
        JNIEnv *env,  jobject, jobject obj) {
    f = fopen(pathToDownload, "a");
    fprintf(f, "METHOD: DELIVER \n\n");
    jobject typeObj = env->GetObjectField(obj, meTypeField);
    jint eventTypeCode = env->CallIntMethod(typeObj, mtCodeMethod); //value of enum MeasurementType
    long timeStamp = (long) env->GetLongField(obj, meTimestampField);// value timestamp
    __android_log_print(ANDROID_LOG_DEBUG, "TIMESTAMP", "TIMESTAMP %ld", timeStamp);
    jdoubleArray dataArray = (jdoubleArray) env->GetObjectField(obj, meDataField);
    double *data = env->GetDoubleArrayElements(dataArray, NULL);
    jstring uuidString = (jstring)env->GetObjectField(obj, meUUIDField);

    const char * uuid = env->GetStringUTFChars(uuidString, 0);
    __android_log_print(ANDROID_LOG_DEBUG, "TAG", "x - %f y - %f z - %f", data[0], data[1], data[2]);
    __android_log_print(ANDROID_LOG_DEBUG, "UUID", "uuid- %s", uuid);

    fprintf(f, "BeaconUID uid(%s, %f, %f)\n", uuid, (int)data[0], (int)data[1]);
    BeaconUID uid(uuid, (int)data[0], (int)data[1]);
    __android_log_print(ANDROID_LOG_DEBUG, "TAG", "beacon mv %s, %f, %f", uuid, data[0], data[1]);
    __android_log_print(ANDROID_LOG_DEBUG, "TAG", "data to lib %s, %f, %f", uuid, timeStamp, data[3]);

    fprintf(f, "BeaconReceivedData brd(%s, %f, %f)\n", uuid, (1.0*((timeStamp-timeS)/1000)), data[3]);
    fprintf(f, "timestamp/1000(%f)", (1.0*((timeStamp-timeS)/1000)));
    BeaconReceivedData brd((1.0*((timeStamp-timeS)/1000)), uid, data[3], data[2]);

  /*  __android_log_print(ANDROID_LOG_DEBUG, "TAGTAG", "beacons in navigator deliver %d", navigator->getBeacons());
    fprintf(f, "BEACONS IN NAVIGATOR: %d \n", navigator->getBeacons());
    __android_log_print(ANDROID_LOG_DEBUG, "onLocationChanged", "timestamp = %f, rssi = %f", brd.timestamp, brd.rssi);*/
    // Process it
    Position3D outPos = navigator->process(brd);
    __android_log_print(ANDROID_LOG_DEBUG, "TAGTAG", "POS x - %f y - %f z - %f", outPos.x, outPos.y, outPos.z);
    fprintf(f, "POSITION x - %f y - %f z - %f \n\n", outPos.x, outPos.y, outPos.z);

    auto processor = navigator->findProcessorByUid(uid);
    if (processor == nullptr) {
        __android_log_print(ANDROID_LOG_DEBUG, "onLocationChanged", "NULPOINTER");
    } else {
        if(processor->isActive()){
            __android_log_print(ANDROID_LOG_DEBUG, "onLocationChanged", "IS_ACTIVE = true");
        }else {
            __android_log_print(ANDROID_LOG_DEBUG, "onLocationChanged", "IS_ACTIVE = false");
        }
        __android_log_print(ANDROID_LOG_DEBUG, "onLocationChanged", "LAST_DIST = %f ", processor -> getLastDistance());
        __android_log_print(ANDROID_LOG_DEBUG, "onLocationChanged", "LAST_TIMESTAMP = %f ", processor -> getLastTimeStamp());
    }
    env->ReleaseStringUTFChars(uuidString, uuid);
    fclose(f);
}

void putToJavaOnLocationChanged(JNIEnv *env){
    f = fopen(pathToDownload, "a");
    Position3D outPos = navigator->getLastPosition();
    __android_log_print(ANDROID_LOG_DEBUG, "onLocationChanged", "POS x - %f y - %f z - %f", outPos.x, outPos.y, outPos.z);
    fprintf(f, "getLastPosition x - %f y - %f z - %f \n\n", outPos.x, outPos.y, outPos.z);
    float dat[] = {(float)outPos.x, (float)outPos.y, (float)outPos.z};
    jfloatArray arrayJFloat = env->NewFloatArray(3);
    env->SetFloatArrayRegion(arrayJFloat, 0, 3, dat);
    env->CallVoidMethod(savedListenerInstance, listenerOnLocationChangedId, arrayJFloat);
    fclose(f);
}

void initTracking(){
    vector<vector<Edge>> edges;
    int j = 0;
    int k = 0;
    vector<Edge> vEdge;
    for (int i = 0; i < sizeof(mEdges); i++){
        if ((i+1) % 3 == 0) {
            Edge edge(int(mEdges[i-1]), mEdges[i]);
            vEdge[k++] = edge;
            if (k == 2){
                edges[j++] = vEdge;
                k = 0;
            }
        }
    }
    edges[j] = vector<Edge>();

    vector<Position3D> vertices;
    int m = 0;
    for (int i = 0; i < sizeof(mGraphs); i++){
        if (i % 2 != 0){
            Position3D position3D(double (mGraphs[i-1]), double (mGraphs[i]), 0.0);
            vertices[m++] = position3D;
        }
    }

    pointGraph = new PointGraph(edges, vertices);

}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeInit(
        JNIEnv *env, jobject instance, jobject onUpdateListener) {
    f = fopen(pathToDownload, "a");
    if (f == NULL)
    {
        __android_log_print(ANDROID_LOG_DEBUG, "TAG", "Error opening file!\n");
    }

    savedListenerInstance = env->NewGlobalRef(onUpdateListener);

    switch (nativeMode){

        case TRILAT_BEACON_NAVIGATOR : {
            auto rssiFact = make_shared<MovingAverageFilterFactory>(3);
            auto distFact = make_shared<NoFilterFactory>();
            navigator = new TrilatBeaconNavigator(rssiFact, distFact);
        }
            break;

        case STANDARD_BEACON_NAVIGATOR : {
            if (currentMap == IT_JIM) {
                constexpr double nx = 36, ny = 24;
                constexpr double dx = 0.3, dy = 0.3;
                constexpr double x0 = 0, y0 = 0;
                auto mesh = make_shared<RectanMesh>(nx, ny, dx, dy, x0, y0);

                // vector<int> mTable(nx * ny);

                mesh->setMaskTable(mTable);
                navigator = new StandardBeaconNavigator(mesh, false);
            }

            if (currentMap == KAA_OFFICE) {
                constexpr double nx = 22, ny = 44;
                constexpr double dx = 0.3, dy = 0.3;
                constexpr double x0 = 0, y0 = 0;
                auto mesh = make_shared<RectanMesh>(nx, ny, dx, dy, x0, y0);

                // vector<int> mTable(nx * ny);

                mesh->setMaskTable(mTable);
                navigator = new StandardBeaconNavigator(mesh, false);
            }
        }
            break;
    }

    jclass listenerClassRef = env->GetObjectClass(savedListenerInstance);
    listenerOnLocationChangedId = env->GetMethodID(listenerClassRef, "onLocationChanged", "([F)V" );

    if(listenerOnLocationChangedId == 0){
        __android_log_write(ANDROID_LOG_DEBUG, "TAG", "error listener");
        return;
    }

    beaconClass = env->FindClass("pro/i_it/indoor/region/SpaceBeacon");

    getPositionId = env->GetMethodID(beaconClass, "getPosition", "()[F");

    getIdId = env->GetMethodID(beaconClass, "getId", "()Ljava/lang/String;");
    getValuesId = env->GetMethodID(beaconClass, "getValues", "()[F");


    jclass measurementEventClass = env->FindClass("pro/i_it/indoor/events/MeasurementEvent");

    meTypeField = env->GetFieldID(measurementEventClass, "type",
                                  "pro/i_it/indoor/events/MeasurementType");
    meTimestampField = env->GetFieldID(measurementEventClass, "timestamp", "J");
    meDataField = env->GetFieldID(measurementEventClass, "data", "[D");
    meUUIDField = env->GetFieldID(measurementEventClass, "uuid", "Ljava/lang/String;");

    jclass measurementTypeEnum = env->FindClass("pro/i_it/indoor/events/MeasurementType");
    mtCodeMethod = env->GetMethodID(measurementTypeEnum, "getCode", "()I");
    fclose(f);

  //  initTracking();
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeRelease(
        JNIEnv *env, jobject instance) {
    navigator = NULL;
    env->DeleteGlobalRef(savedListenerInstance);
    listenerOnLocationChangedId = NULL;
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeSetBeacons(
        JNIEnv *env, jobject instance, jobjectArray beacons) {
    f = fopen(pathToDownload, "a");
    jint size = env->GetArrayLength(beacons);

    jfloatArray position;
    jstring id;
    jfloatArray values;
    fprintf(f, "METHOD: SetBeacons\n");
    __android_log_print(ANDROID_LOG_DEBUG, "TAG", "size %i", size);
    for(int i = 0; i < size; i++){
        jobject beacon = env->GetObjectArrayElement(beacons, i);
        position = (jfloatArray)env->CallObjectMethod(beacon, getPositionId);
        id = (jstring)env->CallObjectMethod(beacon, getIdId);
        values = (jfloatArray)env->CallObjectMethod(beacon, getValuesId);

        jfloat *elements = env->GetFloatArrayElements(values, 0);
        jfloat *elementsPos = env->GetFloatArrayElements(position, 0);
        const char* uuid = env->GetStringUTFChars(id, 0);
        __android_log_print(ANDROID_LOG_DEBUG, "TAGTAG", "beacon %s, %f, %f", uuid, elements[0], elements[1]);
        __android_log_print(ANDROID_LOG_DEBUG, "TAGTAG", "beacon %f, %f, %f", elementsPos[0], elementsPos[1], elementsPos[2]);

        BeaconUID uid(uuid, elements[0], (int)elements[1]);
        navigator->addBeacon(Beacon(uid, elements[2], elements[3],
                                    Position3D(elementsPos[0], elementsPos[1], elementsPos[2]), ""));

        fprintf(f, "ADD BEACONS TO NAVIGATOR: uuid: %s, major: %f, minor: %f, txpower: %f, damp: %f, x: %f, y: %f, z: %f \n", uuid, elements[0], elements[1], elements[2], elements[3], elementsPos[0], elementsPos[1], elementsPos[2]);

       // __android_log_print(ANDROID_LOG_DEBUG, "TAGTAG", "beacons in navigator setBeacons %d", navigator->getBeacons());

        env->ReleaseStringUTFChars(id, uuid);

    }
    fclose(f);
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_callEvent(JNIEnv *env, jobject instance) {
    putToJavaOnLocationChanged(env);
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_setNativeMode(JNIEnv *env, jobject instance,
                                                          jint mode) {
   switch (mode){
       case 0:
           nativeMode = TRILAT_BEACON_NAVIGATOR;
           break;
       case 1:
           nativeMode = STANDARD_BEACON_NAVIGATOR;
           break;
   }
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_setNativeCurrentMap(JNIEnv *env, jobject instance,
                                                                jint map) {
    switch (map){
        case 0:
            currentMap = KAA_OFFICE;
            break;
        case 1:
            currentMap = IT_JIM;
            break;
    }
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_setNativeMaskArray(JNIEnv *env, jobject instance,
                                                               jintArray mask_) {

    if (mask_ != NULL) {
        const jsize length = env->GetArrayLength(mask_);
        jint *mask = env->GetIntArrayElements(mask_, 0);

        jintArray newArray = env->NewIntArray(length);

         mTable.clear();
         mTable.resize(length);
        for (int i = 0; i < length; i++) {
            mTable[i] = mask[i];
        }

        env->ReleaseIntArrayElements(mask_, mask, 0);
    }

}

/*JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_setNativeGraphArrays(JNIEnv *env, jobject instance,
                                                                 jintArray graphs_,
                                                                 jdoubleArray edges_) {
    jint *graphs = env->GetIntArrayElements(graphs_, NULL);
    jdouble *edges = env->GetDoubleArrayElements(edges_, NULL);

    const jsize graphsLenght = env->GetArrayLength(graphs_);
    const jsize edgesLenght = env->GetArrayLength(edges_);

    mGraphs.clear();
    mEdges.clear();
    mGraphs.resize(graphsLenght);
    mEdges.resize(edgesLenght);

    for (int i = 0; i < graphsLenght; i++) {
        mGraphs[i] = graphs[i];
    }
    for (int i = 0; i < edgesLenght; i++) {
        mEdges[i] = edges[i];
    }

    env->ReleaseIntArrayElements(graphs_, graphs, 0);
    env->ReleaseDoubleArrayElements(edges_, edges, 0);
}*/

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

   // initTracking();
    /*Position3D pos1(x1, y1, 0.0);
    Position3D pos2(x2, y2, 0.0);
    int startNode = pointGraph->findNearestVertex(pos1);
    int endNode = pointGraph->findNearestVertex(pos2);
    vector<Position3D> route;
    pointGraph->dijkstraP(startNode, endNode, route);*/
    int j = 0;
    jdoubleArray output = env->NewDoubleArray(/*route.size() * 2*/4);
    jdouble* destArrayElems = env->GetDoubleArrayElements(output, NULL);
    /*for (int i = 0; i < route.size(); i++){
        destArrayElems[j++] = route[i].x;
        destArrayElems[j++] = route[i].y;
    }*/
    destArrayElems[0] = 1.2;
    destArrayElems[1] = 2.3;
    destArrayElems[2] = 3.9;
    destArrayElems[3] = 8.2;

    env->ReleaseDoubleArrayElements(output, destArrayElems, NULL);

    return output;
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_setGraphArraysFromFile(JNIEnv *env, jobject instance,
                                                                   jstring file_, jdouble scale) {
    const char *file = env->GetStringUTFChars(file_, 0);

    __android_log_print(ANDROID_LOG_DEBUG, "TAG", "file content = %s", file);

    std::string data(file);

    pointGraph = new PointGraph(data, scale);

    __android_log_print(ANDROID_LOG_DEBUG, "TAG", "pointGraph created!\n");

    env->ReleaseStringUTFChars(file_, file);
}