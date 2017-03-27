package com.kit.indornavigation.core;

import android.content.Context;

import com.github.alwayswannasleep.models.BeaconModel;
import com.github.alwayswannasleep.models.FloorModel;
import com.kit.indornavigation.model.BeaconConfigData;
import com.kit.indornavigation.model.CalibrationData;
import com.kit.indornavigation.utils.FileUtils;

import java.util.ArrayList;
import java.util.List;

public class AlgoManager {

    private final App app;
    AlgoManager(Context context) {
        app = (App) context.getApplicationContext();
    }

    private List<BeaconModel> calibrateMap(CalibrationData calibrationData, FloorModel map) {
        List<BeaconModel> calibrationResults = new ArrayList<>();
        List<BeaconConfigData> configDatas = calibrationData.getConfigDatas();

        for (BeaconConfigData configData : configDatas) {
            double[] txPower = new double[configData.getRssiData().size()];
            double[] damp = new double[configData.getRssiData().size()];

            float distance = calculateAverage(configData.getDistanceData());
            BeaconModel beaconModel = configData.getBeaconModel();

            // TODO add calibration
//            boolean calibrate = PositioningBridge.calibrate(
//                    configData.getHash(),
//                    asArray(configData.getRssiData()),
//                    asArray(configData.getDistanceData()),
//                    configData.getRssiData().size(),
//                    txPower,
//                    damp
//            );

            List<Double> txPowerArray = new ArrayList<>();
            List<Double> dampArray = new ArrayList<>();

            for (int i = 0; i < txPower.length; i++) {
                txPowerArray.add(txPower[i]);
                dampArray.add(damp[i]);
            }

            configData.setTxData(txPowerArray);
            configData.setDampData(dampArray);

            beaconModel.setCalibratedDistance(distance);
            beaconModel.setDamp(calculateAverage(dampArray));
            beaconModel.setTxPower(calculateAverage(txPowerArray));

            calibrationResults.add(beaconModel);
        }

        FileUtils.saveCalibrationData(calibrationData, map, app);

        return calibrationResults;
    }

    public List<BeaconModel> calibrateBeacons(CalibrationData calibrationData, FloorModel floorModel) {
        List<BeaconModel> beacons = floorModel.getBeacons();
        for (BeaconModel beacon : beacons) {
        }

        return calibrateMap(calibrationData, floorModel);
    }

    private float calculateAverage(List<Double> distanceData) {
        double sum = 0;

        for (double distance : distanceData) {
            sum += distance;
        }

        return (float) sum / distanceData.size();
    }

    private double[] asArray(List<Double> data) {
        double[] result = new double[data.size()];

        for (int i = 0; i < data.size(); i++) {
            result[i] = data.get(i);
        }

        return result;
    }
}
