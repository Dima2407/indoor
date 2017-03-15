package khpi.com.demo.model;

public class Step {

    public static final String MANEUVER_TURN_LEFT = "turn-left";
    public static final String MANEUVER_TURN_RIGHT = "turn-right";
    public static final String MANEUVER_TURN_SHARP_LEFT = "turn-sharp-left";
    public static final String MANEUVER_UTURN_RIGHT = "uturn-right";
    public static final String MANEUVER_TURN_SLIGHT_RIGHT = "turn-slight-right";
    public static final String MANEUVER_MERGE = "merge";
    public static final String MANEUVER_ROUNDABOUT_LEFT = "roundabout-left";
    public static final String MANEUVER_ROUNDABOUT_RIGHT = "roundabout-right";
    public static final String MANEUVER_UTURN_LEFT = "uturn-left";
    public static final String MANEUVER_TURN_SLIGHT_LEFT = "turn-slight-left";
    public static final String MANEUVER_RAMP_RIGHT = "ramp-right";
    public static final String MANEUVER_FORK_RIGHT = "fork-right";
    public static final String MANEUVER_FORK_LEFT = "fork-left";
    public static final String MANEUVER_FERRY_TRAIN = "ferry-train";
    public static final String MANEUVER_TURN_SHARP_RIGHT = "turn-sharp-right";
    public static final String MANEUVER_RAMP_LEFT = "ramp-left";
    public static final String MANEUVER_STRAIGHT = "straight";

    private double startLatitude;
    private double startLongitude;

    private double endLatitude;
    private double endLongitude;

    private String hint;
    private String duration;
    private String distance;

    private String maneuver;
    private float distanceF;

    public Step(double startLatitude, double startLongitude, double endLatitude, double endLongitude) {
        this.startLatitude = startLatitude;
        this.startLongitude = startLongitude;
        this.endLatitude = endLatitude;
        this.endLongitude = endLongitude;
    }

    public Step() {
        this(-1, -1, -1, -1);

        distance = "";
    }

    public double getStartLatitude() {
        return startLatitude;
    }

    public double getStartLongitude() {
        return startLongitude;
    }

    public double getEndLatitude() {
        return endLatitude;
    }

    public double getEndLongitude() {
        return endLongitude;
    }

    public String getHint() {
        return hint;
    }

    public void setHint(final String hint) {
        this.hint = hint;
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

    public String getManeuver() {
        return maneuver;
    }

    public void setManeuver(final String maneuver) {
        this.maneuver = maneuver;
    }

    @Override
    public boolean equals(final Object obj) {
        if (!obj.getClass().isAssignableFrom(Step.class)) {
            return false;
        }

        Step step = (Step) obj;

        return getStartLatitude() == step.getStartLatitude() && getStartLongitude() == step.getStartLongitude() &&
                getEndLatitude() == step.getEndLatitude() && getEndLongitude() == step.getEndLongitude();
    }

    public void setDistanceF(final float distance) {
        this.distanceF = distance;
    }

    public float getDistanceF() {
        return distanceF;
    }
}
