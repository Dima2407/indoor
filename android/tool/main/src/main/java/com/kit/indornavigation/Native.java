package com.kit.indornavigation;

public final class Native {

    static {
        System.loadLibrary("native-lib");
    }

    public static native void addCalibrationBeacon(String hash, int major, int minor, float[] position);

    public static native void addCalibrationData(
            float[] beaconPosition,
            double[] rssi,
            long[] timestamps,
            String hash,
            int major,
            int minor
    );

    public static native void calibrate();

    public static native double[] getCalibrationResults(
            String hash,
            int major,
            int minor,
            double[] results
    );

    public static native void clearCalibrationBeacons();

    public native static void addPreviousCalibrationData(
            final float[] rssi,
            final float[] distances,
            final String macAddress,
            final int major,
            final int minor
    );

    public native static void addCalibrationPosition(final float[] calibrationPosition);
}
