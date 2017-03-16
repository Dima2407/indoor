package pro.i_it.indoor.region;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class SpaceRegion {

    private Set<SpaceBeacon> beacons;

    public SpaceRegion(SpaceBeacon... beacon) {
        this.beacons = new HashSet<>(Arrays.asList(beacon));
    }

    public void addBeacon(SpaceBeacon beacon) {
        this.beacons.add(beacon);
    }

    public void removeBeacon(SpaceBeacon beacon) {
        this.beacons.remove(beacon);
    }

    public native void updateRegion();
}
