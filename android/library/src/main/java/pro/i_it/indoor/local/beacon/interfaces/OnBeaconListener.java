package pro.i_it.indoor.local.beacon.interfaces;

import org.altbeacon.beacon.Beacon;

import java.util.Collection;

/**
 * Created by syn on 10.02.17.
 */

public interface OnBeaconListener {
    void beaconUpdate(Collection<Beacon> beacons);
}
