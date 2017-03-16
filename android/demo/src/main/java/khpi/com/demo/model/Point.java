package khpi.com.demo.model;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

public final class Point {

    @SerializedName("poiLongitude")
    @Expose
    private double longitude;

    @SerializedName("poiLatitude")
    @Expose
    private double latitude;
    private double altitude;

    @SerializedName("xMercator")
    @Expose
    private double mercatorX;

    @SerializedName("yMercator")
    @Expose
    private double mercatorY;

    @SerializedName("poiImage")
    @Expose
    private String imgUrl;

    @SerializedName("poiName")
    @Expose
    private String title;

    @SerializedName("poiDescription")
    @Expose
    private String description;

    @SerializedName("id")
    @Expose
    private long id;

    public double getLongitude() {
        return longitude;
    }

    public void setLongitude(double longitude) {
        this.longitude = longitude;
    }

    public double getLatitude() {
        return latitude;
    }

    public void setLatitude(double latitude) {
        this.latitude = latitude;
    }

    public double getAltitude() {
        return altitude;
    }

    public void setAltitude(double altitude) {
        this.altitude = altitude;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
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

    public String getImgUrl() {
        return imgUrl;
    }

    public void setImgUrl(String imgUrl) {
        this.imgUrl = imgUrl;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }
}
