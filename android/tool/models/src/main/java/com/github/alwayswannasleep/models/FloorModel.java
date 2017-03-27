package com.github.alwayswannasleep.models;

import android.graphics.PointF;
import android.os.Parcel;
import android.os.Parcelable;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

/**
 * Created by syn on 06.03.17.
 */

public class FloorModel implements Serializable, Parcelable {
    @SerializedName("id")
    private Long id;

    @SerializedName("configPath")
    private String configPath;

    @SerializedName("mapPath")
    private String mapPath;

    @SerializedName("graphPath")
    private String graphPath;

    @SerializedName("buildingTitle")
    private String buildingTitle;

    @SerializedName("number")
    private Integer number;

    @SerializedName("subtitle")
    private String subtitle;

    @SerializedName("inpointIdList")
    private List<Long> inpointIdList;

    @SerializedName("indoorMapId")
    private Long indoorMapId;

    @SerializedName("indoorMapTitle")
    private String indoorMapTitle;

    @SerializedName("beaconList")
    @Expose
    private List<BeaconModel> beacons;

    @SerializedName("pixelSize")
    @Expose
    private double pixelSize;

    @SerializedName("width")
    @Expose
    private double width;

    @SerializedName("height")
    @Expose
    private double height;

    @SerializedName("path")
    @Expose
    private String imgPath;

    @SerializedName("maskPath")
    @Expose
    private String maskPath;

    @SerializedName("mapUid")
    @Expose
    private String mapUid;

    @SerializedName("name")
    @Expose
    private String name;

    @SerializedName("description")
    @Expose
    private String description;

    @SerializedName("calibration_file_path")
    @Expose
    private String calibrationFilePath;

    private PointF destination;

    private int floorNumber;

    protected FloorModel(Parcel in) {
        configPath = in.readString();
        mapPath = in.readString();
        graphPath = in.readString();
        buildingTitle = in.readString();
        subtitle = in.readString();
        indoorMapTitle = in.readString();
        beacons = in.createTypedArrayList(BeaconModel.CREATOR);
        pixelSize = in.readDouble();
        width = in.readDouble();
        height = in.readDouble();
        imgPath = in.readString();
        maskPath = in.readString();
        mapUid = in.readString();
        name = in.readString();
        description = in.readString();
        calibrationFilePath = in.readString();
        destination = in.readParcelable(PointF.class.getClassLoader());
        floorNumber = in.readInt();
        id = in.readLong();
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeString(configPath);
        dest.writeString(mapPath);
        dest.writeString(graphPath);
        dest.writeString(buildingTitle);
        dest.writeString(subtitle);
        dest.writeString(indoorMapTitle);
        dest.writeTypedList(beacons);
        dest.writeDouble(pixelSize);
        dest.writeDouble(width);
        dest.writeDouble(height);
        dest.writeString(imgPath);
        dest.writeString(maskPath);
        dest.writeString(mapUid);
        dest.writeString(name);
        dest.writeString(description);
        dest.writeString(calibrationFilePath);
        dest.writeParcelable(destination, flags);
        dest.writeInt(floorNumber);
        dest.writeLong(id);
    }

    public static final Creator<FloorModel> CREATOR = new Creator<FloorModel>() {
        @Override
        public FloorModel createFromParcel(Parcel in) {
            return new FloorModel(in);
        }

        @Override
        public FloorModel[] newArray(int size) {
            return new FloorModel[size];
        }
    };

    public String getCalibrationFilePath() {
        return calibrationFilePath;
    }

    public void setCalibrationFilePath(String calibrationFilePath) {
        this.calibrationFilePath = calibrationFilePath;
    }

    public List<BeaconModel> getBeacons() {
        return beacons;
    }

    public void setBeacons(List<BeaconModel> beacons) {
        this.beacons = beacons;
    }

    public double getPixelSize() {
        return pixelSize;
    }

    public void setPixelSize(double pixelSize) {
        this.pixelSize = pixelSize;
    }

    public double getWidth() {
        return width;
    }

    public void setWidth(double width) {
        this.width = width;
    }

    public double getHeight() {
        return height;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    public String getImgPath() {
        return imgPath;
    }

    public void setImgPath(String imgPath) {
        this.imgPath = imgPath;
    }

    public String getMapUid() {
        return mapUid;
    }

    public void setMapUid(String mapUid) {
        this.mapUid = mapUid;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public PointF getDestination() {
        return destination;
    }

    public void setDestination(PointF destination) {
        this.destination = destination;

    }

    public String getMaskPath() {
        return maskPath;
    }

    public void setMaskPath(String maskPath) {
        this.maskPath = maskPath;
    }

    public String getDescription() {
        return description;
    }

    public int getFloorNumber() {
        return floorNumber;
    }

    public void setFloorNumber(final int floorNumber) {
        this.floorNumber = floorNumber;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getConfigPath() {
        return configPath;
    }

    public void setConfigPath(String configPath) {
        this.configPath = configPath;
    }

    public String getMapPath() {
        return mapPath;
    }

    public void setMapPath(String mapPath) {
        this.mapPath = mapPath;
    }

    public String getGraphPath() {
        return graphPath;
    }

    public void setGraphPath(String graphPath) {
        this.graphPath = graphPath;
    }

    public Integer getNumber() {
        return number;
    }

    public void setNumber(Integer number) {
        this.number = number;
    }

    public String getSubtitle() {
        return subtitle;
    }

    public void setSubtitle(String subtitle) {
        this.subtitle = subtitle;
    }

    public List<Long> getInpointIdList() {
        return inpointIdList;
    }

    public void setInpointIdList(List<Long> inpointIdList) {
        this.inpointIdList = inpointIdList;
    }

    public Long getIndoorMapId() {
        return indoorMapId;
    }

    public void setIndoorMapId(Long indoorMapId) {
        this.indoorMapId = indoorMapId;
    }

    public String getIndoorMapTitle() {
        return indoorMapTitle;
    }

    public void setIndoorMapTitle(String indoorMapTitle) {
        this.indoorMapTitle = indoorMapTitle;
    }

    public String getBuildingTitle() {
        return buildingTitle;
    }

    public void setBuildingTitle(String buildingTitle) {
        this.buildingTitle = buildingTitle;
    }

    public FloorModel() {
        beacons = new ArrayList<>();
        mapUid = UUID.randomUUID().toString();
    }



    @Override
    public int describeContents() {
        return 0;
    }

}
