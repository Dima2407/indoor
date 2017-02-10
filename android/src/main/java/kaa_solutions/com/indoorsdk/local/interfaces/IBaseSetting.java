package kaa_solutions.com.indoorsdk.local.interfaces;

import android.os.RemoteException;

import kaa_solutions.com.indoorsdk.ui.main.model.SettingModel;
import kaa_solutions.com.indoorsdk.ui.main.model.SettingsType;

/**
 * Created by syn on 09.02.17.
 */

public interface IBaseSetting {

    void updateSettings(SettingModel settings);

    void setEnable(boolean isEnable) ;

    @SettingsType
    int getSettingType();
}
