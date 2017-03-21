package pro.i_it.indoor.region;

import java.util.*;

public class SpaceRegion {

    private Set<SpaceBeacon> beacons;

    public SpaceRegion(SpaceBeacon... beacon) {
        this.beacons = new HashSet<>(Arrays.asList(beacon));
    }

    public SpaceRegion(Collection<SpaceBeacon> beacons) {
        this.beacons = new HashSet<>(beacons);
    }

    void addBeacon(SpaceBeacon beacon) {
        this.beacons.add(beacon);
    }

    void removeBeacon(SpaceBeacon beacon) {
        this.beacons.remove(beacon);
    }

    public boolean isChanged(){
        throw new UnsupportedOperationException();
    }

    public Set<SpaceRegion> getBeacons() {
        throw new UnsupportedOperationException();
    }
}
