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

extern "C" {

    JNIEXPORT jstring JNICALL
            Java_pro_i_1it_indoor_providers_AndroidDebuggableMeasurementTransfer_stringFromJNI(
            JNIEnv *env,
            jobject /* this */);

    JNIEXPORT void JNICALL
            Java_pro_i_1it_indoor_providers_AndroidMeasurementTransfer_deliver(
            JNIEnv *env,
            jobject /* this */, jobject obj);

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
}

    JNIEXPORT jstring JNICALL
    Java_pro_i_1it_indoor_providers_AndroidDebuggableMeasurementTransfer_stringFromJNI(
            JNIEnv *env,
            jobject /* this */) {
        std::string hello = "Hello from C++";
        return env->NewStringUTF(hello.c_str());
    }

    JNIEXPORT void JNICALL
    Java_pro_i_1it_indoor_providers_AndroidMeasurementTransfer_deliver(
            JNIEnv *env,
            jobject /* this */, jobject obj) {

        jclass measurementEventClass = env->GetObjectClass(obj);
        jclass measurementTypeEnum = env->FindClass("pro/i_it/indoor/events/MeasurementType");

        jfieldID typeId = env->GetFieldID(measurementEventClass, "type",
                                          "pro/i_it/indoor/events/MeasurementType");
        jfieldID timeStampId = env->GetFieldID(measurementEventClass, "timestamp", "J");
        jfieldID dataArrayId = env->GetFieldID(measurementEventClass, "data", "[D");

        jobject typeObj = env->GetObjectField(obj, typeId);
        jmethodID descriptionMethodId = env->GetMethodID(measurementTypeEnum, "getDescription",
                                                         "()Ljava/lang/String;");
        jstring description = (jstring) env->CallObjectMethod(typeObj,
                                                              descriptionMethodId); //value of enum MeasurementType

        long timeStamp = (long) env->GetLongField(obj, timeStampId);// value timestamp

        jobject dataArray = env->GetObjectField(obj, dataArrayId);
        jdoubleArray *array = reinterpret_cast<jdoubleArray *>(&dataArray);
        double *data = env->GetDoubleArrayElements(*array, NULL);

        auto rssiFact = make_shared<MovingAverageFilterFactory>(5);
        auto distFact = make_shared<NoFilterFactory>();

        navigator = new TrilatBeaconNavigator(rssiFact, distFact);

        // Create 3 beacons
        Beacon beacons[] = {
                Beacon(BeaconUID("Guinea Pig", 1, 0), -3.0, 2.0, Position3D(0.3, 0.5, 0.0), ""),
                Beacon(BeaconUID("Guinea Pig", 1, 1), -4.0, 2.5, Position3D(9.7, 0.4, 0.0), ""),
                Beacon(BeaconUID("Guinea Pig", 1, 2), -2.0, 3.0, Position3D(-0.2, 10.6, 0.0), "")
        };

        // Add them to the navigator
        navigator->addBeacons(beacons);

        // Create and process 3 events
        Position3D inPos(0.75, 0.38, 0.0); // Some given position
        BeaconUID uid("TODO", data[1], data[2]);
        BeaconReceivedData brd(timeStamp, uid, data[3]);

        // Process it
        Position3D outPos = navigator->process(brd);

        jfloatArray arrayJFloat = env->NewFloatArray(3);
        float dat[] = {2.f, 4.f, 5.f};
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
    }

    JNIEXPORT void JNICALL
    Java_pro_i_1it_indoor_IndoorLocationManager_nativeRelease(JNIEnv
                                                              *env,
                                                              jobject instance) {
        navigator = NULL;
        env->DeleteGlobalRef(savedListenerInstance);
        listenerOnLocationChangedId = NULL;
    }
