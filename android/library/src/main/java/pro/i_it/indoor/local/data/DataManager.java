package pro.i_it.indoor.local.data;

import java.util.ArrayList;

import pro.i_it.indoor.local.beacon.model.BeaconManagerConfig;
import pro.i_it.indoor.model.SettingModel;
import pro.i_it.indoor.model.SettingsType;

/**
 * Created by syn on 09.02.17.
 */

public class DataManager {


    public static ArrayList<SettingModel> getSettingList() {
        ArrayList<SettingModel> settingModels = new ArrayList<>();

        SettingModel wifiSetting = new SettingModel();
        wifiSetting.setEnable(false);
        wifiSetting.setConfigType(SettingsType.WIFI);
        wifiSetting.setLabel("Wifi");
        settingModels.add(wifiSetting);

        BeaconManagerConfig beaconManagerConfig = new BeaconManagerConfig();
        beaconManagerConfig.setEnable(false);
        beaconManagerConfig.setConfigType(SettingsType.BEACON);
        beaconManagerConfig.setLabel("Beacon");
        settingModels.add(beaconManagerConfig);

        SettingModel gpsSetting = new SettingModel();
        gpsSetting.setEnable(false);
        gpsSetting.setConfigType(SettingsType.GPS);
        gpsSetting.setLabel("GPS");
        settingModels.add(gpsSetting);


        return settingModels;
    }
}
