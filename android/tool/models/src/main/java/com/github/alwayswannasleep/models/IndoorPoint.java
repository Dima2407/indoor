package com.github.alwayswannasleep.models;

import com.google.gson.annotations.SerializedName;

import java.io.Serializable;

public final class IndoorPoint implements Serializable {

    @SerializedName("created_at")
    private long createdAt;

    @SerializedName("description")
    private String description;

    @SerializedName("id")
    private long id;

    @SerializedName("floorId")
    private long floorId;

    @SerializedName("gps_lat")
    private double latitude;

    @SerializedName("gps_lon")
    private double longitude;

    @SerializedName("gps_alt")
    private double altitude;

    @SerializedName("hint")
    private String hint;

    @SerializedName("icon_id")
    private String icon;

    @SerializedName("image")
    private String image;

    @SerializedName("near_x")
    private double nearX;

    @SerializedName("near_y")
    private double nearY;

    @SerializedName("subtitle")
    private String subtitle;

    @SerializedName("tags")
    private String tags;

    @SerializedName("title")
    private String title;

    @SerializedName("type")
    private String type;

    @SerializedName("updated_at")
    private long updatedAt;

    @SerializedName("x")
    private double x;

    @SerializedName("y")
    private double y;

    public long getCreatedAt() {
        return createdAt;
    }

    public void setCreatedAt(long createdAt) {
        this.createdAt = createdAt;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public long getFloorId() {
        return floorId;
    }

    public void setFloorId(long floorId) {
        this.floorId = floorId;
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

    public double getAltitude() {
        return altitude;
    }

    public void setAltitude(double altitude) {
        this.altitude = altitude;
    }

    public String getHint() {
        return hint;
    }

    public void setHint(String hint) {
        this.hint = hint;
    }

    public String getIcon() {
        return icon;
    }

    public void setIcon(String icon) {
        this.icon = icon;
    }

    public String getImage() {
        return image;
    }

    public void setImage(String image) {
        this.image = image;
    }

    public double getNearX() {
        return nearX;
    }

    public void setNearX(double nearX) {
        this.nearX = nearX;
    }

    public double getNearY() {
        return nearY;
    }

    public void setNearY(double nearY) {
        this.nearY = nearY;
    }

    public String getSubtitle() {
        return subtitle;
    }

    public void setSubtitle(String subtitle) {
        this.subtitle = subtitle;
    }

    public String getTags() {
        return tags;
    }

    public void setTags(String tags) {
        this.tags = tags;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public long getUpdatedAt() {
        return updatedAt;
    }

    public void setUpdatedAt(long updatedAt) {
        this.updatedAt = updatedAt;
    }

    public double getX() {
        return x;
    }

    public void setX(double x) {
        this.x = x;
    }

    public double getY() {
        return y;
    }

    public void setY(double y) {
        this.y = y;
    }

    @Override
    public String toString() {
        return "IndoorPoint{" +
                "createdAt=" + createdAt +
                ", description='" + description + '\'' +
                ", id=" + id +
                ", floorId=" + floorId +
                ", latitude=" + latitude +
                ", longitude=" + longitude +
                ", altitude=" + altitude +
                ", hint='" + hint + '\'' +
                ", icon='" + icon + '\'' +
                ", image='" + image + '\'' +
                ", nearX=" + nearX +
                ", nearY=" + nearY +
                ", subtitle='" + subtitle + '\'' +
                ", tags='" + tags + '\'' +
                ", title='" + title + '\'' +
                ", type='" + type + '\'' +
                ", updatedAt=" + updatedAt +
                ", x=" + x +
                ", y=" + y +
                '}';
    }
}
