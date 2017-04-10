package com.github.alwayswannasleep.models;

import android.graphics.PointF;
import android.os.Parcel;
import android.os.Parcelable;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

import java.io.Serializable;
import java.util.UUID;

public class BeaconModel implements Parcelable, Serializable, Cloneable {

    private static final float DEFAULT_DAMP = 2.f;
    private static final float DEFAULT_TX_POWER = -71.2f;
    private static final float DEFAULT_CALIBRATED_DISTANCE = 0;

    @SerializedName("x")
    @Expose
    private float positionX;

    @SerializedName("y")
    @Expose
    private float positionY;

    @SerializedName("z")
    @Expose
    private float positionZ;

    @SerializedName("uuid")
    @Expose
    private String uuid;

    @Expose
    @SerializedName("macAddress")
    private String macAddress;

    @Expose
    @SerializedName("buildingTitle")
    private String buildingTitle;

    @Expose
    @SerializedName("buildingId")
    private long buildingId;

    @Expose
    @SerializedName("floorNumber")
    private int floorNumber;

    @Expose
    @SerializedName("floorId")
    private long floorId;

    @Expose
    @SerializedName("damp")
    private float damp;

    @Expose
    @SerializedName("major")
    private long major;

    @Expose
    @SerializedName("minor")
    private long minor;

    @Expose
    @SerializedName("txpower")
    private float txPower;

    private float calibratedDistance;

    public BeaconModel() {
        setDefaultCalibrationData();
    }

    public BeaconModel(BeaconModel beaconModel) {
        uuid = beaconModel.getUuid();
        macAddress = beaconModel.getMacAddress();
        major = beaconModel.getMajor();
        minor = beaconModel.getMinor();
        setDefaultCalibrationData();
    }

    protected BeaconModel(Parcel in) {
        uuid = in.readString();
        positionX = in.readFloat();
        positionY = in.readFloat();
        positionZ = in.readFloat();
        macAddress = in.readString();
        buildingTitle = in.readString();
        buildingId = in.readLong();
        floorNumber = in.readInt();
        floorId = in.readLong();
        damp = in.readFloat();
        major = in.readLong();
        minor = in.readLong();
        txPower = in.readFloat();
        calibratedDistance = in.readFloat();
    }


    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(uuid);
        dest.writeFloat(positionX);
        dest.writeFloat(positionY);
        dest.writeFloat(positionZ);
        dest.writeString(macAddress);
        dest.writeString(buildingTitle);
        dest.writeLong(buildingId);
        dest.writeInt(floorNumber);
        dest.writeLong(floorId);
        dest.writeFloat(damp);
        dest.writeLong(major);
        dest.writeLong(minor);
        dest.writeFloat(txPower);
        dest.writeFloat(calibratedDistance);
    }

    @Override
    public int describeContents() {
        return 0;
    }

    public static final Creator<BeaconModel> CREATOR = new Creator<BeaconModel>() {
        @Override
        public BeaconModel createFromParcel(Parcel in) {
            return new BeaconModel(in);
        }

        @Override
        public BeaconModel[] newArray(int size) {
            return new BeaconModel[size];
        }
    };

    @Override
    public BeaconModel clone() {
        try {
            return (BeaconModel) super.clone();
        } catch (CloneNotSupportedException ignore) {
        }

        return null;
    }

    public String getUuid() {
        return uuid;
    }

    public void setUuid(String uuid) {
        this.uuid = uuid;
    }

    public String getMacAddress() {
        return macAddress;
    }

    public void setMacAddress(String macAddress) {
        this.macAddress = macAddress;
    }

    public PointF getPosition() {
        return new PointF(positionX, positionY);
    }

    public void setPosition(PointF position) {
        this.positionX = position.x;
        this.positionY = position.y;
    }

    public long getMajor() {
        return major;
    }

    public void setMajor(long major) {
        this.major = major;
    }

    public long getMinor() {
        return minor;
    }

    public void setMinor(long minor) {
        this.minor = minor;
    }

    @Override
    public String toString() {
        return "BeaconModel{" +
                ", positionX=" + positionX +
                ", positionY=" + positionY +
                ", macAddress='" + macAddress +
                '}';
    }

    public float getDamp() {
        return damp;
    }

    public void setDamp(float damp) {
        this.damp = damp;
    }

    public float getTxPower() {
        return txPower;
    }

    public void setTxPower(float txPower) {
        this.txPower = txPower;
    }

    public float getCalibratedDistance() {
        return calibratedDistance;
    }

    public void setCalibratedDistance(float calibratedDistance) {
        this.calibratedDistance = calibratedDistance;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        BeaconModel that = (BeaconModel) o;

        return macAddress != null ? macAddress.equals(that.macAddress) : that.macAddress == null;

    }

    public void setDefaultCalibrationData() {
        calibratedDistance = DEFAULT_CALIBRATED_DISTANCE;
        damp = DEFAULT_DAMP;
        txPower = DEFAULT_TX_POWER;
    }
}
