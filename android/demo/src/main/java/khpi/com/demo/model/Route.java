package khpi.com.demo.model;

import com.google.android.gms.maps.model.LatLng;

import java.util.ArrayList;
import java.util.List;

public final class Route {

    private List<Step> steps;
    private String startAddress;
    private String endAddress;

    private String duration;
    private String distance;

    private List<String> warnings;

    public List<Step> getSteps() {
        return steps;
    }

    public void setSteps(final List<Step> steps) {
        this.steps = steps;
    }

    public String getStartAddress() {
        return startAddress;
    }

    public void setStartAddress(final String startAddress) {
        this.startAddress = startAddress;
    }

    public String getEndAddress() {
        return endAddress;
    }

    public void setEndAddress(final String endAddress) {
        this.endAddress = endAddress;
    }

    public String getDuration() {
        return duration;
    }

    public void setDuration(final String duration) {
        this.duration = duration;
    }

    public String getDistance() {
        return distance;
    }

    public void setDistance(final String distance) {
        this.distance = distance;
    }

    public List<String> getWarnings() {
        return warnings;
    }

    public void setWarnings(final List<String> warnings) {
        this.warnings = warnings;
    }

    public List<LatLng> convertSteps() {
        List<LatLng> latLngs = new ArrayList<>();

        for (int i = 0; i < steps.size(); i++) {
            Step step = steps.get(i);

            latLngs.add(new LatLng(step.getStartLatitude(), step.getStartLongitude()));

            if (i == steps.size() - 1) {
                latLngs.add(new LatLng(step.getEndLatitude(), step.getEndLongitude()));
            }
        }

        return latLngs;
    }

    public LatLng getDestinationPoint() {
        Step last = steps.get(steps.size() - 1);

        return new LatLng(last.getEndLatitude(), last.getEndLongitude());
    }
}
