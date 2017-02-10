package kaa_solutions.com.indoorsdk.local.data;

import java.util.ArrayList;

import kaa_solutions.com.indoorsdk.local.beacon.model.BeaconManagerConfig;
import kaa_solutions.com.indoorsdk.local.data.interfaces.IDataManager;
import kaa_solutions.com.indoorsdk.ui.main.model.SettingModel;
import kaa_solutions.com.indoorsdk.ui.main.model.SettingsType;

/**
 * Created by syn on 09.02.17.
 */

public class DataManager implements IDataManager {


    @Override
    public ArrayList<SettingModel> getSettingList() {
        ArrayList<SettingModel> settingModels = new ArrayList<>();

        SettingModel wifiSetting = new SettingModel();
        wifiSetting.setEnable(false);
        wifiSetting.setConfigType(SettingsType.WIFI);
        wifiSetting.setLable("Wifi");
        settingModels.add(wifiSetting);

        BeaconManagerConfig beaconManagerConfig = new BeaconManagerConfig();
        beaconManagerConfig.setEnable(false);
        beaconManagerConfig.setConfigType(SettingsType.BEACON);
        beaconManagerConfig.setLable("Beacon");
        settingModels.add(beaconManagerConfig);

        SettingModel gpsSetting = new SettingModel();
        gpsSetting.setEnable(false);
        gpsSetting.setConfigType(SettingsType.GPS);
        gpsSetting.setLable("GPS");
        settingModels.add(gpsSetting);


        return settingModels;
    }
}
