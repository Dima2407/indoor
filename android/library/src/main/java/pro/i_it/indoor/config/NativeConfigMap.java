package pro.i_it.indoor.config;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

import pro.i_it.indoor.masks.MaskTableFetcher;

public class NativeConfigMap {

    public static final String KEY_MESH_N_X = "mesh_nx";
    public static final String KEY_MESH_N_Y = "mesh_ny";
    public static final String KEY_MESH_D_X = "mesh_dx";
    public static final String KEY_MESH_D_Y = "mesh_dy";
    public static final String KEY_MESH_X_0 = "mesh_x0";
    public static final String KEY_MESH_Y_0 = "mesh_y0";
    public static final String KEY_MASK = "mask";

    public static final String KEY_MAP_ANGLE = "map_angle";
    public static final String KEY_USE_MASK = "use_mask";
    public static final String KEY_USE_BEACONS = "use_beacons";
    public static final String KEY_USE_SENSORS = "use_sensors";
    public static final String KEY_INIT_X = "x0";
    public static final String KEY_INIT_Y = "y0";
    public static final String KEY_BEACONS = "beacons";

    private final Map<String, Object> configs = new HashMap<>();

    public float getFloat(String key) {
        return (float) configs.get(key);
    }

    public int getInt(String key) {
        return (int) configs.get(key);
    }
    public double getDouble(String key) {
        return (double) configs.get(key);
    }

    public boolean getBoolean(String key){
        return (boolean)configs.get(key);
    }
    public String getString(String key) {
        return (String) configs.get(key);
    }

    public int[] getIntArray(String key) {
        return (int[]) configs.get(key);
    }

    public Object[] getObjectArray(String key) {
        return (Object[]) configs.get(key);
    }

    public void set(String key, Object o) {
        configs.put(key, o);
    }

    public void set(String key, MaskTableFetcher fetcher) {
        configs.put(key, fetcher.fetchMaskTable());
    }

    public void set(String key, Collection<?> items){
        configs.put(key, items.toArray());
    }

}
