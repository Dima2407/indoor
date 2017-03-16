package khpi.com.demo.model;

import android.graphics.PointF;
import android.os.Parcel;
import android.os.Parcelable;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

public class BeaconModel implements Parcelable {

    @SerializedName("x")
    @Expose
    private float positionX;

    @SerializedName("y")
    @Expose
    private float positionY;

    @SerializedName("z")
    @Expose
    private float positionZ;

    @Expose
    @SerializedName("macAddress")
    private String macAddress;

    @SerializedName("major")
    @Expose
    private int major;

    @SerializedName("minor")
    @Expose
    private int minor;

    @Expose
    @SerializedName("damp")
    private float damp;

    @Expose
    @SerializedName("floorId")
    private int floorId;

    @Expose
    @SerializedName("floorNumber")
    private int floorNumber;

    @Expose
    @SerializedName("buildingId")
    private int buildingId;

    @Expose
    @SerializedName("buildingTitle")
    private String buildingTitle;

    public BeaconModel() {
    }

    public BeaconModel(BeaconModel beaconModel) {
        macAddress = beaconModel.getMacAddress();
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

    public void setPositionX(float positionX) {
        this.positionX = positionX;
    }

    public void setPositionY(float positionY) {
        this.positionY = positionY;
    }

    public void setPositionZ(float positionZ) {
        this.positionZ = positionZ;
    }

    public void setFloorId(int floorId) {
        this.floorId = floorId;
    }

    public void setFloorNumber(int floorNumber) {
        this.floorNumber = floorNumber;
    }

    public void setBuildingId(int buildingId) {
        this.buildingId = buildingId;
    }

    public void setBuildingTitle(String buildingTitle) {
        this.buildingTitle = buildingTitle;
    }

    public float getPositionX() {
        return positionX;
    }

    public float getPositionY() {
        return positionY;
    }

    public float getPositionZ() {
        return positionZ;
    }

    public int getFloorId() {
        return floorId;
    }

    public int getFloorNumber() {
        return floorNumber;
    }

    public int getBuildingId() {
        return buildingId;
    }

    public String getBuildingTitle() {
        return buildingTitle;
    }

    public float getDamp() {
        return damp;
    }

    public void setDamp(float damp) {
        this.damp = damp;
    }

    public void setMajor(int major) {
        this.major = major;
    }

    public void setMinor(int minor) {
        this.minor = minor;
    }

    public int getMajor(){
        return major;
    }

    public int getMinor(){
        return minor;
    }



    @Override
    public String toString() {
        return "BeaconModel{" +
                ", positionX=" + positionX +
                ", positionY=" + positionY +
                ", macAddress='" + macAddress +
                '}';
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel parcel, int i) {
        parcel.writeString(macAddress);
        parcel.writeFloat(positionX);
        parcel.writeFloat(positionY);
        parcel.writeFloat(positionZ);
        parcel.writeFloat(damp);
        parcel.writeInt(major);
        parcel.writeInt(minor);
        parcel.writeInt(floorId);
        parcel.writeInt(floorNumber);
        parcel.writeInt(buildingId);
        parcel.writeString(buildingTitle);
    }

    private BeaconModel(Parcel parcel) {
        macAddress = parcel.readString();
        positionX = parcel.readFloat();
        positionY = parcel.readFloat();
        positionZ = parcel.readFloat();
        damp = parcel.readFloat();
        major = parcel.readInt();
        minor = parcel.readInt();
        floorId = parcel.readInt();
        floorNumber = parcel.readInt();
        buildingId = parcel.readInt();
        buildingTitle = parcel.readString();
    }

    public static Creator<BeaconModel> CREATOR = new Creator<BeaconModel>() {
        @Override
        public BeaconModel createFromParcel(Parcel parcel) {
            return new BeaconModel(parcel);
        }

        @Override
        public BeaconModel[] newArray(int i) {
            return new BeaconModel[i];
        }
    };

    public PointF getPosition(float pixelSize) {
        return new PointF(positionX/pixelSize, positionY/pixelSize
        );
    }


}
