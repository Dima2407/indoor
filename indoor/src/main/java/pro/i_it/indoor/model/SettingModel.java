package pro.i_it.indoor.model;

/**
 * Created by syn on 09.02.17.
 */

public class SettingModel {
    private String lable;
    @SettingsType
    private int configType;
    private boolean enable;

    public String getLable() {
        return lable;
    }

    public void setLable(String lable) {
        this.lable = lable;
    }

    @SettingsType
    public int getConfigType() {
        return configType;
    }

    public void setConfigType(@SettingsType int configType) {
        this.configType = configType;
    }

    public boolean isEnable() {
        return enable;
    }

    public void setEnable(boolean enable) {
        this.enable = enable;
    }
}
