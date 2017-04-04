package com.kit.indornavigation.model;

import com.github.alwayswannasleep.models.BeaconModel;

import java.util.List;

public final class BeaconConfigData {
    private int hash;
    private BeaconModel beaconModel;
    private List<Double> rssiData;
    private List<Double> txData;
    private List<Double> distanceData;
    private List<Double> dampData;
    private List<Long> timestampsData;

    public int getHash() {
        return hash;
    }

    public void setHash(int hash) {
        this.hash = hash;
    }

    public List<Double> getRssiData() {
        return rssiData;
    }

    public void setRssiData(List<Double> rssiData) {
        this.rssiData = rssiData;
    }

    public List<Double> getTxData() {
        return txData;
    }

    public void setTxData(List<Double> txData) {
        this.txData = txData;
    }

    public List<Double> getDistanceData() {
        return distanceData;
    }

    public void setDistanceData(List<Double> distanceData) {
        this.distanceData = distanceData;
    }

    public List<Double> getDamp() {
        return dampData;
    }

    public void setDampData(List<Double> dampData) {
        this.dampData = dampData;
    }

    public BeaconModel getBeaconModel() {
        return beaconModel;
    }

    public void setBeaconModel(BeaconModel beaconModel) {
        this.beaconModel = beaconModel;
    }

    public List<Long> getTimestampsData() {
        return timestampsData;
    }

    public void setTimestampsData(final List<Long> timestampsData) {
        this.timestampsData = timestampsData;
    }
}
