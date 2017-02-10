package kaa_solutions.com.indoorsdk.local.permision;

import android.content.Context;

import kaa_solutions.com.indoorsdk.local.permision.interfaces.ICheckPermissionResult;
import kaa_solutions.com.indoorsdk.local.permision.interfaces.IPermissionManager;

/**
 * Created by syn on 10.02.17.
 */

public class PermissionManager implements IPermissionManager {
    private Context context;

    public PermissionManager(Context context) {
        this.context = context;

    }

    @Override
    public void checkPermission(ICheckPermissionResult callback) {

    }
}
