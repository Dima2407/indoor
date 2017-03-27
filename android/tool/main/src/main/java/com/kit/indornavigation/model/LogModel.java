package com.kit.indornavigation.model;

import java.io.Serializable;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

/**
 * Created by syn on 07.03.17.
 */

public class LogModel implements Serializable {
    private String aStartTime;
    private float aUserPositionX;
    private float aUserPositionY;
    private ArrayList<BeaconLogModel> beaconsLog;

    public LogModel() {
        beaconsLog = new ArrayList<>();
    }

    public LogModel(ArrayList<BeaconLogModel> beaconsLog) {
        this.beaconsLog = beaconsLog;
    }

    public ArrayList<BeaconLogModel> getBeaconsLog() {
        return beaconsLog;
    }

    public void setBeaconsLog(ArrayList<BeaconLogModel> beaconsLog) {
        this.beaconsLog = beaconsLog;
    }

    public void setStartTime(long startTime) {
        this.aStartTime = new SimpleDateFormat("dd.MM.yyyy:HH-mm-ss").format(new Date(startTime));
    }

    public void setUserPositionX(float userPositionX) {
        this.aUserPositionX = userPositionX;
    }

    public void setUserPositionY(float userPositionY) {
        this.aUserPositionY = userPositionY;
    }
}
