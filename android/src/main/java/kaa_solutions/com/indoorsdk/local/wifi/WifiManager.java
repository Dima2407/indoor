package kaa_solutions.com.indoorsdk.local.wifi;

import android.annotation.SuppressLint;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.wifi.ScanResult;
import android.provider.Settings;

import java.util.List;

import kaa_solutions.com.indoorsdk.local.wifi.interfaces.IWifiManager;
import kaa_solutions.com.indoorsdk.local.wifi.interfaces.IWifiScanResultListener;
import kaa_solutions.com.indoorsdk.ui.main.model.SettingModel;

import static android.net.wifi.WifiManager.SCAN_RESULTS_AVAILABLE_ACTION;
import static android.provider.Settings.ACTION_LOCATION_SOURCE_SETTINGS;
import static kaa_solutions.com.indoorsdk.ui.main.model.SettingsType.WIFI;

/**
 * Created by syn on 10.02.17.
 */

public class WifiManager implements IWifiManager {
    private Context context;
    private BroadcastReceiver wifiReceiver;
    private android.net.wifi.WifiManager systemWifiManager;
    private SettingModel settingModel;
    private IWifiScanResultListener wifiScanResult;

    public WifiManager(Context context) {
        this.context = context;
        systemWifiManager = (android.net.wifi.WifiManager) context.getSystemService(Context.WIFI_SERVICE);
        initBroadcast();
    }


    private void initBroadcast() {
        wifiReceiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                if (!settingModel.isEnable()) {
                    return;
                }
                List<ScanResult> results = systemWifiManager.getScanResults();
                if (wifiScanResult != null) {
                    wifiScanResult.scanResult(results);
                }
                systemWifiManager.startScan();
            }
        };
    }

    @Override
    public void updateSettings(SettingModel settings) {
        this.settingModel = settings;
    }

    @Override
    public void setEnable(boolean isEnable) {
        settingModel.setEnable(isEnable);
        if (isEnable) {
            checkPermission();
            startScan();
        } else {
            stopScan();
        }
    }

    private void stopScan() {
        context.unregisterReceiver(wifiReceiver);
    }

    @SuppressLint("ServiceCast")
    private void startScan() {
        if (!systemWifiManager.isWifiEnabled()) {
            systemWifiManager.setWifiEnabled(true);
        }
        context.registerReceiver(wifiReceiver, new IntentFilter(SCAN_RESULTS_AVAILABLE_ACTION));
        systemWifiManager.startScan();
    }

    private void checkPermission() {
        String provider = Settings.Secure.getString(context.getContentResolver(), Settings.Secure.LOCATION_PROVIDERS_ALLOWED);
        if (!provider.contains("gps")) { //if gps is disabled
            context.startActivity(new Intent(ACTION_LOCATION_SOURCE_SETTINGS));
        }
    }


    @Override
    public int getSettingType() {
        return WIFI;
    }

    @Override
    public void setWifiScanResultListener(IWifiScanResultListener wifiScanResult) {
        this.wifiScanResult = wifiScanResult;
    }
}
