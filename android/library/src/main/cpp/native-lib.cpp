#include <jni.h>
#include <string>

extern "C"
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
        jobject /* this */, jobject) {
}