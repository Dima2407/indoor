package pro.i_it.indoor.region;

import java.util.*;

public class SpaceRegion {

    private Set<SpaceBeacon> beacons;
    private boolean changedFromPrevious;

    public SpaceRegion(SpaceBeacon... beacon) {
        this.beacons = new HashSet<>(Arrays.asList(beacon));
    }

    public SpaceRegion(Collection<SpaceBeacon> beacons) {
        this.beacons = new HashSet<>(beacons);
    }

    void addBeacon(SpaceBeacon beacon) {
        if(this.beacons.add(beacon)){
            changedFromPrevious = true;
        }
    }

    void removeBeacon(SpaceBeacon beacon) {
        if(this.beacons.remove(beacon)){
            changedFromPrevious = true;
        }
    }

    public boolean isChanged(){
        return changedFromPrevious;
    }

    public Set<SpaceBeacon> getBeacons() {
        changedFromPrevious = false;
       return beacons;
    }
}
