package pro.i_it.indoor.dependency;

import android.content.Context;

import pro.i_it.indoor.local.beacon.BeaconManager;
import pro.i_it.indoor.local.data.DataManager;
import pro.i_it.indoor.local.gps.GPSManager;
import pro.i_it.indoor.local.wifi.WifiManager;

/**
 * Created by syn on 09.02.17.
 */

public class LocaleManager {
    private DataManager dataManager;
    private BeaconManager beaconManager;
    private WifiManager wifiManager;
    private GPSManager gpsManager;

    public BeaconManager getBeaconManager() {
        return beaconManager;
    }

    public WifiManager getWifiManager() {
        return wifiManager;
    }

    public GPSManager getGPSManager() {
        return gpsManager;
    }

    public LocaleManager(Context context) {
        dataManager = new DataManager();
        beaconManager = new BeaconManager(context);
        wifiManager = new WifiManager(context);
        gpsManager = new GPSManager(context);
    }

    public DataManager getDataManager() {
        return dataManager;
    }
}
