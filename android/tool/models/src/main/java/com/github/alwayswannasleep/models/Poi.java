package com.github.alwayswannasleep.models;

import com.google.gson.annotations.SerializedName;

import java.io.Serializable;

public final class Poi implements Serializable {

    @SerializedName("id")
    private long id;

    @SerializedName("poiDescription")
    private String poiDescription;

    @SerializedName("poiImage")
    private String poiImage;

    @SerializedName("poiLatitude")
    private double latitude;

    @SerializedName("poiLongitude")
    private double longitude;

    @SerializedName("poiName")
    private String poiName;

    @SerializedName("SpecialPoiName")
    private String specialPoiName;

    @SerializedName("xMercator")
    private double mercatorX;

    @SerializedName("yMercator")
    private double mercatorY;

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getPoiDescription() {
        return poiDescription;
    }

    public void setPoiDescription(String poiDescription) {
        this.poiDescription = poiDescription;
    }

    public String getPoiImage() {
        return poiImage;
    }

    public void setPoiImage(String poiImage) {
        this.poiImage = poiImage;
    }

    public double getLatitude() {
        return latitude;
    }

    public void setLatitude(double latitude) {
        this.latitude = latitude;
    }

    public double getLongitude() {
        return longitude;
    }

    public void setLongitude(double longitude) {
        this.longitude = longitude;
    }

    public String getPoiName() {
        return poiName;
    }

    public void setPoiName(String poiName) {
        this.poiName = poiName;
    }

    public String getSpecialPoiName() {
        return specialPoiName;
    }

    public void setSpecialPoiName(String specialPoiName) {
        this.specialPoiName = specialPoiName;
    }

    public double getMercatorX() {
        return mercatorX;
    }

    public void setMercatorX(double mercatorX) {
        this.mercatorX = mercatorX;
    }

    public double getMercatorY() {
        return mercatorY;
    }

    public void setMercatorY(double mercatorY) {
        this.mercatorY = mercatorY;
    }

    @Override
    public String toString() {
        return "Poi{" +
                "mercatorY=" + mercatorY +
                ", mercatorX=" + mercatorX +
                ", specialPoiName='" + specialPoiName + '\'' +
                ", poiName='" + poiName + '\'' +
                ", longitude=" + longitude +
                ", latitude=" + latitude +
                ", poiImage='" + poiImage + '\'' +
                ", poiDescription='" + poiDescription + '\'' +
                ", id=" + id +
                '}';
    }
}
