package kaa_solutions.com.indoorsdk.local.gps;

import android.Manifest;
import android.content.Context;
import android.content.pm.PackageManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;

import kaa_solutions.com.indoorsdk.local.gps.interfaces.IGPSManager;
import kaa_solutions.com.indoorsdk.local.gps.interfaces.ILocationChangeListener;
import kaa_solutions.com.indoorsdk.local.gps.model.Position;
import kaa_solutions.com.indoorsdk.ui.main.model.SettingModel;

import static android.location.LocationManager.GPS_PROVIDER;
import static kaa_solutions.com.indoorsdk.local.gps.interfaces.ProviderType.DEFAULT_GPS;
import static kaa_solutions.com.indoorsdk.local.gps.interfaces.ProviderType.DEFAULT_NETWORK;
import static kaa_solutions.com.indoorsdk.ui.main.model.SettingsType.GPS;

/**
 * Created by syn on 12.02.17.
 */

public class GPSManager implements IGPSManager {
    private ILocationChangeListener listener;
    private LocationListener locationListener;
    private LocationManager locationManager;
    private SettingModel settings;
    private Context context;

    public GPSManager(Context context) {
        locationManager = (LocationManager) context.getSystemService(Context.LOCATION_SERVICE);
        this.context = context;
        initLocations();


    }

    private void initLocations() {
        locationListener = new LocationListener() {
            @Override
            public void onLocationChanged(Location location) {
                if (listener == null) {
                    return;
                }
                listener.locationUpdate(new Position(location.getLatitude(), location.getLongitude(), location.getAltitude(), location.getProvider() == GPS_PROVIDER ? DEFAULT_GPS : DEFAULT_NETWORK));
            }

            @Override
            public void onStatusChanged(String provider, int status, Bundle extras) {

            }

            @Override
            public void onProviderEnabled(String provider) {

            }

            @Override
            public void onProviderDisabled(String provider) {

            }
        };

    }

    @Override
    public void setPositionListener(ILocationChangeListener listener) {
        this.listener = listener;
    }

    @Override
    public void updateSettings(SettingModel settings) {
        this.settings = settings;
    }

    @Override
    public void setEnable(boolean isEnable) {
        if (isEnable) {
            if (!(ActivityCompat.checkSelfPermission(context, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED && ActivityCompat.checkSelfPermission(context, Manifest.permission.ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED)) {
                locationManager.requestLocationUpdates(LocationManager.NETWORK_PROVIDER, 0, 0, locationListener);
            }
        } else {
            locationManager.removeUpdates(locationListener);
        }
        if (settings == null) {
            return;
        }
        settings.setEnable(isEnable);
    }

    @Override
    public int getSettingType() {
        return GPS;
    }
}
