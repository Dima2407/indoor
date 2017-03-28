package com.kit.indornavigation;

public final class Native {

    static {
        System.loadLibrary("native-lib");
    }

    public static native void addCalibrationBeacon(String hash, int major, int minor, float[] position);

    public static native void addCalibrationData(float[] beaconPosition, double[] rssi, float[] calibrationPosition, String hash, int major, int minor);

    public static native void calibrate();

    public static native boolean getCalibrationResults(String hash, int major, int minor, double[] results);

    public static native void clearCalibrationBeacons();
}
