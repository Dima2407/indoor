package com.kit.indornavigation.core;

import com.github.alwayswannasleep.models.BeaconModel;
import com.github.alwayswannasleep.models.FloorModel;
import com.kit.indornavigation.Native;
import com.kit.indornavigation.model.BeaconConfigData;
import com.kit.indornavigation.model.CalibrationData;
import com.kit.indornavigation.model.CalibrationResult;

import java.util.ArrayList;
import java.util.List;

public class AlgoManager {

    private List<CalibrationResult> calibrateMap(
            List<CalibrationData> calibrationDatas,
            List<CalibrationResult> previosResults,
            List<BeaconModel> beacons,
            FloorModel map
    ) {

        if (!calibrationDatas.isEmpty()) {
            for (BeaconConfigData data : calibrationDatas.get(0).getConfigDatas()) {
                BeaconModel calibratedBeacon = data.getBeaconModel();
                if (CalibrationResult.listContainsBeacon(previosResults, calibratedBeacon)) {
                    CalibrationResult result = previosResults.get(CalibrationResult.findIndex(
                            previosResults,
                            calibratedBeacon));

                    List<CalibrationResult.Data> results = result.getResults();

                    float[] rssi = new float[results.size()];
                    float[] distances = new float[results.size()];

                    for (int i = 0; i < results.size(); i++) {
                        rssi[i] = results.get(i).getAvgRssi();
                        distances[i] = results.get(i).getCalibratedDistance();
                    }

                    Native.addPreviousCalibrationData(rssi,
                                                      distances,
                                                      calibratedBeacon.getMacAddress(),
                                                      (int) calibratedBeacon.getMajor(),
                                                      (int) calibratedBeacon.getMinor());
                }
            }
        }

        List<CalibrationResult> calibrationResults = new ArrayList<>(previosResults);

        float pixelSize = (float) map.getPixelSize();
        for (CalibrationData calibrationData : calibrationDatas) {
            List<BeaconConfigData> configDatas = calibrationData.getConfigDatas();

            float[] calibrationPosition = new float[]{calibrationData.getPosition().x * pixelSize, calibrationData
                    .getPosition().y * pixelSize};

            Native.addCalibrationPosition(calibrationPosition);
            for (BeaconConfigData configData : configDatas) {
                BeaconModel beaconModel = configData.getBeaconModel();

                float[] beaconPosition = new float[]{beaconModel.getPosition().x * pixelSize, beaconModel
                        .getPosition().y * pixelSize};

                Native.addCalibrationData(
                        beaconPosition,
                        asDoubleArray(configData.getRssiData()),
                        asLongArray(configData.getTimestampsData()),
                        beaconModel.getMacAddress(),
                        (int) beaconModel.getMajor(),
                        (int) beaconModel.getMinor()
                );
            }
        }

        Native.calibrate();

        for (BeaconModel beacon : beacons) {
            double[] results = new double[2];
            double[] calibrationPoints = Native.getCalibrationResults(beacon.getMacAddress(),
                                                                      (int) beacon.getMajor(),
                                                                      (int) beacon.getMinor(),
                                                                      results);

            if (calibrationPoints == null) {
                continue;
            }

            beacon.setTxPower((float) results[0]);
            beacon.setDamp((float) results[1]);

            CalibrationResult calibrationResult = null;
            int index = CalibrationResult.findIndex(calibrationResults, beacon);
            if (!calibrationResults.isEmpty() && index != -1) {
                calibrationResult = calibrationResults.get(index);
            }

            if (calibrationResult == null) {
                calibrationResult = new CalibrationResult();
                calibrationResult.setCalibratedBeacon(beacon);
                calibrationResult.setResults(new ArrayList<CalibrationResult.Data>());
                calibrationResults.add(calibrationResult);
            }

            List<CalibrationResult.Data> result = new ArrayList<>(calibrationResult.getResults());
            result.clear();

            for (int i = 0; i < calibrationPoints.length; i += 2) {
                CalibrationResult.Data data = new CalibrationResult.Data();
                data.setCalibratedDistance((float) calibrationPoints[i]);
                data.setAvgRssi((float) calibrationPoints[i + 1]);
                result.add(data);
            }

            calibrationResult.setResults(result);
        }

        Native.clearCalibrationBeacons();
        return calibrationResults;
    }

    private double[] asDoubleArray(List<Double> data) {
        double[] result = new double[data.size()];

        for (int i = 0; i < data.size(); i++) {
            result[i] = data.get(i);
        }

        return result;
    }

    private long[] asLongArray(final List<Long> data) {
        long[] result = new long[data.size()];

        for (int i = 0; i < data.size(); i++) {
            result[i] = data.get(i);
        }

        return result;
    }

    public List<CalibrationResult> calibrateBeacons(
            final List<BeaconModel> beaconModels,
            final List<CalibrationResult> calibrationResults,
            final List<CalibrationData> calibrationDatas,
            final FloorModel floorModel
    ) {
        float pixelSize = (float) floorModel.getPixelSize();
        for (BeaconModel beacon : beaconModels) {
            Native.addCalibrationBeacon(
                    beacon.getMacAddress(),
                    (int) beacon.getMajor(),
                    (int) beacon.getMinor(),
                    new float[]{beacon.getPosition().x * pixelSize, beacon.getPosition().y * pixelSize});
        }

        return calibrateMap(calibrationDatas, calibrationResults, beaconModels, floorModel);
    }
}
