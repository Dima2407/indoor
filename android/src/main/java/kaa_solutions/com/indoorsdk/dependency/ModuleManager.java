package kaa_solutions.com.indoorsdk.dependency;

import android.content.Context;

import kaa_solutions.com.indoorsdk.dependency.interfaces.ILocalManager;
import kaa_solutions.com.indoorsdk.dependency.interfaces.IModuleManager;

/**
 * Created by syn on 09.02.17.
 */

public class ModuleManager implements IModuleManager {
    private static ModuleManager moduleManager;
    private ILocalManager localManager;


    public static ModuleManager getDefaultModuleManager() {
        return moduleManager;
    }

    public static void initDefaultModuleManager(Context context){
        if (moduleManager == null) {
            moduleManager = new ModuleManager(context);
        }
    }

    public ModuleManager(Context context) {
        localManager = new LocaleManager(context);
    }

    @Override
    public ILocalManager getLocalManager() {
        return localManager;
    }
}
