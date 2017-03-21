package pro.i_it.indoor.region;

import java.util.List;

public class InMemoryBeaconsLoader implements BeaconsInRegionLoader{

    private SpaceRegion beacons;

    @Override
    public boolean onLocationChanged(float x, float y, float z) {
        return false;
    }
}
