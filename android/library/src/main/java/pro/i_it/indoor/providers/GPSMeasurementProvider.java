package pro.i_it.indoor.providers;

import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageManager;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import pro.i_it.indoor.events.MeasurementEvent;

import static android.Manifest.permission.ACCESS_COARSE_LOCATION;
import static android.Manifest.permission.ACCESS_FINE_LOCATION;

public class GPSMeasurementProvider extends MeasurementProvider {
    private LocationListener locationListener;
    private LocationManager locationManager;
    private Context context;
    private volatile boolean isRunning = false;
    private final static int REQUEST_CODE = 10;

    public GPSMeasurementProvider(Context context, MeasurementTransfer transfer) {
        super(transfer);
        locationManager = (LocationManager) context.getSystemService(Context.LOCATION_SERVICE);
        this.context = context;
        initLocations();
    }

    private void initLocations() {
        locationListener = new LocationListener() {
            @Override
            public void onLocationChanged(Location location) {
                if (transfer != null) {
                    final MeasurementEvent event = MeasurementEvent.createGPS(location.getLatitude(), location.getLongitude());
                    transfer.deliver(event);
                }
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
    public void start() {
        if (!isRunning) {
            if (!(ActivityCompat.checkSelfPermission(context, ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED &&
                    ActivityCompat.checkSelfPermission(context, ACCESS_COARSE_LOCATION) != PackageManager.PERMISSION_GRANTED)) {
                locationManager.requestLocationUpdates(LocationManager.NETWORK_PROVIDER, 0, 0, locationListener);
            }else {
                ActivityCompat.requestPermissions((Activity) context, new String[]{ACCESS_COARSE_LOCATION, ACCESS_FINE_LOCATION},
                        REQUEST_CODE);
            }
        }
        isRunning = true;
    }

    @Override
    public void stop() {
        if (isRunning) {
            locationManager.removeUpdates(locationListener);
        }
        isRunning = false;
    }

}
