#define _USE_MATH_DEFINES

#define NDEBUG 0

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
using namespace Navigator::Accel::AngleFilt;
using namespace Navigator::Math::Kalman;
using namespace Navigator::Particles;


shared_ptr<AbstractBeaconNavigator> bluetoothNavigator;
shared_ptr<StandardAccelNavigator> sensorNavigator;
shared_ptr<ParticleNavigator> particleNavigator;
shared_ptr<PointGraph> pointGraph;
shared_ptr<RectanMesh> mesh;
unique_ptr<AngleCorrect> angleCorrect;


string logTrilat3FilePath;
string logBecPosFilePath;
string logAccFiltFilePath;
string logAccPosFilePath;
string logBeaconsFilePath;

struct IndoorSdkApi {
    jclass kSpaceBeaconClass;
    jmethodID kSpaceBeaconGetPositionMethod;
    jmethodID kSpaceBeaconGetIdMethod;
    jmethodID kSpaceBeaconGetValuesMethod;

    jclass kMeasurementEventClass;
    jfieldID kMeasurementEventTypeField;
    jfieldID kMeasurementEventTimestampField;
    jfieldID kMeasurementEventDataField;
    jfieldID kMeasurementEventUUIDField;
    jfieldID kMeasurementEventNestedField;

    jclass kMeasurementTypeEnum;
    jmethodID kMeasurementTypeGetCodeMethod;

    jclass kConfigMapClass;
    int kMeshConfigNXField = 0;
    int kMeshConfigNYField = 1;
    int kMeshConfigDXField = 2;
    int kMeshConfigDYField = 3;
    int kMeshConfigX0Field = 4;
    int kMeshConfigY0Field = 5;
    int kMaskField = 6;
    int kMapAngleField = 7;
    int kUseMaskField = 8;
    int kUseBeaconsField = 9;
    int kUseSensorsField = 10;
    int kInitXField = 11;
    int kInitYField = 12;
    int kBeaconsField = 13;
    int kGraphPathField = 14;
    int kGraphScaleField = 15;
    int kUseFilterField = 16;
    int kUseMapEdgesField = 17;
    int kUseMeshMaskField = 18;
    int kUseWallsField = 19;
    int kActiveBLEModeField = 20;
    int kMultiLaterationEnabledField = 21;
    int kParticleEnabledField = 22;
    int kUseKalmanFilter = 23;
    int kEnableLogger = 24;
    jmethodID kGetFloatMethod;
    jmethodID kGetIntMethod;
    jmethodID kGetDoubleMethod;
    jmethodID kGetBooleanMethod;
    jmethodID kGetObjectMethod;

    jclass kIndoorRouterClass;

    jfieldID kIndoorRouterOriginXField;
    jfieldID kIndoorRouterOriginYField;
    jfieldID kIndoorRouterDestinationXField;
    jfieldID kIndoorRouterDestinationYField;
    jfieldID kIndoorRouterDistanceField;
    jfieldID kIndoorRouterRouteField;
    jfieldID kIndoorRouterPixelSizeField;

};

struct IndoorSdkConfigs {
    bool useBeacons;
    bool useSensors;
    bool useMask;

    int mapAngle;

    float startX = std::nan("");
    float startY = std::nan("");

    bool sensorsActive;

    bool useFilter = false;
    bool useMapEdges = false;
    bool useMeshMask = false;
    bool useWalls = false;
    int activeBLEMode = 1;
    bool multiLaterationEnabled = false;
    bool particleEnabled = false;
    bool useKalmanFilter = false;
    bool enableLogger = false;
};

double timeS = -1;

IndoorSdkApi api;
IndoorSdkConfigs configs;

extern "C" {

JNIEXPORT jdoubleArray JNICALL
Java_pro_i_1it_indoor_providers_AndroidMeasurementTransfer_nativeDeliver(
        JNIEnv *env, jobject, jobject obj);

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeInit(
        JNIEnv *, jobject, jobject);

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeRelease(
        JNIEnv *, jobject);

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeTakeLastPositionWithDestination(JNIEnv *, jobject,
                                                                                  jobject);

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
    api.kMeasurementEventNestedField = env->GetFieldID(api.kMeasurementEventClass, "nested",
                                                       "[Lpro/i_it/indoor/events/MeasurementEvent;");
    api.kMeasurementEventUUIDField = env->GetFieldID(api.kMeasurementEventClass, "uuid",
                                                     "Ljava/lang/String;");

    api.kMeasurementTypeEnum = env->FindClass("pro/i_it/indoor/events/MeasurementType");
    api.kMeasurementTypeGetCodeMethod = env->GetMethodID(api.kMeasurementTypeEnum, "getCode",
                                                         "()I");

    api.kConfigMapClass = env->FindClass("pro/i_it/indoor/config/NativeConfigMap");
    api.kGetFloatMethod = env->GetMethodID(api.kConfigMapClass, "getFloat", "(I)F");
    api.kGetIntMethod = env->GetMethodID(api.kConfigMapClass, "getInt", "(I)I");
    api.kGetBooleanMethod = env->GetMethodID(api.kConfigMapClass, "getBoolean", "(I)Z");
    api.kGetDoubleMethod = env->GetMethodID(api.kConfigMapClass, "getDouble", "(I)D");
    api.kGetObjectMethod = env->GetMethodID(api.kConfigMapClass, "getObject",
                                            "(I)Ljava/lang/Object;");

    api.kIndoorRouterClass = env->FindClass("pro/i_it/indoor/routing/IndoorRouter");
    api.kIndoorRouterOriginXField = env->GetFieldID(api.kIndoorRouterClass, "startX", "F");
    api.kIndoorRouterOriginYField = env->GetFieldID(api.kIndoorRouterClass, "startY", "F");
    api.kIndoorRouterDestinationXField = env->GetFieldID(api.kIndoorRouterClass, "destinationX",
                                                         "F");
    api.kIndoorRouterDestinationYField = env->GetFieldID(api.kIndoorRouterClass, "destinationY",
                                                         "F");
    api.kIndoorRouterDistanceField = env->GetFieldID(api.kIndoorRouterClass, "distance", "F");
    api.kIndoorRouterRouteField = env->GetFieldID(api.kIndoorRouterClass, "route", "[F");
    api.kIndoorRouterPixelSizeField = env->GetFieldID(api.kIndoorRouterClass, "pixelSize", "D");

}

JNIEXPORT jdoubleArray JNICALL
Java_pro_i_1it_indoor_providers_AndroidMeasurementTransfer_nativeDeliver(
        JNIEnv *env, jobject, jobject obj) {
    jobject typeObj = env->GetObjectField(obj, api.kMeasurementEventTypeField);
    jlong timeStamp = env->GetLongField(obj, api.kMeasurementEventTimestampField);
    jobjectArray nestedEvents = (jobjectArray) env->GetObjectField(obj,
                                                                   api.kMeasurementEventNestedField);

    jint eventTypeCode = env->CallIntMethod(typeObj, api.kMeasurementTypeGetCodeMethod);
    if (timeS <= 0) {
        timeS = timeStamp;
    }
    double eventTime = (1.0 * ((timeStamp - timeS) / 1000));
    jdoubleArray positionResult = env->NewDoubleArray(3);
    if (eventTypeCode == 2 && configs.useBeacons) {

        const jsize length = env->GetArrayLength(nestedEvents);

        std::vector<BeaconReceivedData> brds;

        for (int i = 0; i < length; i++) {

            jobject event = env->GetObjectArrayElement(nestedEvents, i);

            jstring uuidString = (jstring) env->GetObjectField(event,
                                                               api.kMeasurementEventUUIDField);

            jdoubleArray dataArray = (jdoubleArray) env->GetObjectField(event,
                                                                        api.kMeasurementEventDataField);

            double *data = env->GetDoubleArrayElements(dataArray, NULL);

            const char *uuid = env->GetStringUTFChars(uuidString, 0);

            BeaconUID uid(uuid, (int) data[0], (int) data[1]);

            BeaconReceivedData brd(eventTime, uid, data[3], data[2]);
            brds.push_back(brd);
            env->ReleaseStringUTFChars(uuidString, uuid);
            env->ReleaseDoubleArrayElements(dataArray, data, 0);
        }

        // BLE process !!!!!!!!!!!!!!!!!!!!!!!
        Position3D outPos = bluetoothNavigator->process(brds);

        const double position[3] = {outPos.x, outPos.y, outPos.z};
        env->SetDoubleArrayRegion(positionResult, 0, 3, position);
        if (logBecPosFilePath.size() > 0) {
            ofstream fos(logBecPosFilePath, ios::app);
            fos.precision(8);
            fos << setw(10) << timeStamp << " " << setw(15) << eventTime << " " << outPos << endl;
        }

        if (! logTrilat3FilePath.empty()) {
            if (shared_ptr<KalmanBeaconNavigator> nav = dynamic_pointer_cast<KalmanBeaconNavigator>(
                    bluetoothNavigator)) {
                ofstream fos(logTrilat3FilePath, ios::app);
                vector<BeaconUID> uids = nav->getLastTrilatUids();
                for (auto value: uids) {
                    fos << timeStamp << " " << value << endl;
                }
            }
        }
    } else if (eventTypeCode == 1 && configs.useSensors && configs.sensorsActive) {   // Sensors (accel)
        jdoubleArray dataArray = (jdoubleArray) env->GetObjectField(obj,
                                                                    api.kMeasurementEventDataField);
        double *data = env->GetDoubleArrayElements(dataArray, NULL);
        double ax = data[0];
        double ay = data[1];
        double az = data[2];
        double azimuth = data[3];
        double pitch = data[4];
        double roll = data[5];

        // By Oleksiy Grechhnyev: use angleCorrect (moving average filter + -mapAngle + yaw corection) !
        angleCorrect->correct(azimuth, pitch, roll);

        /*// This is already included in angleCorrect !!!
        azimuth = azimuth - configs.mapAngle;

        if (azimuth > 180) {
            azimuth = -360 + azimuth;
        } else if (azimuth < -180) {
            azimuth = 360 + azimuth;
        }*/

        AccelReceivedData ard{eventTime, ax, ay, az, pitch, azimuth, roll};

        // Log ard
        if (! logAccFiltFilePath.empty()) {
            ofstream(logAccFiltFilePath, ios::app) << setw(12) << timeStamp << " " << setw(12) << eventTime << " " <<
                 setw(12) << ard.ax << " " << setw(12) << ard.ay << " " << setw(12) << ard.az << " " <<
                 setw(12) << ard.yaw << " " << setw(12) << ard.pitch << " " << setw(12) << ard.roll << endl;
        }

        // Sensor (Accelerometer) Navigator process() !!!!!!!!!!
        Position3D outPos = sensorNavigator->process(ard);

        // Log outpos
        if (! logAccPosFilePath.empty()) {
            ofstream(logAccPosFilePath, ios::app) << setw(12) << timeStamp << " " << setw(12) << eventTime << " " << outPos << endl;
        }

        const double position[3] = {outPos.x, outPos.y, outPos.z};
        env->SetDoubleArrayRegion(positionResult, 0, 3, position);
        env->ReleaseDoubleArrayElements(dataArray, data, 0);
    }
    return positionResult;
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeInit(
        JNIEnv *env, jobject instance, jobject config) {
    LOGD("IndoorLocationManager_nativeInit");
    timeS = -1;

    prepare_sdk(env);

    configs = {};
    configs.useBeacons = env->CallBooleanMethod(config, api.kGetBooleanMethod,
                                                api.kUseBeaconsField);
    configs.useSensors = env->CallBooleanMethod(config, api.kGetBooleanMethod,
                                                api.kUseSensorsField);
    configs.particleEnabled = env->CallBooleanMethod(config, api.kGetBooleanMethod,
                                                     api.kParticleEnabledField);
    configs.useMask = env->CallBooleanMethod(config, api.kGetBooleanMethod, api.kUseMaskField);
    configs.mapAngle = env->CallIntMethod(config, api.kGetIntMethod, api.kMapAngleField);
    configs.startX = env->CallFloatMethod(config, api.kGetFloatMethod, api.kInitXField);
    configs.startY = env->CallFloatMethod(config, api.kGetFloatMethod, api.kInitYField);
    configs.useFilter = env->CallBooleanMethod(config, api.kGetBooleanMethod, api.kUseFilterField);
    configs.useMapEdges = env->CallBooleanMethod(config, api.kGetBooleanMethod,
                                                 api.kUseMapEdgesField);
    configs.useMeshMask = env->CallBooleanMethod(config, api.kGetBooleanMethod,
                                                 api.kUseMeshMaskField);
    configs.useWalls = env->CallBooleanMethod(config, api.kGetBooleanMethod, api.kUseWallsField);
    configs.activeBLEMode = env->CallIntMethod(config, api.kGetIntMethod, api.kActiveBLEModeField);
    configs.multiLaterationEnabled = env->CallBooleanMethod(config, api.kGetBooleanMethod,
                                                            api.kMultiLaterationEnabledField);
    configs.useKalmanFilter = env->CallBooleanMethod(config, api.kGetBooleanMethod,
                                                     api.kUseKalmanFilter);
    configs.enableLogger = env->CallBooleanMethod(config, api.kGetBooleanMethod, api.kEnableLogger);


    // Oleksiy Grechnyev: create angleCorrect for correcting yaw, pitch, roll
    angleCorrect = make_unique<AngleCorrect>(configs.mapAngle, 20);

    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    {
        std::stringstream ss;
        ss << "/sdcard/Download/" << "triplets_ble_cpp"
           << std::put_time(&tm, "%d-%m-%Y %H-%M-%S")
           << ".txt";
        logTrilat3FilePath = ss.str();
    }
    {
        std::stringstream ss;
        ss << "/sdcard/Download/" << "beaconsID_cpp" << std::put_time(&tm, "%d-%m-%Y %H-%M-%S")
           << ".txt";
        logBeaconsFilePath = ss.str();
    }
    {
        std::stringstream ss;
        ss << "/sdcard/Download/" << "position_beacon_cpp"
           << std::put_time(&tm, "%d-%m-%Y %H-%M-%S")
           << ".txt";
        logBecPosFilePath = ss.str();
    }
    {
        std::stringstream ss;
        ss << "/sdcard/Download/" << "position_accel_cpp"
           << std::put_time(&tm, "%d-%m-%Y %H-%M-%S")
           << ".txt";
        logAccPosFilePath = ss.str();
    }
    if (configs.useSensors) {
        std::stringstream ss;
        ss << "/sdcard/Download/" << "accel_filtered_cpp"
           << std::put_time(&tm, "%d-%m-%Y %H-%M-%S")
           << ".txt";
        logAccFiltFilePath = ss.str();
        ofstream(logAccFiltFilePath) << " TS1 TS2  ax ay az yaw pitch roll" << endl;
    }

    if (configs.useMask) {
        jintArray maskArray = (jintArray) env->CallObjectMethod(config, api.kGetObjectMethod,
                                                                api.kMaskField);
        const jsize length = env->GetArrayLength(maskArray);
        jint *mask = env->GetIntArrayElements(maskArray, 0);

        vector<int> table(length);
        memcpy(&table[0], mask, length * sizeof(int));

        env->ReleaseIntArrayElements(maskArray, mask, 0);

        const double nx = env->CallDoubleMethod(config, api.kGetDoubleMethod,
                                                api.kMeshConfigNXField);
        const double ny = env->CallDoubleMethod(config, api.kGetDoubleMethod,
                                                api.kMeshConfigNYField);
        const double dx = env->CallDoubleMethod(config, api.kGetDoubleMethod,
                                                api.kMeshConfigDXField);
        const double dy = env->CallDoubleMethod(config, api.kGetDoubleMethod,
                                                api.kMeshConfigDYField);
        const double x0 = env->CallDoubleMethod(config, api.kGetDoubleMethod,
                                                api.kMeshConfigX0Field);
        const double y0 = env->CallDoubleMethod(config, api.kGetDoubleMethod,
                                                api.kMeshConfigY0Field);

        mesh = make_shared<RectanMesh>(nx, ny, dx, dy, x0, y0);

        mesh->setMaskTable(table);
    }
    if (configs.useBeacons) {

        shared_ptr<AbstractBeaconNavigator> navigator;

        if (configs.activeBLEMode == 1) {

            StandardBeaconNavigatorConfig nConfig;
            nConfig.meshConfig.useMeshMask = configs.useMeshMask;
            nConfig.meshConfig.useMapEdges = configs.useMapEdges;
            nConfig.useInit = true;

            if (configs.multiLaterationEnabled) {
                nConfig.useStrongest = 0;
            }
            navigator = make_shared<StandardBeaconNavigator>(mesh, false, nConfig);

        } else if (configs.activeBLEMode == 2) {
            KalmanBeaconNavigatorConfig nConfig;
            nConfig.meshConfig.useMeshMask = configs.useMeshMask;
            nConfig.meshConfig.useMapEdges = configs.useMapEdges;


            if (configs.multiLaterationEnabled) {
                nConfig.useStrongest = 0;
            }

            KalmanConfig filterConfig;

            navigator = make_shared<KalmanBeaconNavigator>(mesh, nConfig, filterConfig);

        }

        if (configs.useKalmanFilter) {
            MeshConfig meshConfig;
            meshConfig.useMapEdges = configs.useMapEdges;
            meshConfig.useMeshMask = configs.useMeshMask;
            const shared_ptr<KalmanXYBeaconNavigator> &nav = make_shared<KalmanXYBeaconNavigator>(
                    navigator, meshConfig, mesh);
            bluetoothNavigator = nav;
        } else {
            bluetoothNavigator = navigator;
        }

        jobjectArray beacons = (jobjectArray) env->CallObjectMethod(config, api.kGetObjectMethod,
                                                                    api.kBeaconsField);

        jint size = env->GetArrayLength(beacons);


        ofstream fileB(logBeaconsFilePath);


        for (int i = 0; i < size; i++) {
            jobject beacon = env->GetObjectArrayElement(beacons, i);
            jfloatArray position = (jfloatArray) env->CallObjectMethod(beacon,
                                                                       api.kSpaceBeaconGetPositionMethod);
            jstring id = (jstring) env->CallObjectMethod(beacon, api.kSpaceBeaconGetIdMethod);
            jfloatArray values = (jfloatArray) env->CallObjectMethod(beacon,
                                                                     api.kSpaceBeaconGetValuesMethod);

            jfloat *elements = env->GetFloatArrayElements(values, 0);
            jfloat *elementsPos = env->GetFloatArrayElements(position, 0);
            const char *uuid = env->GetStringUTFChars(id, 0);

            //if (configs.enableLogger) {
            fileB << uuid << "  " << (int) elements[0] << "  " << (int) elements[1] << "  ";
            fileB << elements[2] << "  " << elements[3] << "  ";
            fileB << elementsPos[0] << "  " << elementsPos[1] << "  " << elementsPos[2] << endl;
            // }

            BeaconUID uid(uuid, (int) elements[0], (int) elements[1]);
            bluetoothNavigator->addBeacon(Beacon(uid, elements[2], elements[3],
                                                 Position3D(elementsPos[0], elementsPos[1],
                                                            elementsPos[2]),
                                                 ""));


            env->ReleaseFloatArrayElements(values, elements, 0);
            env->ReleaseStringUTFChars(id, uuid);
        }


    }

    jstring graphPath_ = (jstring) env->CallObjectMethod(config, api.kGetObjectMethod,
                                                         api.kGraphPathField);
    double scale = env->CallDoubleMethod(config, api.kGetDoubleMethod, api.kGraphScaleField);
    //TODO: scale unused now, but in future
    const char *graphPath = env->GetStringUTFChars(graphPath_, 0);

    pointGraph = make_shared<PointGraph>(graphPath);

    env->ReleaseStringUTFChars(graphPath_, graphPath);
    LOGD("IndoorLocationManager_nativeInit -");
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeRelease(
        JNIEnv *env, jobject instance) {
    LOGD("IndoorLocationManager_nativeRelease");
    LOGD("IndoorLocationManager_nativeRelease -");
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeTakeLastPositionWithDestination(JNIEnv *env,
                                                                                  jobject instance,
                                                                                  jobject router) {
    LOGD("IndoorLocationManager_nativeTakeLastPosition");

    Position3D outPos(configs.startX, configs.startY, 0.0f);

    if (configs.useBeacons) {
        if (!bluetoothNavigator->isInitFinished()) {
            return;
        }
        outPos = bluetoothNavigator->getLastPosition();

    }

    if (std::isnan(outPos.x) || std::isnan(outPos.y)) {
        return;
    }

    if (configs.useSensors && !configs.sensorsActive) {
        AccelConfig aConfig;
        //aConfig.mapOrientationAngle = configs.mapAngle;
        aConfig.useFilter = configs.useFilter;
        aConfig.meshConfig.useMapEdges = configs.useMapEdges;
        aConfig.meshConfig.useMeshMask = configs.useMeshMask;
        aConfig.meshConfig.useWalls = configs.useWalls;
        LOGD("init position  at (%f %f)", outPos.x, outPos.y);

        double startX = outPos.x, startY = outPos.y;

        sensorNavigator = make_shared<StandardAccelNavigator>(mesh, startX, startY, aConfig);
        configs.sensorsActive = true;
        if (configs.particleEnabled && configs.useBeacons) {
            LOGD(" BLE = %p, SENSOR = %p", bluetoothNavigator.get(), sensorNavigator.get());
            particleNavigator = make_shared<ParticleNavigator>(bluetoothNavigator, sensorNavigator,
                                                               mesh);
        }
    }

    if (configs.useSensors && !configs.particleEnabled) {
        outPos = sensorNavigator->getLastPosition();
    }

    if (configs.particleEnabled) {
        LOGD("PARTICLE = %p", particleNavigator.get());
        outPos = particleNavigator->obtainLastPosition();
    }

    LOGD("last position (%f,%f,%f)", outPos.x, outPos.y, outPos.z);

    env->SetFloatField(router, api.kIndoorRouterOriginXField, (float) outPos.x);
    env->SetFloatField(router, api.kIndoorRouterOriginYField, (float) outPos.y);


    double destinationX = env->GetFloatField(router, api.kIndoorRouterDestinationXField);
    double destinationY = env->GetFloatField(router, api.kIndoorRouterDestinationYField);
    if (destinationX < 0 && destinationY < 0) {
        return;
    }
    double pixelSize = env->GetDoubleField(router, api.kIndoorRouterPixelSizeField);
    double startX = outPos.x / pixelSize;
    double startY = outPos.y / pixelSize;

    Position3D start(startX, startY, 0.0);
    Position3D end(destinationX, destinationY, 0.0);
    int startNode = pointGraph->findNearestVertex(start);
    int endNode = pointGraph->findNearestVertex(end);
    vector<Position3D> route;
    double distance = pointGraph->dijkstraP(startNode, endNode, route);

    env->SetFloatField(router, api.kIndoorRouterDistanceField, (float) distance);

    int length = route.size() * 2 + 4;
    jfloatArray output = env->NewFloatArray(length);  //
    jfloat *destArrayElems = env->GetFloatArrayElements(output, NULL);
    destArrayElems[0] = (float) startX;
    destArrayElems[1] = (float) startY;
    for (int i = 0, j = 2; i < route.size(); i++, j += 2) {
        destArrayElems[j] = (float) route[i].x;
        destArrayElems[j + 1] = (float) route[i].y;
    }
    destArrayElems[length - 2] = (float) destinationX;
    destArrayElems[length - 1] = (float) destinationY;

    env->ReleaseFloatArrayElements(output, destArrayElems, NULL);

    env->SetObjectField(router, api.kIndoorRouterRouteField, output);

    LOGD("IndoorLocationManager_nativeTakeLastPosition -");


}
