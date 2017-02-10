package kaa_solutions.com.indoorsdk.dependency.interfaces;

import kaa_solutions.com.indoorsdk.local.beacon.interfaces.IBeaconManager;
import kaa_solutions.com.indoorsdk.local.data.interfaces.IDataManager;

/**
 * Created by syn on 09.02.17.
 */

public interface ILocalManager {
    IBeaconManager getBeaconManager();

    IDataManager getDataManager();
}
