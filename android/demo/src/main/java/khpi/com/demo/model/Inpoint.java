package khpi.com.demo.model;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

import java.sql.Date;

/**
 * Created by kit on 9/11/16.
 */
public class Inpoint {
    @SerializedName("id")
    @Expose
    private long id;

    @SerializedName("floorId")
    @Expose
    private long floorId;

    @SerializedName("title")
    @Expose
    private String title;

    @SerializedName("subtitle")
    @Expose
    private String subtitle;

    @SerializedName("description")
    @Expose
    private String description;

    @SerializedName("image")
    @Expose
    private String image;

    @SerializedName("hint")
    @Expose
    private String hint;

    @SerializedName("tags")
    @Expose
    private String tags;

    @SerializedName("type")
    @Expose
    private String type;

    @SerializedName("icon_id")
    @Expose
    private String icon_id;

    @SerializedName("x")
    @Expose
    private double x;

    @SerializedName("y")
    @Expose
    private double y;

    @SerializedName("near_route_x")
    @Expose
    private double near_route_x;

    @SerializedName("near_route_y")
    @Expose
    private double near_route_y;

    @SerializedName("gps_lat")
    @Expose
    private double gps_lat;

    @SerializedName("gps_lon")
    @Expose
    private double gps_lon;

    @SerializedName("gps_alt")
    @Expose
    private double gps_alt;

    @SerializedName("map_id")
    @Expose
    private long map_id;

    @SerializedName("created_at")
    @Expose
    private Date created_at;

    @SerializedName("updated_at")
    @Expose
    private Date updated_at;

    @SerializedName("floorNumber")
    @Expose
    private int floorNumber;

    @SerializedName("buildingId")
    @Expose
    private int buildingId;

    @SerializedName("buildingTitle")
    @Expose
    private String buildingTitle;

    public long getId() {
        return id;
    }

    public long getFloorId() {
        return floorId;
    }

    public String getTitle() {
        return title;
    }

    public String getSubtitle() {
        return subtitle;
    }

    public String getDescription() {
        return description;
    }

    public String getImage() {
        return image;
    }

    public String getHint() {
        return hint;
    }

    public String getTags() {
        return tags;
    }

    public String getType() {
        return type;
    }

    public String getIcon_id() {
        return icon_id;
    }

    public double getX() {
        return x;
    }

    public double getY() {
        return y;
    }

    public double getNear_route_x() {
        return near_route_x;
    }

    public double getNear_route_y() {
        return near_route_y;
    }

    public double getGps_lat() {
        return gps_lat;
    }

    public double getGps_lon() {
        return gps_lon;
    }

    public double getGps_alt() {
        return gps_alt;
    }

    public long getMap_id() {
        return map_id;
    }

    public Date getCreated_at() {
        return created_at;
    }

    public Date getUpdated_at() {
        return updated_at;
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

    public void setId(long id) {
        this.id = id;
    }

    public void setFloorId(long floorId) {
        this.floorId = floorId;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setSubtitle(String subtitle) {
        this.subtitle = subtitle;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public void setImage(String image) {
        this.image = image;
    }

    public void setHint(String hint) {
        this.hint = hint;
    }

    public void setTags(String tags) {
        this.tags = tags;
    }

    public void setType(String type) {
        this.type = type;
    }

    public void setIcon_id(String icon_id) {
        this.icon_id = icon_id;
    }

    public void setX(double x) {
        this.x = x;
    }

    public void setY(double y) {
        this.y = y;
    }

    public void setNear_route_x(double near_route_x) {
        this.near_route_x = near_route_x;
    }

    public void setNear_route_y(double near_route_y) {
        this.near_route_y = near_route_y;
    }

    public void setGps_lat(double gps_lat) {
        this.gps_lat = gps_lat;
    }

    public void setGps_lon(double gps_lon) {
        this.gps_lon = gps_lon;
    }

    public void setGps_alt(double gps_alt) {
        this.gps_alt = gps_alt;
    }

    public void setMap_id(long map_id) {
        this.map_id = map_id;
    }

    public void setCreated_at(Date created_at) {
        this.created_at = created_at;
    }

    public void setUpdated_at(Date updated_at) {
        this.updated_at = updated_at;
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
}
