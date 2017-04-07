package pro.i_it.indoor.region;


import java.util.Collection;
import java.util.HashSet;
import java.util.Set;

public class InMemoryBeaconsLoader implements BeaconsInRegionLoader {

    private static final String TAG = InMemoryBeaconsLoader.class.getSimpleName();

    private float radius;
    private Set<SpaceBeacon> beacons;
    private SpaceRegion newRegion;

    public InMemoryBeaconsLoader(Collection<SpaceBeacon> beacons, float radius){
        newRegion = new SpaceRegion();
        this.beacons = new HashSet<>(beacons);
        this.radius = radius;
    }

    @Override
    public SpaceRegion onLocationChanged(float x, float y, float z) {
        for(SpaceBeacon beacon : beacons){
            newRegion.addBeacon(beacon);
        }
        return newRegion;
    }

    private void findBeaconsInRegion(float x, float y, float z) {
        for(SpaceBeacon beacon : beacons){
            if(calculateDistance(beacon.getPosition(), x, y, z) < radius){
                newRegion.addBeacon(beacon);
            }else {
                newRegion.removeBeacon(beacon);
            }
        }
    }

    private double calculateDistance(float[] position, float x, float y, float z) {
        return Math.sqrt(Math.pow((x - position[0]), 2)
                + Math.pow((y - position[1]), 2)
                + Math.pow((z - position[2]), 2)
        );
    }


}
