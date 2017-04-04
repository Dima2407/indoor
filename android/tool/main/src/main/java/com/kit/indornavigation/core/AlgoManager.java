package com.kit.indornavigation.core;

import android.content.Context;

import com.github.alwayswannasleep.models.BeaconModel;
import com.github.alwayswannasleep.models.FloorModel;
import com.kit.indornavigation.Native;
import com.kit.indornavigation.model.BeaconConfigData;
import com.kit.indornavigation.model.CalibrationData;
import com.kit.indornavigation.utils.FileUtils;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class AlgoManager {

    private final App app;

    AlgoManager(Context context) {
        app = (App) context.getApplicationContext();
    }

    private List<BeaconModel> calibrateMap(
            CalibrationData calibrationData,
            FloorModel map,
            float pixelSize
    ) {
        List<BeaconModel> calibrationResults = new ArrayList<>();
        List<BeaconConfigData> configDatas = calibrationData.getConfigDatas();

        float[] calibrationPosition = new float[]{calibrationData.getPosition().x * pixelSize, calibrationData
                .getPosition().y * pixelSize};
        for (BeaconConfigData configData : configDatas) {
            BeaconModel beaconModel = configData.getBeaconModel();

            float[] beaconPosition = new float[]{beaconModel.getPosition().x * pixelSize, beaconModel
                    .getPosition().y * pixelSize};

            Native.addCalibrationData(
                    beaconPosition,
                    asDoubleArray(configData.getRssiData()),
                    asLongArray(configData.getTimestampsData()),
                    calibrationPosition,
                    beaconModel.getMacAddress(),
                    (int) beaconModel.getMajor(),
                    (int) beaconModel.getMinor()
            );
        }

        Native.calibrate();

        for (BeaconConfigData configData : configDatas) {
            BeaconModel beaconModel = configData.getBeaconModel();

            double[] results = new double[2];
            if (!Native.getCalibrationResults(
                    beaconModel.getMacAddress(),
                    (int) beaconModel.getMajor(),
                    (int) beaconModel.getMinor(),
                    results)
                    ) {
                continue;
            }

            configData.setTxData(Collections.nCopies(configData.getDistanceData().size(),
                                                     results[0]
            ));
            configData.setDampData(Collections.nCopies(configData.getDistanceData().size(),
                                                       results[1]
            ));

            beaconModel.setCalibratedDistance(calculateAverage(configData.getDistanceData()));
            beaconModel.setDamp((float) results[1]);
            beaconModel.setTxPower((float) results[0]);

            calibrationResults.add(beaconModel);
        }

        FileUtils.saveCalibrationData(calibrationData, map, app);

        Native.clearCalibrationBeacons();
        return calibrationResults;
    }

    public List<BeaconModel> calibrateBeacons(
            CalibrationData calibrationData,
            List<BeaconModel> beacons,
            float pixelSize,
            FloorModel map
    ) {
        for (BeaconModel beacon : beacons) {
            Native.addCalibrationBeacon(
                    beacon.getMacAddress(),
                    (int) beacon.getMajor(),
                    (int) beacon.getMinor(),
                    new float[]{beacon.getPosition().x * pixelSize, beacon.getPosition().y * pixelSize}
            );
        }

        return calibrateMap(calibrationData, map, pixelSize);
    }

    private float calculateAverage(List<Double> distanceData) {
        double sum = 0;

        for (double distance : distanceData) {
            sum += distance;
        }

        return (float) sum / distanceData.size();
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

}
