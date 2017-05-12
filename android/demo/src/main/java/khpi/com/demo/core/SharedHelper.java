package khpi.com.demo.core;

import android.content.Context;
import android.content.SharedPreferences;

public final class SharedHelper {
    private static final String SHARED_NAME = "shared";
    private static final String USE_PRODUCTION = "use production";
    private static final String DRAW_IN_RADAR = "in radar";
    private static final String USE_BINARY_MASK = "use standard beacon navigator";

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

    public void setUseBinaryMask(boolean useBinaryMask){
        sharedPreferences.edit().putBoolean(USE_BINARY_MASK, useBinaryMask).apply();
    }

    public boolean useBinaryMask(){
        return sharedPreferences.getBoolean(USE_BINARY_MASK, false);
    }
}
