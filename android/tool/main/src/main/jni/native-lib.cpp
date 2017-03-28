#include "Navigator.h"
#include <jni.h>
#include <android/log.h>

std::vector<Navigator::Beacons::Beacon> *beacons = NULL;
Navigator::Beacons::Calibrate::CalibrationPoint *calibrationPoint = NULL;
std::unordered_map<Navigator::Beacons::BeaconUID, Navigator::Beacons::Beacon> result;

void addCalibrationBeacon(JNIEnv *_env, jclass *_obj, jstring _hash, jint _major, jint _minor,
                          jfloatArray _beaconPosition) {
    float *beaconPosition = _env->GetFloatArrayElements(_beaconPosition, NULL);
    const char *hash = _env->GetStringUTFChars(_hash, NULL);

    if (beacons == NULL) {
        beacons = new std::vector<Navigator::Beacons::Beacon>();
    }

    beacons->push_back(
            {{hash, _major, _minor}, nan(""), nan(""), {beaconPosition[0], beaconPosition[1], 0}});

    _env->ReleaseFloatArrayElements(_beaconPosition, beaconPosition, 0);
    _env->ReleaseStringUTFChars(_hash, hash);
}

void
addCalibrationData(JNIEnv *_env, jclass *_obj, jfloatArray _beaconPosition, jdoubleArray _rssi,
                   jfloatArray _calibrationPosition, jstring _hash, jint _major, jint _minor) {
    float *beaconPosition = _env->GetFloatArrayElements(_beaconPosition, NULL);
    float *calibrationPosition = _env->GetFloatArrayElements(_calibrationPosition, NULL);
    double *rssi = _env->GetDoubleArrayElements(_rssi, NULL);
    int rssiElementsCount = _env->GetArrayLength(_rssi);
    const char *hash = _env->GetStringUTFChars(_hash, NULL);

    __android_log_print(ANDROID_LOG_INFO, "CRASH_TEST", "rssi_count=%d, hash=%s start",
                        rssiElementsCount, hash);

    if (calibrationPoint == NULL) {
        calibrationPoint = new Navigator::Beacons::Calibrate::CalibrationPoint();
        calibrationPoint->position = {calibrationPosition[0], calibrationPosition[1], 0};
    }

    for (int i = 0; i < rssiElementsCount; ++i) {
        calibrationPoint->packets.push_back({/*timestamp*/ 0, {hash, _major, _minor}, rssi[i]});
    }

    _env->ReleaseFloatArrayElements(_beaconPosition, beaconPosition, 0);
    _env->ReleaseFloatArrayElements(_calibrationPosition, calibrationPosition, 0);
    _env->ReleaseDoubleArrayElements(_rssi, rssi, 0);
    _env->ReleaseStringUTFChars(_hash, hash);

    __android_log_print(ANDROID_LOG_INFO, "CRASH_TEST", "rssi_count=%d, hash=%s end",
                        rssiElementsCount, hash);
}

void calibrate(JNIEnv *env, jclass *obj) {
    if (calibrationPoint == NULL) {
        return;
    }

    Navigator::Beacons::Calibrate::BeaconCalibrator calibrator;
    calibrator.addBeacons(*beacons);

    result = calibrator.calibrate({(*calibrationPoint)}, {});
}

jboolean getCalibrationResults(JNIEnv *_env, jclass *_obj, jstring _hash, jint _major, jint _minor,
                               jdoubleArray _outputResult) {
    if (result.empty()) {
        return JNI_FALSE;
    }

    const char *hash = _env->GetStringUTFChars(_hash, NULL);

    const Navigator::Beacons::Beacon &beacon = result.at({hash, _major, _minor});

    _env->SetDoubleArrayRegion(_outputResult, 0, 2,
                               new double[2]{beacon.getTxPower(), beacon.getDamp()});
    _env->ReleaseStringUTFChars(_hash, hash);
    return (jboolean) beacon.isCalibrated();
}

void clearCalibrationBeacons(JNIEnv *_env, jclass *_obj) {
    if (beacons != NULL) {
        delete beacons;
        beacons = NULL;
    }

    result.clear();

    if (calibrationPoint != NULL) {
        delete calibrationPoint;
        calibrationPoint = NULL;
    }
}

int registerNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *gMethods,
                          int numMethods) {
    jclass clazz;
    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

static JNINativeMethod gMethods[] = {
        {"addCalibrationBeacon",    "(Ljava/lang/String;II[F)V",     (void *) addCalibrationBeacon},
        {"addCalibrationData",      "([F[D[FLjava/lang/String;II)V", (void *) addCalibrationData},
        {"calibrate",               "()V",                           (void *) calibrate},
        {"getCalibrationResults",   "(Ljava/lang/String;II[D)Z",     (void *) getCalibrationResults},
        {"clearCalibrationBeacons", "()V",                           (void *) clearCalibrationBeacons}
};

static const char *const kClassPathName = "com/kit/indornavigation/Native";

jint JNI_OnLoad(JavaVM *pVm, void *reserved) {
    JNIEnv *env;
    if (pVm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }

    int result = registerNativeMethods(env,
                                       kClassPathName, gMethods,
                                       sizeof(gMethods) / sizeof(gMethods[0]));

    if (result != JNI_TRUE) {
        return -1;
    }

    return JNI_VERSION_1_6;
}