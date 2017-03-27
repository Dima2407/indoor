package com.github.alwayswannasleep.models;

import com.google.gson.annotations.SerializedName;

import java.io.Serializable;
import java.util.Date;
import java.util.List;

public final class IndoorMap implements Serializable {

    @SerializedName("created_at")
    private Date createdAt;

    @SerializedName("floor_list")
    private List<FloorModel> floors;

    @SerializedName("id")
    private long id;

    @SerializedName("subtitle")
    private String subTitle;

    @SerializedName("title")
    private String title;

    @SerializedName("updated_at")
    private Date updatedAt;

    public long getCreatedAt() {
        return createdAt.getTime();
    }

    public void setCreatedAt(long createdAt) {
        this.createdAt = new Date(createdAt);
    }

    public List<FloorModel> getFloors() {
        return floors;
    }

    public void setFloors(List<FloorModel> floors) {
        this.floors = floors;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public String getSubTitle() {
        return subTitle;
    }

    public void setSubTitle(String subTitle) {
        this.subTitle = subTitle;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public long getUpdatedAt() {
        return updatedAt.getTime();
    }

    public void setUpdatedAt(long updatedAt) {
        this.updatedAt = new Date(updatedAt);
    }

    @Override
    public String toString() {
        return "Map{" +
                "createdAt=" + createdAt +
                ", data='" + floors + '\'' +
                ", id=" + id +
                ", subTitle='" + subTitle + '\'' +
                ", title='" + title + '\'' +
                ", updatedAt=" + updatedAt +
                '}';
    }
}
