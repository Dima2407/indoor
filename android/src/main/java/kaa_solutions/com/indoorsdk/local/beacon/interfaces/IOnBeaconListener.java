package kaa_solutions.com.indoorsdk.local.beacon.interfaces;

import org.altbeacon.beacon.Beacon;

import java.util.Collection;

/**
 * Created by syn on 10.02.17.
 */

public interface IOnBeaconListener {
    void beaconUpdate(Collection<Beacon> beacons);
}
