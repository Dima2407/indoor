package pro.i_it.indoor.local.gps.interfaces;

import android.support.annotation.IntDef;

import java.lang.annotation.Retention;

import static java.lang.annotation.RetentionPolicy.SOURCE;
import static pro.i_it.indoor.local.gps.interfaces.ProviderType.DEFAULT_GPS;
import static pro.i_it.indoor.local.gps.interfaces.ProviderType.DEFAULT_NETWORK;

/**
 * Created by syn on 12.02.17.
 */

@Retention(SOURCE)
@IntDef({DEFAULT_GPS, DEFAULT_NETWORK})
public @interface ProviderType {
    int DEFAULT_GPS = 1;
    int DEFAULT_NETWORK = 2;
}
