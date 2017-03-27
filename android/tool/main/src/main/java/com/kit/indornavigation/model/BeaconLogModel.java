package com.kit.indornavigation.model;

import org.altbeacon.beacon.Beacon;

public class BeaconLogModel {
    private long createTime;
    private int dump;
    private String mac;
    private String major;
    private String minor;
    private int rssi;
    private float tx;


    public BeaconLogModel(Beacon otherBeacon) {
        createTime = System.currentTimeMillis();
        mac = otherBeacon.getBluetoothAddress();
        major = otherBeacon.getId2().toHexString();
        minor = otherBeacon.getId3().toHexString();
        rssi = otherBeacon.getRssi();
        tx = otherBeacon.getTxPower();
        dump = 2;
    }

    public long getCreateTime() {
        return createTime;
    }

    public void setCreateTime(long createTime) {
        this.createTime = createTime;
    }

    public int getDump() {
        return dump;
    }

    public void setDump(int dump) {
        this.dump = dump;
    }

    public String getMac() {
        return mac;
    }

    public void setMac(String mac) {
        this.mac = mac;
    }

    public int getRssi() {
        return rssi;
    }

    public void setRssi(int rssi) {
        this.rssi = rssi;
    }

    public float getTx() {
        return tx;
    }

    public void setTx(float tx) {
        this.tx = tx;
    }

    public String getMajor() {
        return major;
    }

    public void setMajor(String major) {
        this.major = major;
    }

    public String getMinor() {
        return minor;
    }

    public void setMinor(String minor) {
        this.minor = minor;
    }
}
