package khpi.com.demo.utils;

import android.location.Location;

public final class GeoUtils {

    private static final double RADIUS = 6378137.0;

    public static double convertLatitudeToMercatorY(double latitude) {
        return Math.log(Math.tan(Math.PI / 4 + Math.toRadians(latitude) / 2)) * RADIUS;
    }

    public static double convertLongitudeToMercatorX(double longitude) {
        return Math.toRadians(longitude) * RADIUS;
    }

    public static double distanceBetween(Location location1, Location location2) {
        float[] results = new float[1];

        Location.distanceBetween(location1.getLatitude(), location1.getLongitude(), location2.getLatitude(), location2.getLongitude(), results);

        return results[0];
    }
}
