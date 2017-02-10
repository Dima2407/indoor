package kaa_solutions.com.indoorsdk.dependency;

import android.content.Context;

import kaa_solutions.com.indoorsdk.dependency.interfaces.ILocalManager;
import kaa_solutions.com.indoorsdk.local.beacon.BeaconManage;
import kaa_solutions.com.indoorsdk.local.beacon.interfaces.IBeaconManager;
import kaa_solutions.com.indoorsdk.local.data.DataManager;
import kaa_solutions.com.indoorsdk.local.data.interfaces.IDataManager;
import kaa_solutions.com.indoorsdk.local.permision.PermissionManager;
import kaa_solutions.com.indoorsdk.local.permision.interfaces.IPermissionManager;
import kaa_solutions.com.indoorsdk.local.wifi.WifiManager;
import kaa_solutions.com.indoorsdk.local.wifi.interfaces.IWifiManager;

/**
 * Created by syn on 09.02.17.
 */

public class LocaleManager implements ILocalManager {
    private IDataManager dataManager;
    private IBeaconManager beaconManager;
    private IWifiManager wifiManager;
    private IPermissionManager permissionManager;

    @Override
    public IBeaconManager getBeaconManager() {
        return beaconManager;
    }

    public LocaleManager(Context context) {
        dataManager = new DataManager();
        beaconManager = new BeaconManage(context);
        wifiManager = new WifiManager(context);
        permissionManager = new PermissionManager(context);
    }

    @Override
    public IDataManager getDataManager() {
        return dataManager;
    }
}
