package pro.i_it.indoor.model;


import android.support.annotation.IntDef;

import java.lang.annotation.Retention;

import static java.lang.annotation.RetentionPolicy.SOURCE;
import static pro.i_it.indoor.model.SettingsType.BEACON;
import static pro.i_it.indoor.model.SettingsType.GPS;
import static pro.i_it.indoor.model.SettingsType.NOT_SET;
import static pro.i_it.indoor.model.SettingsType.WIFI;

/**
 * Created by syn on 09.02.17.
 */

@Retention(SOURCE)
@IntDef({NOT_SET, GPS, WIFI, BEACON})
public @interface SettingsType {
    int NOT_SET = 0;
    int GPS = 1;
    int WIFI = 2;
    int BEACON = 3;
}