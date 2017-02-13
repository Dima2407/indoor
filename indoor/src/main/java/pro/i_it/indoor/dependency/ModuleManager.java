package pro.i_it.indoor.dependency;

import android.content.Context;


/**
 * Created by syn on 09.02.17.
 */

public class ModuleManager {
    private static ModuleManager moduleManager;
    private LocaleManager localManager;


    public static ModuleManager getDefaultModuleManager() {
        return moduleManager;
    }

    public static void initDefaultModuleManager(Context context) {
        if (moduleManager == null) {
            moduleManager = new ModuleManager(context);
        }
    }

    public ModuleManager(Context context) {
        localManager = new LocaleManager(context);
    }


    public LocaleManager getLocalManager() {
        return localManager;
    }
}
