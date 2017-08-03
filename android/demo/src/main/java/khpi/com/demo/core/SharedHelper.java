package khpi.com.demo.core;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.PointF;
import android.text.TextUtils;

public final class SharedHelper {

    public static final int MODE_BLE = 1;
    public static final int MODE_SENSORS = 2;
    public static final int MODE_MIXIN = 3;

    public static final int SUB_MODE_BLE_1 = 1;
    public static final int SUB_MODE_BLE_2 = 2;

    public static final int SUB_MODE_SENSORS_1 = 1;
    public static final int SUB_MODE_SENSORS_2 = 2;
    public static final int SUB_MODE_SENSORS_3 = 3;

    private static final String SHARED_NAME = "shared";
    private static final String USE_PRODUCTION = "use production";
    private static final String DRAW_IN_RADAR = "in radar";
    private static final String ACTIVE_MODE = "active mode";
    private static final String ACTIVE_BLE_MODE = "active ble mode";
    private static final String ACTIVE_SENSORS_MODE = "active sensors mode";
    private static final String X_POSITION = "x position";
    private static final String Y_POSITION = "y position";
    private static final String MAP_CORRECTION = "map correction";
    private static final String MESH_CORRECTION = "mesh correction";
    private static final String WALLS_CORRECTION = "walls correction";

    private static final String MULTI_LATERATION_ENABLED = "multi lateration enabled";

    private final SharedPreferences sharedPreferences;

    SharedHelper(Context context) {
        sharedPreferences = context.getSharedPreferences(SHARED_NAME, Context.MODE_PRIVATE);
    }

    public boolean useProduction() {
        return sharedPreferences.getBoolean(USE_PRODUCTION, false);
    }

    public void setUseProduction(boolean useProduction) {
        sharedPreferences.edit().putBoolean(USE_PRODUCTION, useProduction).apply();
    }

    public boolean containsProductionFlag() {
        return sharedPreferences.contains(USE_PRODUCTION);
    }

    public boolean drawInRadar() {
        return sharedPreferences.getBoolean(DRAW_IN_RADAR, false);
    }

    public void setDrawInRadar(boolean b) {
        sharedPreferences.edit().putBoolean(DRAW_IN_RADAR, b).apply();
    }

    public int getActiveModeKey() {
        return sharedPreferences.getInt(ACTIVE_MODE, 0);
    }

    public void setActiveModeKey(int activeModeKey) {
        sharedPreferences.edit()
                .putInt(ACTIVE_MODE, activeModeKey)
                .apply();
    }

    public void setInitPosition(String x, String y) {
        if (TextUtils.isEmpty(x)) {
            x = "0.0";
        }
        if (TextUtils.isEmpty(y)) {
            y = "0.0";
        }
        sharedPreferences.edit()
                .putFloat(X_POSITION, Float.parseFloat(x))
                .putFloat(Y_POSITION, Float.parseFloat(y))
                .apply();
    }

    public PointF getInitPosition() {
        return new PointF(sharedPreferences.getFloat(X_POSITION, 0),
                sharedPreferences.getFloat(Y_POSITION, 0));
    }

    public int getBLESubMode() {
        return sharedPreferences.getInt(ACTIVE_BLE_MODE, 1);
    }

    public void setBLESubMode(int value) {
        sharedPreferences.edit()
                .putInt(ACTIVE_BLE_MODE, value)
                .apply();
    }

    public int getSensorsSubMode() {
        return sharedPreferences.getInt(ACTIVE_SENSORS_MODE, 1);
    }

    public void setSensorsSubMode(int value) {
        sharedPreferences.edit()
                .putInt(ACTIVE_SENSORS_MODE, value)
                .apply();
    }

    public boolean useMapCoordinateCorrection() {
        return sharedPreferences.getBoolean(MAP_CORRECTION, false);
    }


    public void setMapCoordinateCorrection(boolean value) {
        sharedPreferences.edit().putBoolean(MAP_CORRECTION, value).apply();
    }

    public boolean useMeshCoordinateCorrection() {
        return sharedPreferences.getBoolean(MESH_CORRECTION, false);
    }

    public void setMeshCoordinateCorrection(boolean value) {
        sharedPreferences.edit().putBoolean(MESH_CORRECTION, value).apply();
    }

    public boolean useWallCoordinateCorrection() {
        return sharedPreferences.getBoolean(WALLS_CORRECTION, false);
    }

    public void setWallCoordinateCorrection(boolean value) {
        sharedPreferences.edit().putBoolean(WALLS_CORRECTION, value).apply();
    }

    public boolean isMultiLaterationEnabled() {
        return sharedPreferences.getBoolean(MULTI_LATERATION_ENABLED, false);
    }

    public void setMultiLaterationEnabled(boolean enabled) {
        sharedPreferences.edit().putBoolean(MULTI_LATERATION_ENABLED, enabled).apply();
    }
}
