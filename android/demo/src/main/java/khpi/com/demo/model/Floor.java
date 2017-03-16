package khpi.com.demo.model;

import android.os.Parcel;
import android.os.Parcelable;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

import java.util.List;

/**
 * Created by kit on 9/24/16.
 */
public class Floor implements Parcelable {

    @SerializedName("id")
    @Expose
    private int id;

    @SerializedName("mapPath")
    @Expose
    private String mapPath;

    @SerializedName("graphPath")
    @Expose
    private String graphPath;

    @SerializedName("maskPath")
    @Expose
    private String maskPath;

    @SerializedName("configPath")
    @Expose
    private String configPath;

    @SerializedName("buildingId")
    @Expose
    private int buildingId;

    @SerializedName("buildingTitle")
    @Expose
    private String buildingTitle;

    @SerializedName("number")
    @Expose
    private int number;

    @SerializedName("inpointIdList")
    @Expose
    private List<Integer> inpointIdList;

    @SerializedName("beaconList")
    @Expose
    private List<BeaconModel> beacons;

    @SerializedName("subtitle")
    @Expose
    private String subtitle;

    @SerializedName("width")
    @Expose
    private double width;

    @SerializedName("height")
    @Expose
    private double height;

    @SerializedName("pixelSize")
    @Expose
    private double pixelSize;


    public void setPixelSize(double pixelSize) {
        this.pixelSize = pixelSize;
    }

    public double getPixelSize() {

        return pixelSize;
    }


    public void setSubtitle(String subtitle) {
        this.subtitle = subtitle;
    }

    public String getSubtitle() {

        return subtitle;
    }

    public void setId(int id) {
        this.id = id;
    }


    public void setMapPath(String mapPath) {
        this.mapPath = mapPath;
    }

    public void setGraphPath(String graphPath) {
        this.graphPath = graphPath;
    }

    public void setMaskPath(String maskPath) {
        this.maskPath = maskPath;
    }

    public void setBuildingId(int buildingId) {
        this.buildingId = buildingId;
    }

    public void setBuildingTitle(String buildingTitle) {
        this.buildingTitle = buildingTitle;
    }

    public void setNumber(int number) {
        this.number = number;
    }

    public void setInpointIdList(List<Integer> inpointIdList) {
        this.inpointIdList = inpointIdList;
    }

    public void setBeacons(List<BeaconModel> beacons) {
        this.beacons = beacons;
    }

    public int getId() {
        return id;
    }

    public String getMapPath() {
        return mapPath;
    }

    public String getGraphPath() {
        return graphPath;
    }

    public String getMaskPath() {
        return maskPath;
    }

    public int getBuildingId() {
        return buildingId;
    }

    public String getBuildingTitle() {
        return buildingTitle;
    }

    public int getNumber() {
        return number;
    }

    public List<Integer> getInpointIdList() {
        return inpointIdList;
    }

    public List<BeaconModel> getBeacons() {
        return beacons;
    }

    public void setWidth(double width) {
        this.width = width;
    }

    public void setHeight(double height) {
        this.height = height;
    }

    public double getWidth() {
        return width;
    }

    public double getHeight() {
        return height;
    }


    public void setConfigPath(String configPath) {
        this.configPath = configPath;
    }

    public String getConfigPath() {

        return configPath;
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeInt(this.id);
        dest.writeString(this.configPath);
        dest.writeString(this.mapPath);
        dest.writeString(this.graphPath);
        dest.writeString(this.maskPath);
        dest.writeInt(this.buildingId);
        dest.writeString(this.buildingTitle);
        dest.writeInt(this.number);
        dest.writeList(this.beacons);
        dest.writeList(this.inpointIdList);
        dest.writeString(this.subtitle);
        dest.writeDouble(this.pixelSize);
        dest.writeDouble(this.width);
        dest.writeDouble(this.height);
    }

    public Floor(){}

    protected Floor(Parcel in) {
        this.id = in.readInt();
        this.configPath = in.readString();
        this.mapPath = in.readString();
        this.graphPath = in.readString();
        this.maskPath = in.readString();
        this.buildingId = in.readInt();
        this.buildingTitle = in.readString();
        this.number = in.readInt();
        this.beacons = in.readArrayList(List.class.getClassLoader());
        this.inpointIdList = in.readArrayList(List.class.getClassLoader());
        this.subtitle = in.readString();
        this.pixelSize = in.readDouble();
        this.width = in.readDouble();
        this.height = in.readDouble();
    }

    public static final Creator<Floor> CREATOR = new Creator<Floor>() {
        @Override
        public Floor createFromParcel(Parcel source) {
            return new Floor(source);
        }

        @Override
        public Floor[] newArray(int size) {
            return new Floor[size];
        }
    };

}
