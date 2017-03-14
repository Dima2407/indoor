package pro.i_it.indoor.providers;

import android.annotation.SuppressLint;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.net.wifi.ScanResult;
import android.provider.Settings;
import pro.i_it.indoor.events.MeasurementEvent;

import java.util.List;

import static android.net.wifi.WifiManager.SCAN_RESULTS_AVAILABLE_ACTION;
import static android.provider.Settings.ACTION_LOCATION_SOURCE_SETTINGS;

public class WiFiMeasurementProvider extends MeasurementProvider {
    private Context context;
    private BroadcastReceiver wifiReceiver;
    private android.net.wifi.WifiManager systemWifiManager;
    private volatile boolean isRunning = false;

    public WiFiMeasurementProvider(Context context, MeasurementTransfer transfer) {
        super(transfer);
        this.context = context;
        systemWifiManager = (android.net.wifi.WifiManager) context.getSystemService(Context.WIFI_SERVICE);
        initBroadcast();
    }


    private void initBroadcast() {
        wifiReceiver = new BroadcastReceiver() {
            @Override
            public void onReceive(Context context, Intent intent) {
                if (isRunning) {
                    if (transfer != null) {
                        List<ScanResult> results = systemWifiManager.getScanResults();
                        if (results != null) {
                           for(ScanResult result : results){
                               final MeasurementEvent event = MeasurementEvent.createWiFi(result);
                               transfer.deliver(event);
                           }
                        }
                        systemWifiManager.startScan();
                    }
                }
            }
        };
    }

    @Override
    public void start() {
        checkPermission();
        startScan();
        isRunning = true;

    }

    @Override
    public void stop() {
        context.unregisterReceiver(wifiReceiver);
        isRunning = false;
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
}
