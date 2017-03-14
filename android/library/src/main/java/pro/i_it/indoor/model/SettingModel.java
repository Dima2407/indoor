package pro.i_it.indoor.model;

/**
 * Created by syn on 09.02.17.
 */

public class SettingModel {
    private String label;
    @SettingsType
    private int configType;
    private boolean enable;

    public String getLabel() {
        return label;
    }

    public void setLabel(String label) {
        this.label = label;
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

    @Override
    public String toString() {
        return getLabel();
    }
}
