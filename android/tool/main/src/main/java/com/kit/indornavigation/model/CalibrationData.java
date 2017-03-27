package com.kit.indornavigation.model;

import android.graphics.PointF;

import java.util.List;

public final class CalibrationData {

    private PointF position;
    private List<BeaconConfigData> configDatas;

    public PointF getPosition() {
        return position;
    }

    public void setPosition(PointF position) {
        this.position = position;
    }

    public List<BeaconConfigData> getConfigDatas() {
        return configDatas;
    }

    public void setConfigDatas(List<BeaconConfigData> configDatas) {
        this.configDatas = configDatas;
    }
}
