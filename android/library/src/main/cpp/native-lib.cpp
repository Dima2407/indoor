#include <jni.h>
#include <string>
#include <android/log.h>

extern "C" {

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

        jfieldID typeId = env->GetFieldID(measurementEventClass, "type", "pro/i_it/indoor/events/MeasurementType");
        jfieldID timeStampId = env->GetFieldID(measurementEventClass, "timestamp", "J");
        jfieldID dataArrayId = env->GetFieldID(measurementEventClass, "data", "[D");

        jobject typeObj = env->GetObjectField(obj, typeId);
        jmethodID descriptionMethodId = env->GetMethodID(measurementTypeEnum, "getDescription", "()Ljava/lang/String;");
        jstring description = (jstring)env->CallObjectMethod(typeObj, descriptionMethodId); //value of enum MeasurementType

        __android_log_write(ANDROID_LOG_DEBUG, "TAG", env->GetStringUTFChars(description, 0));

        jlong timeStamp = env->GetLongField(obj, timeStampId);// value timestamp

        __android_log_print(ANDROID_LOG_DEBUG, "TAG", "timestamp = %li", timeStamp);

        jobject dataArray = env->GetObjectField(obj, dataArrayId);
        jdoubleArray *array = reinterpret_cast<jdoubleArray *>(&dataArray);
        double *data = env->GetDoubleArrayElements(*array, NULL);

        for(int i = 0; i < 2; i++){
            __android_log_print(ANDROID_LOG_DEBUG, "TAG", "array = %d", array[i]);
        }

    }




}
