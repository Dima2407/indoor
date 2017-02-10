package kaa_solutions.com.indoorsdk.local.wifi;

import android.content.Context;

import kaa_solutions.com.indoorsdk.local.wifi.interfaces.IWifiManager;
import kaa_solutions.com.indoorsdk.ui.main.model.SettingModel;

/**
 * Created by syn on 10.02.17.
 */

public class WifiManager implements IWifiManager {
    private Context context;

    public WifiManager(Context context) {
        this.context = context;
    }

    @Override
    public void updateSettings(SettingModel settings) {

    }

    @Override
    public void setEnable(boolean isEnable) {
        startScan();


    }

    private void startScan() {
        checkPermission();
    }

    private void checkPermission() {

    }

    @Override
    public int getSettingType() {
        return 0;
    }
}
