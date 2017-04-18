#include "Navigator.h"
#include <jni.h>

using CalibrationPoint = Navigator::Beacons::Calibrate::CalibrationPoint;
using BeaconUID = Navigator::Beacons::BeaconUID;
using Beacon = Navigator::Beacons::Beacon;
using CalibrationTable = Navigator::Beacons::Calibrate::Algorithm::CalibrationTable;

std::vector<Navigator::Beacons::Beacon>* beacons = NULL;
CalibrationPoint* calibrationPoint = NULL;
std::vector<CalibrationPoint>* calibrationPoints = NULL;
std::unordered_map<BeaconUID, Beacon> result;
std::unordered_map<BeaconUID, CalibrationTable> previousCalibrationResults;

void addCalibrationBeacon(JNIEnv* _env, jclass* _obj, jstring _hash, jint _major, jint _minor,
                          jfloatArray _beaconPosition) {
    float* beaconPosition = _env->GetFloatArrayElements(_beaconPosition, NULL);
    const char* hash = _env->GetStringUTFChars(_hash, NULL);

    if (beacons == NULL) {
        beacons = new std::vector<Navigator::Beacons::Beacon>();
    }

    beacons->push_back(
            {{hash, _major, _minor}, nan(""), nan(""), {beaconPosition[0], beaconPosition[1], 0}});

    _env->ReleaseFloatArrayElements(_beaconPosition, beaconPosition, 0);
    _env->ReleaseStringUTFChars(_hash, hash);
}

void
addPreviousCalibrationData(JNIEnv* _env, jclass* _obj, jfloatArray _rssi, jfloatArray _distances,
                           jstring _mac, jint _major, jint _minor) {
    float* rssi = _env->GetFloatArrayElements(_rssi, NULL);
    float* distances = _env->GetFloatArrayElements(_distances, NULL);
    int rssiElementsCount = _env->GetArrayLength(_rssi);
    const char* mac = _env->GetStringUTFChars(_mac, NULL);

    BeaconUID uid(mac, _major, _minor);
    CalibrationTable table = previousCalibrationResults[uid];

    for (int i = 0; i < rssiElementsCount; ++i) {
        table.push_back(std::make_pair(distances[i], rssi[i]));
    }

    previousCalibrationResults[uid] = table;

    _env->ReleaseFloatArrayElements(_rssi, rssi, 0);
    _env->ReleaseFloatArrayElements(_distances, distances, 0);
    _env->ReleaseStringUTFChars(_mac, mac);
}

void addCalibrationPosition(JNIEnv* _env, jclass* _obj, jfloatArray calibrationPosition) {
    if (calibrationPoints == NULL) {
        calibrationPoints = new std::vector<CalibrationPoint>();
    }

    float* position = _env->GetFloatArrayElements(calibrationPosition, NULL);
    if (calibrationPoint != NULL) {
        calibrationPoints->push_back(*calibrationPoint);
    }
    delete calibrationPoint;
    calibrationPoint = new CalibrationPoint();
    calibrationPoint->position = {position[0], position[1], 0};

    _env->ReleaseFloatArrayElements(calibrationPosition, position, 0);
}

void
addCalibrationData(JNIEnv* _env, jclass* _obj, jfloatArray _beaconPosition, jdoubleArray _rssi,
                   jlongArray _timestamps, jstring _hash, jint _major, jint _minor) {
    float* beaconPosition = _env->GetFloatArrayElements(_beaconPosition, NULL);
    double* rssi = _env->GetDoubleArrayElements(_rssi, NULL);
    long long* timestamps = _env->GetLongArrayElements(_timestamps, NULL);
    int rssiElementsCount = _env->GetArrayLength(_rssi);
    const char* hash = _env->GetStringUTFChars(_hash, NULL);

    for (int i = 0; i < rssiElementsCount; ++i) {
        calibrationPoint->packets
                .push_back({(double) timestamps[i], {hash, _major, _minor}, rssi[i]});
    }

    _env->ReleaseFloatArrayElements(_beaconPosition, beaconPosition, 0);
    _env->ReleaseDoubleArrayElements(_rssi, rssi, 0);
    _env->ReleaseLongArrayElements(_timestamps, timestamps, 0);
    _env->ReleaseStringUTFChars(_hash, hash);
}

void calibrate(JNIEnv* env, jclass* obj) {
    if (calibrationPoints == NULL || beacons == NULL) {
        return;
    }

    calibrationPoints->push_back(*calibrationPoint);

    Navigator::Beacons::Calibrate::BeaconCalibrator calibrator;
    calibrator.addBeacons(*beacons);
    calibrator.setCalTables(previousCalibrationResults);

    result = calibrator.calibrate(*calibrationPoints, {});
    auto values = calibrator.getCalTables();

    for (auto it = values.begin(); it != values.end(); it++) {
        auto foundResult = previousCalibrationResults.find(it->first);
        if (foundResult == previousCalibrationResults.end()) {
            previousCalibrationResults[it->first] = it->second;
            continue;
        }

        foundResult->second.insert(foundResult->second.end(), it->second.begin(), it->second.end());
    }
}

jdoubleArray
getCalibrationResults(JNIEnv* _env, jclass* _obj, jstring _hash, jint _major, jint _minor,
                      jdoubleArray _outputResult) {
    if (result.empty()) {
        return NULL;
    }
    const char* hash = _env->GetStringUTFChars(_hash, NULL);

    BeaconUID uid = {hash, _major, _minor};
    const Beacon &beacon = result[uid];

    auto ret = new double[2]{beacon.getTxPower(), beacon.getDamp()};
    _env->SetDoubleArrayRegion(_outputResult, 0, 2, ret);
    _env->ReleaseStringUTFChars(_hash, hash);

    delete[] ret;

    if (!beacon.isCalibrated()) {
        return NULL;
    }

    auto results = previousCalibrationResults[uid];
    auto doubleResults = _env->NewDoubleArray(results.size() * 2);
    double* tmp = new double[results.size() * 2];
    int i = 0;
    for (auto it = results.begin(); it != results.end(); it++) {
        tmp[i++] = it->first;
        tmp[i++] = it->second;
    }

    _env->SetDoubleArrayRegion(doubleResults, 0, results.size() * 2, tmp);
    delete[] tmp;

    return doubleResults;
}

void clearCalibrationBeacons(JNIEnv* _env, jclass* _obj) {
    if (beacons != NULL) {
        delete beacons;
        beacons = NULL;
    }

    if (calibrationPoint != NULL) {
        delete calibrationPoint;
        calibrationPoint = NULL;
    }

    delete calibrationPoints;
    calibrationPoints = NULL;
}

int registerNativeMethods(JNIEnv* env, const char* className, JNINativeMethod* gMethods,
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
        {"addCalibrationBeacon",       "(Ljava/lang/String;II[F)V",     (void*) addCalibrationBeacon},
        {"addCalibrationData",         "([F[D[JLjava/lang/String;II)V", (void*) addCalibrationData},
        {"calibrate",                  "()V",                           (void*) calibrate},
        {"getCalibrationResults",      "(Ljava/lang/String;II[D)[D",    (void*) getCalibrationResults},
        {"clearCalibrationBeacons",    "()V",                           (void*) clearCalibrationBeacons},
        {"addPreviousCalibrationData", "([F[FLjava/lang/String;II)V",   (void*) addPreviousCalibrationData},
        {"addCalibrationPosition",     "([F)V",                         (void*) addCalibrationPosition}
};

static const char* const kClassPathName = "com/kit/indornavigation/Native";

jint JNI_OnLoad(JavaVM* pVm, void* reserved) {
    JNIEnv* env;
    if (pVm->GetEnv((void**) &env, JNI_VERSION_1_6) != JNI_OK) {
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