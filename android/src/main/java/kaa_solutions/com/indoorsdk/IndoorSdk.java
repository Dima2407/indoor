package kaa_solutions.com.indoorsdk;

import android.content.Context;

import kaa_solutions.com.indoorsdk.dependency.ModuleManager;

/**
 * Created by syn on 09.02.17.
 */

public class IndoorSdk {
    public static void initIndoorSdk(Context context) {
        ModuleManager.initDefaultModuleManager(context);
    }
}
