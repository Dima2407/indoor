package pro.i_it.indoor.region;


import java.util.Set;

public class InMemoryBeaconsLoader implements BeaconsInRegionLoader{

    private Set<SpaceBeacon> beacons;

    @Override
    public SpaceRegion onLocationChanged(float x, float y, float z) {
        throw new UnsupportedOperationException();
    }
}
