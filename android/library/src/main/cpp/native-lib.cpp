#include <jni.h>
#include <string>
#include <android/log.h>
#include <Navigator.h>


using namespace std;
using namespace Navigator::Beacons;
using namespace Navigator::Beacons::Factory;
using namespace Navigator::Math::Trilat;
using Navigator::Math::Position3D;

jobject savedListenerInstance;
jmethodID listenerOnLocationChangedId;
TrilatBeaconNavigator *navigator;

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

    __android_log_print(ANDROID_LOG_DEBUG, "TAGTAG", "beacons in navigator deliver %d", navigator->getBeacons());
    fprintf(f, "BEACONS IN NAVIGATOR: %d \n", navigator->getBeacons());
    __android_log_print(ANDROID_LOG_DEBUG, "onLocationChanged", "timestamp = %f, rssi = %f", brd.timestamp, brd.rssi);
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

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_nativeInit(
        JNIEnv *env, jobject instance, jobject onUpdateListener) {
    f = fopen(pathToDownload, "a");
    if (f == NULL)
    {
        __android_log_print(ANDROID_LOG_DEBUG, "TAG", "Error opening file!\n");
    }

    savedListenerInstance = env->NewGlobalRef(onUpdateListener);
    auto rssiFact = make_shared<MovingAverageFilterFactory>(3);
    auto distFact = make_shared<NoFilterFactory>();

    navigator = new TrilatBeaconNavigator(rssiFact, distFact);

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

        __android_log_print(ANDROID_LOG_DEBUG, "TAGTAG", "beacons in navigator setBeacons %d", navigator->getBeacons());

        env->ReleaseStringUTFChars(id, uuid);

    }
    fclose(f);
}

JNIEXPORT void JNICALL
Java_pro_i_1it_indoor_IndoorLocationManager_callEvent(JNIEnv *env, jobject instance) {
    putToJavaOnLocationChanged(env);
}