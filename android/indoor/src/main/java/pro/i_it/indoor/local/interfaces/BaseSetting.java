package pro.i_it.indoor.local.interfaces;

import pro.i_it.indoor.model.SettingModel;
import pro.i_it.indoor.model.SettingsType;

/**
 * Created by syn on 09.02.17.
 */

public interface BaseSetting {

    void updateSettings(SettingModel settings);

    void setEnable(boolean isEnable) ;

    @SettingsType
    int getSettingType();
}
