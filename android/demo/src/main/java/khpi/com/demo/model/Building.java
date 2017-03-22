package khpi.com.demo.model;

import android.os.Parcel;
import android.os.Parcelable;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

import java.sql.Date;
import java.util.List;

/**
 * Created by kit on 9/24/16.
 */
public class Building implements Parcelable {

    @SerializedName("id")
    @Expose
    private long id;

    @SerializedName("title")
    @Expose
    private String title;

    @SerializedName("subtitle")
    @Expose
    private String subtitle;

    @SerializedName("floor_list")
    @Expose
    private List<Floor> floors;

    @SerializedName("poi_id")
    @Expose
    private long outpointId;

    @SerializedName("poi_name")
    @Expose
    private String poiName;

    @SerializedName("created_at")
    @Expose
    private Date created_at;

    @SerializedName("updated_at")
    @Expose
    private Date updated_at;

    @SerializedName("beacon_mac_list")
    @Expose
    private List<String> beacon_list;

    private int currentFloorIndex;

    public List<Floor> getFloors(){
        return floors;
    }

    public void setFloors(List<Floor> floors){
        this.floors = floors;
    }

    public Building() {
    }

    public void setCurrentFloorIndex(final int currentFloorIndex) {
        this.currentFloorIndex = currentFloorIndex;
    }

    public int getCurrentFloorIndex() {
        return currentFloorIndex;
    }

    public void setId(long id) {
        this.id = id;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setSubtitle(String subtitle) {
        this.subtitle = subtitle;
    }

    public void setOutpointId(long outpointId) {
        this.outpointId = outpointId;
    }

    public void setPoiName(String poiName) {
        this.poiName = poiName;
    }

    public void setCreated_at(Date created_at) {
        this.created_at = created_at;
    }

    public void setUpdated_at(Date updated_at) {
        this.updated_at = updated_at;
    }

    public void setBeacon_list(List<String> beacon_list) {
        this.beacon_list = beacon_list;
    }

    public long getId() {
        return id;
    }

    public String getTitle() {
        return title;
    }

    public String getSubtitle() {
        return subtitle;
    }

    public long getOutpointId() {
        return outpointId;
    }

    public String getPoiName() {
        return poiName;
    }

    public Date getCreated_at() {
        return created_at;
    }

    public Date getUpdated_at() {
        return updated_at;
    }

    public List<String> getBeacon_list() {
        return beacon_list;
    }

    @Override
    public int describeContents() {
        return 0;
    }

    @Override
    public void writeToParcel(Parcel dest, int flags) {
        dest.writeLong(this.id);
        dest.writeString(this.title);
        dest.writeString(this.subtitle);
        dest.writeTypedList(getFloors());
        dest.writeLong(this.outpointId);
        dest.writeString(this.poiName);
        dest.writeSerializable(this.created_at);
        dest.writeSerializable(this.updated_at);
        dest.writeList(this.beacon_list);
        dest.writeInt(this.currentFloorIndex);
    }

    protected Building(Parcel in) {
        this.id = in.readLong();
        this.title = in.readString();
        this.subtitle = in.readString();
        setFloors(in.createTypedArrayList(Floor.CREATOR));
        this.outpointId = in.readLong();
        this.poiName = in.readString();
        this.created_at = (Date) in.readSerializable();
        this.updated_at = (Date) in.readSerializable();
        this.beacon_list = in.readArrayList(List.class.getClassLoader());
        this.currentFloorIndex = in.readInt();
    }

    public static final Creator<Building> CREATOR = new Creator<Building>() {
        @Override
        public Building createFromParcel(Parcel source) {
            return new Building(source);
        }

        @Override
        public Building[] newArray(int size) {
            return new Building[size];
        }
    };
}
