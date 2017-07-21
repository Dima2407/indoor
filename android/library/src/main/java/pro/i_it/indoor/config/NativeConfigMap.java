package pro.i_it.indoor.config;

import android.util.SparseArray;

import java.util.Collection;

import pro.i_it.indoor.masks.MaskTableFetcher;

public class NativeConfigMap {

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
    public static final int KEY_USE_SENSORS =10;
    public static final int KEY_INIT_X = 11;
    public static final int KEY_INIT_Y = 12;
    public static final int KEY_BEACONS = 13;

    public static final int KEY_GRAPH_PATH = 14;
    public static final int KEY_GRAPH_SCALE = 15;

    private final SparseArray<Object> configs = new SparseArray<>();

    public float getFloat(int key) {
        Object o = configs.get(key);
        if(o instanceof Float){
            return (float) o;
        }
        return Float.NaN;
    }

    public int getInt(int key) {
        Object o = configs.get(key);
        if(o instanceof Integer){
            return (int) o;
        }
        return -1;
    }
    public double getDouble(int key) {
        Object o = configs.get(key);
        if(o instanceof Double){
            double o1 = (double) o;
            return o1;
        }
        return Double.NaN;
    }

    public boolean getBoolean(int key) {
        Object o = configs.get(key);
        return o instanceof Boolean && (boolean) o;
    }

    public Object getObject(int key) {
        return configs.get(key);
    }

    public void set(int key, Object o) {
        configs.put(key, o);
    }

    public void set(int key, MaskTableFetcher fetcher) {
        configs.put(key, fetcher.fetchMaskTable());
    }

    public void set(int key, Collection<?> items){
        configs.put(key, items.toArray());
    }

}
