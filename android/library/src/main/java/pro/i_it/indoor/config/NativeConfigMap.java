package pro.i_it.indoor.config;

import android.util.Log;
import android.util.SparseArray;

import java.util.Collection;

import pro.i_it.indoor.masks.MaskTableFetcher;

public class NativeConfigMap {

    private static final String TAG = NativeConfigMap.class.getSimpleName();

    public static final int KEY_MESH_N_X = 0;
    public static final int KEY_MESH_N_Y = 1;
    public static final int KEY_MESH_D_X = 2;
    public static final int KEY_MESH_D_Y = 3;
    public static final int KEY_MESH_X_0 = 4;
    public static final int KEY_MESH_Y_0 = 5;
    public static final int KEY_MASK = 6;

    public static final int KEY_MAP_ANGLE = 7;
    public static final int KEY_USE_MASK = 8;
    public static final int KEY_USE_BEACONS = 9;
    public static final int KEY_USE_SENSORS = 10;
    public static final int KEY_INIT_X = 11;
    public static final int KEY_INIT_Y = 12;
    public static final int KEY_BEACONS = 13;

    public static final int KEY_GRAPH_PATH = 14;
    public static final int KEY_GRAPH_SCALE = 15;

    public static final int KEY_USE_FILTER = 16;
    public static final int KEY_USE_MAP_EDGES = 17;
    public static final int KEY_USE_MESH_MASK = 18;
    public static final int KEY_USE_WALLS = 19;
    public static final int KEY_ACTIVE_BLE_MODE = 20;

    public static final int KEY_MULTI_LATERATION = 21;

    public static final int KEY_PARTICLE_ENABLED = 22;

    public static final int KEY_USE_KALMAN_FILTER = 23;

    private final SparseArray<Object> configs = new SparseArray<>();

    public float getFloat(int key) {
        float value = getInternalFloat(key);
        Log.d(TAG, "get: " + getStringKey(key) + " " + value);
        return value;
    }

    private String getStringKey(int key) {
        switch (key) {
            case KEY_MESH_N_X:
                return "KEY_MESH_N_X";
            case KEY_MESH_N_Y:
                return "KEY_MESH_N_Y";
            case KEY_MESH_D_X:
                return "KEY_MESH_D_X";
            case KEY_MESH_D_Y:
                return "KEY_MESH_D_Y";
            case KEY_MESH_X_0:
                return "KEY_MESH_X_0";
            case KEY_MESH_Y_0:
                return "KEY_MESH_Y_0";
            case KEY_MASK:
                return "KEY_MASK";

            case KEY_MAP_ANGLE:
                return "KEY_MAP_ANGLE";
            case KEY_USE_MASK:
                return "KEY_USE_MASK";
            case KEY_USE_BEACONS:
                return "KEY_USE_BEACONS";
            case KEY_USE_SENSORS:
                return "KEY_USE_SENSORS";
            case KEY_INIT_X:
                return "KEY_INIT_X";
            case KEY_INIT_Y:
                return "KEY_INIT_Y";
            case KEY_BEACONS:
                return "KEY_BEACONS";

            case KEY_GRAPH_PATH:
                return "KEY_GRAPH_PATH";
            case KEY_GRAPH_SCALE:
                return "KEY_GRAPH_SCALE";

            case KEY_USE_FILTER:
                return "KEY_USE_FILTER";
            case KEY_USE_MAP_EDGES:
                return "KEY_USE_MAP_EDGES";
            case KEY_USE_MESH_MASK:
                return "KEY_USE_MESH_MASK";
            case KEY_USE_WALLS:
                return "KEY_USE_WALLS";
            case KEY_ACTIVE_BLE_MODE:
                return "KEY_ACTIVE_BLE_MODE";

            case KEY_MULTI_LATERATION:
                return "KEY_MULTI_LATERATION";

            case KEY_PARTICLE_ENABLED:
                return "KEY_PARTICLE_ENABLED";

            case KEY_USE_KALMAN_FILTER:
                return "KEY_USE_KALMAN_FILTER";
        }
        return "undefined";
    }

    public int getInt(int key) {
        int value = getInternalInt(key);
        Log.d(TAG, "get: " + getStringKey(key) + " " + value);
        return value;
    }

    public double getDouble(int key) {
        double value = getInternalDouble(key);
        Log.d(TAG, "get: " + getStringKey(key) + " " + value);
        return value;
    }

    public boolean getBoolean(int key) {
        boolean value = getInternalBoolean(key);
        Log.d(TAG, "get: "+ getStringKey(key) + " " + value);
        return value;
    }

    public Object getObject(int key) {
        Object value = configs.get(key);
        Log.d(TAG, "get: "+ getStringKey(key) + " " + value);
        return value;
    }

    public void set(int key, Object o) {
        configs.put(key, o);
    }

    public void set(int key, MaskTableFetcher fetcher) {
        configs.put(key, fetcher.fetchMaskTable());
    }

    public void set(int key, Collection<?> items) {
        configs.put(key, items.toArray());
    }


    private float getInternalFloat(int key) {
        Object o = configs.get(key);
        if (o instanceof Float) {
            return (float) o;
        }
        return Float.NaN;
    }

    private int getInternalInt(int key) {
        Object o = configs.get(key);
        if (o instanceof Integer) {
            return (int) o;
        }
        return -1;
    }

    private double getInternalDouble(int key) {
        Object o = configs.get(key);
        if (o instanceof Double) {
            double o1 = (double) o;
            return o1;
        }
        return Double.NaN;
    }

    private boolean getInternalBoolean(int key) {
        Object o = configs.get(key);
        return o instanceof Boolean && (boolean) o;
    }
}
