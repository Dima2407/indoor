package pro.i_it.indoor.routing;

import android.location.Location;

import java.util.ArrayList;
import java.util.List;

public class Route {

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
}
