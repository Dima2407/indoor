package pro.i_it.indoor.local.beacon.model;


import pro.i_it.indoor.model.SettingModel;

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
