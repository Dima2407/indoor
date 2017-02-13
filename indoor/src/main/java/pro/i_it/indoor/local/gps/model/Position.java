package pro.i_it.indoor.local.gps.model;

import pro.i_it.indoor.local.gps.interfaces.ProviderType;

/**
 * Created by syn on 12.02.17.
 */

public class Position {
    @ProviderType
    private int providerType;
    private double lat;
    private double lng;
    private double alt;

    public Position(double latitude, double longitude, double altitude, @ProviderType int providerType) {
        this.providerType = providerType;
        lat = latitude;
        lng = longitude;
        alt = altitude;
    }

    @ProviderType
    public int getProviderType() {
        return providerType;
    }

    public void setProviderType(@ProviderType int providerType) {
        this.providerType = providerType;
    }

    public double getLat() {
        return lat;
    }

    public void setLat(double lat) {
        this.lat = lat;
    }

    public double getLng() {
        return lng;
    }

    public void setLng(double lng) {
        this.lng = lng;
    }

    public double getAlt() {
        return alt;
    }

    public void setAlt(double alt) {
        this.alt = alt;
    }
}
