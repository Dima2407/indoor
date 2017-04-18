package com.kit.indornavigation.model;

import com.github.alwayswannasleep.models.BeaconModel;

import java.util.List;

public class CalibrationResult {

    public static boolean listContainsBeacon(
            List<CalibrationResult> calibrationResults,
            BeaconModel beaconModel
    ) {
        for (int i = 0; i < calibrationResults.size(); i++) {
            if (beaconModel.equals(calibrationResults.get(i).getCalibratedBeacon())) {
                return true;
            }
        }

        return false;
    }

    public static int findIndex(
            List<CalibrationResult> calibrationResults,
            BeaconModel beaconModel
    ) {
        for (int i = 0; i < calibrationResults.size(); i++) {
            if (beaconModel.equals(calibrationResults.get(i).getCalibratedBeacon())) {
                return i;
            }
        }

        return -1;
    }

    public static int findLastIndex(
            List<CalibrationResult> calibrationResults,
            BeaconModel beaconModel
    ) {
        for (int i = calibrationResults.size() - 1; i >= 0; i--) {
            if (beaconModel.equals(calibrationResults.get(i).getCalibratedBeacon())) {
                return i;
            }
        }

        return -1;
    }

    private BeaconModel calibratedBeacon;
    private List<Data> results;

    @Override
    public boolean equals(final Object o) {
        if (this == o) {
            return true;
        }

        if (!(o instanceof CalibrationResult)) {
            return false;
        }

        final CalibrationResult that = (CalibrationResult) o;

        return calibratedBeacon != null ? calibratedBeacon.equals(that.calibratedBeacon) : that.calibratedBeacon == null;
    }

    public BeaconModel getCalibratedBeacon() {
        return calibratedBeacon;
    }

    public void setCalibratedBeacon(final BeaconModel calibratedBeacon) {
        this.calibratedBeacon = calibratedBeacon;
    }

    public List<Data> getResults() {
        return results;
    }

    public void setResults(final List<Data> results) {
        this.results = results;
    }

    @Override
    public int hashCode() {
        return calibratedBeacon != null ? calibratedBeacon.hashCode() : 0;
    }

    public static class Data {

        private float calibratedDistance;
        private float avgRssi;

        public float getCalibratedDistance() {
            return calibratedDistance;
        }

        public void setCalibratedDistance(final float calibratedDistance) {
            this.calibratedDistance = calibratedDistance;
        }

        public float getAvgRssi() {
            return avgRssi;
        }

        public void setAvgRssi(final float avgRssi) {
            this.avgRssi = avgRssi;
        }
    }
}
