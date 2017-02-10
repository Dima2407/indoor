package kaa_solutions.com.indoorsdk.local.beacon.model;

import kaa_solutions.com.indoorsdk.ui.main.model.SettingModel;

/**
 * Created by syn on 09.02.17.
 */

public class BeaconManagerConfig extends SettingModel {
    private AltBeaconConfigModel configModel;

    public BeaconManagerConfig() {
        configModel = new AltBeaconConfigModel();
    }

    public AltBeaconConfigModel getConfigModel() {
        return configModel;
    }

    public void setConfigModel(AltBeaconConfigModel configModel) {
        this.configModel = configModel;
    }
}
