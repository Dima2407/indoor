package kaa_solutions.com.indoorsdk.local.beacon.interfaces;

import android.content.Context;

import kaa_solutions.com.indoorsdk.local.interfaces.IBaseSetting;

/**
 * Created by syn on 09.02.17.
 */

public interface IBeaconManager extends IBaseSetting {

    void setOnBeaconListener(IOnBeaconListener iOnBeaconListener);
}
