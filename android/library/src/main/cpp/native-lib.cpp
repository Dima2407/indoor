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

extern "C" {

    JNIEXPORT jstring JNICALL
            Java_pro_i_1it_indoor_providers_AndroidDebuggableMeasurementTransfer_stringFromJNI(
            JNIEnv *env,
            jobject
 this
);

    JNIEXPORT void JNICALL
            Java_pro_i_1it_indoor_providers_AndroidMeasurementTransfer_deliver(
            JNIEnv *env,
            jobject
 this
, jobject obj);

    JNIEXPORT void JNICALL
            Java_pro_i_1it_indoor_IndoorLocationManager_nativeInit(JNIEnv
                                                                   *env,
                                                                   jobject instance,
                                                                   jobject
                                                                   onUpdateListener);

    JNIEXPORT void JNICALL
            Java_pro_i_1it_indoor_IndoorLocationManager_nativeRelease(JNIEnv
                                                                      *env,
                                                                      jobject instance);

    JNIEXPORT void JNICALL
            Java_pro_i_1it_indoor_IndoorLocationManager_nativeSetBeacons(JNIEnv *env, jobject instance,
                                                                         jobjectArray beacons);

}

    JNIEXPORT jstring JNICALL
    Java_pro_i_1it_indoor_providers_AndroidDebuggableMeasurementTransfer_stringFromJNI(
            JNIEnv *env,
            jobject
 this
) {
        std::string hello = "Hello from C++";
        return env->NewStringUTF(hello.c_str());
    }

    JNIEXPORT void JNICALL
    Java_pro_i_1it_indoor_providers_AndroidMeasurementTransfer_deliver(
            JNIEnv *env,
            jobject
 this
, jobject obj) {

        jobject typeObj = env->GetObjectField(obj, meTypeField);
        jint eventTypeCode = env->CallIntMethod(typeObj, mtCodeMethod); //value of enum MeasurementType
        long timeStamp = (long) env->GetLongField(obj, meTimestampField);// value timestamp
        jdoubleArray dataArray = (jdoubleArray) env->GetObjectField(obj, meDataField);
        double *data = env->GetDoubleArrayElements(dataArray, NULL);
        jstring uuidString = (jstring)env->GetObjectField(obj, meUUIDField);

        __android_log_print(ANDROID_LOG_DEBUG, "TAG", "x - %f y - %f z - %f", data[0], data[1], data[2]);

        const char * uuid = env->GetStringUTFChars(uuidString, 0);
        BeaconUID uid(uuid, (int)data[0], (int)data[1]);
        BeaconReceivedData brd(timeStamp, uid, data[2]);

        // Process it
        Position3D outPos = navigator->process(brd);

        jfloatArray arrayJFloat = env->NewFloatArray(3);
        float dat[] = {(float)outPos.x, (float)outPos.y, (float)outPos.z};

        env->ReleaseStringUTFChars(uuidString, uuid);
        env->SetFloatArrayRegion(arrayJFloat, 0, 3, dat);
        env->CallVoidMethod(savedListenerInstance, listenerOnLocationChangedId, arrayJFloat);
    }

    JNIEXPORT void JNICALL
    Java_pro_i_1it_indoor_IndoorLocationManager_nativeInit(JNIEnv
                                                           *env,
                                                           jobject instance,
                                                           jobject
                                                           onUpdateListener) {

        savedListenerInstance = env->NewGlobalRef(onUpdateListener);
        auto rssiFact = make_shared<MovingAverageFilterFactory>(5);
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
    }

    JNIEXPORT void JNICALL
    Java_pro_i_1it_indoor_IndoorLocationManager_nativeRelease(JNIEnv
                                                              *env,
                                                              jobject instance) {
        navigator = NULL;
        env->DeleteGlobalRef(savedListenerInstance);
        listenerOnLocationChangedId = NULL;
    }

    JNIEXPORT void JNICALL
    Java_pro_i_1it_indoor_IndoorLocationManager_nativeSetBeacons(JNIEnv *env, jobject instance,
                                                                 jobjectArray beacons) {

        jint size = env->GetArrayLength(beacons);

        jfloatArray position;
        jstring id;
        jfloatArray values;

        __android_log_print(ANDROID_LOG_DEBUG, "TAG", "size %i", size);
        for(int i = 0; i < size; i++){
            jobject beacon = env->GetObjectArrayElement(beacons, i);
            position = (jfloatArray)env->CallObjectMethod(beacon, getPositionId);
            id = (jstring)env->CallObjectMethod(beacon, getIdId);
            values = (jfloatArray)env->CallObjectMethod(beacon, getValuesId);

            jfloat *elements = env->GetFloatArrayElements(values, 0);
            jfloat *elementsPos = env->GetFloatArrayElements(position, 0);
            __android_log_print(ANDROID_LOG_DEBUG, "onLocationChanged", "values 1 - %f, 2 - %f, 3 - %f, 4 - %f, 5 - %f, 6 - %f, 7 - %f",
                                elements[0], elements[1], elements[2], elements[3],
                                elementsPos[0], elementsPos[1], elementsPos[2]);
            const char* uuid = env->GetStringUTFChars(id, 0);
            navigator->addBeacon(Beacon(BeaconUID(uuid, elements[0], elements[1]), elements[2], elements[3],
                                        Position3D(elementsPos[0], elementsPos[1], elementsPos[2]), ""));
            env->ReleaseStringUTFChars(id, uuid);
        }
    }
