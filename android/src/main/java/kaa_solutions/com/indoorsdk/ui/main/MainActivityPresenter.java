package kaa_solutions.com.indoorsdk.ui.main;

import android.Manifest;
import android.net.wifi.ScanResult;
import android.support.v4.app.ActivityCompat;
import android.util.Log;

import org.altbeacon.beacon.Beacon;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;

import kaa_solutions.com.indoorsdk.dependency.ModuleManager;
import kaa_solutions.com.indoorsdk.dependency.interfaces.ILocalManager;
import kaa_solutions.com.indoorsdk.local.beacon.interfaces.IOnBeaconListener;
import kaa_solutions.com.indoorsdk.local.gps.interfaces.ILocationChangeListener;
import kaa_solutions.com.indoorsdk.local.gps.model.Position;
import kaa_solutions.com.indoorsdk.local.interfaces.IBaseSetting;
import kaa_solutions.com.indoorsdk.local.wifi.interfaces.IWifiScanResultListener;
import kaa_solutions.com.indoorsdk.ui.main.interfaces.IMainActivity;
import kaa_solutions.com.indoorsdk.ui.main.interfaces.IMainActivityPresenter;
import kaa_solutions.com.indoorsdk.ui.main.interfaces.IOnChangeSettingListener;
import kaa_solutions.com.indoorsdk.ui.main.model.SettingModel;

import static kaa_solutions.com.indoorsdk.config.DebugConfig.IS_DEBUG;
import static kaa_solutions.com.indoorsdk.config.DebugConfig.MAIN_ACTIVITY_DEBUG;
import static kaa_solutions.com.indoorsdk.config.DebugConfig.WIFI_IS_DEBUG;

/**
 * Created by syn on 09.02.17.
 */

public class MainActivityPresenter implements IMainActivityPresenter, IOnChangeSettingListener {
    private static final String TAG = MainActivityPresenter.class.getSimpleName();
    private IMainActivity view;
    private ILocalManager localManager;
    private HashMap<Integer, IBaseSetting> settingHashMap;

    @Override

    public void init(IMainActivity view) {
        this.view = view;
        localManager = ModuleManager.getDefaultModuleManager().getLocalManager();
        localManager.getBeaconManager();
        ArrayList<SettingModel> settingModels = localManager
                .getDataManager()
                .getSettingList();
        initSettings();
        updateSettings(settingModels);
        view.setOnChangeConfig(this);
        view.updateData(settingModels);
    }

    private void initSettings() {
        ActivityCompat.requestPermissions(view.getActivity(),
                new String[]{Manifest.permission.ACCESS_COARSE_LOCATION},
                0);

        settingHashMap = new HashMap<>();
        settingHashMap.put(localManager.getBeaconManager().getSettingType(), localManager.getBeaconManager());
        settingHashMap.put(localManager.getWifiManager().getSettingType(), localManager.getWifiManager());
        settingHashMap.put(localManager.getGPSManager().getSettingType(), localManager.getGPSManager());

        localManager.getBeaconManager().setOnBeaconListener(new IOnBeaconListener() {
            @Override
            public void beaconUpdate(Collection<Beacon> beacons) {
                if (IS_DEBUG && MAIN_ACTIVITY_DEBUG) {
                    Log.d(TAG, "beaconUpdate: ");
                    for (Beacon beacon : beacons) {
                        Log.d(TAG, "didRangeBeaconsInRegion: " + beacon.toString());
                    }
                }

            }
        });

        localManager.getWifiManager().setWifiScanResultListener(new IWifiScanResultListener() {
            @Override
            public void scanResult(List<ScanResult> results) {
                if (IS_DEBUG && WIFI_IS_DEBUG) {
                    for (ScanResult result : results) {
                        Log.d(TAG, "onReceive: BSSID: " + result.BSSID + " SSID:" + result.SSID + " level:" + result.level);
                    }
                }
            }
        });
        localManager.getGPSManager().setPositionListener(new ILocationChangeListener() {
            @Override
            public void locationUpdate(Position position) {
                Log.d(TAG, "locationUpdate: x:"+position.getLat()+ " y:"+position.getLng());
            }
        });

    }

    private void updateSettings(ArrayList<SettingModel> settingModels) {
        for (SettingModel settingModel : settingModels) {
            if (settingHashMap.containsKey(settingModel.getConfigType())) {
                settingHashMap.get(settingModel.getConfigType()).updateSettings(settingModel);
            }
        }
    }

    @Override
    public void onChange(SettingModel settingModel) {
        if (settingHashMap.containsKey(settingModel.getConfigType())) {
            settingHashMap.get(settingModel.getConfigType()).setEnable(settingModel.isEnable());
        }
    }
}
