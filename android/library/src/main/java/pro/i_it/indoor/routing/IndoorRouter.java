package pro.i_it.indoor.routing;


import android.graphics.PointF;
import android.util.Log;

import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class IndoorRouter {

    private float[] route;
    private float distance;

    private float startX = -1.0f;
    private float startY = -1.0f;

    private float destinationX = -1.0f;
    private float destinationY = -1.0f;

    private double pixelSize = -1.0f;

    private static final double WALK_SPEED = 1.38;
    private static final double IT_JIM_SCALE = 0.007;

    private final DecimalFormat df = new DecimalFormat("0.0");

    private final String[] speeds = new String[]{"sec", "min", "hour"};

    public Route buildRoute() {
        return buildRoute(getMoutions(route), pixelSize);
    }

    public Route buildRoute(final List<Motion> motions, double pixelSize) {
        Route route = new Route();
        route.setStartAddress("Your location");
        route.setEndAddress("Destination point has been reached");
        route.setWarnings(new ArrayList<String>());
        route.setDuration(null);

        List<Step> steps = new ArrayList<>();

        for (int i = 0; i < motions.size(); i++) {
            Motion motion = motions.get(i);

            Step step = new Step(motion, pixelSize);

            double v = (motion.distance * pixelSize) / WALK_SPEED;
            int j = 0;
            while (v > 60) {
                v = v / 60;
                j++;
            }

            step.setDuration(df.format(v) + speeds[j]);

            if (motion.angleDirection > 0) {
                step.setManeuver(Step.MANEUVER_TURN_LEFT);
                step.setHint("Turn left");
            } else if (motion.angleDirection < 0) {
                step.setManeuver(Step.MANEUVER_TURN_RIGHT);
                step.setHint("Turn right");
            } else {
                step.setManeuver(Step.MANEUVER_STRAIGHT);
                step.setHint("Move forward");
            }

            if (i == 0) {
                step.setHint("Let's go");
            }

            step.setDistance(df.format(motion.distance * pixelSize) + " m");
            step.setDistanceF((float) (motion.distance * pixelSize));
            steps.add(step);
        }

        double v = (getDistance()) / WALK_SPEED;
        int i = 0;
        while (v > 60) {
            v = v / 60;
            i++;
        }

        route.setDistance(df.format(getDistance()) + " m");
        route.setDuration(df.format(v) + " " + speeds[i]);
        route.setSteps(steps);

        return route;
    }

    public List<Motion> getMoutions(float[] route) {
        if (route.length < 6) {
            return new ArrayList<>();
        }

        List<Motion> result = new ArrayList<>();
        for (int i = 2; i < (route.length - 2) / 2; i++) {
            PointF a = new PointF(route[(i - 2) * 2], route[(i - 2) * 2 + 1]);
            PointF b = new PointF(route[(i - 1) * 2], route[(i - 1) * 2 + 1]);
            PointF c = new PointF(route[(i - 0) * 2], route[(i - 0) * 2 + 1]);

            Motion motion = new Motion(a, b, c);
            Log.d("RouteHelper", motion.toString());
            result.add(motion);
        }
        return result;
    }

    public float[] getRoute() {
        return route;
    }

    public void clearDestination() {
        this.pixelSize = -1.0f;
        this.destinationX = -1.0f;
        this.destinationY = -1.0f;
        this.route = new float[0];
    }

    public void setDestination(float destinationX, float destinationY, double pixelSize) {
        this.destinationX = destinationX;
        this.destinationY = destinationY;
        this.pixelSize = pixelSize;
    }

    public PointF getStartPosition() {
        return new PointF(startX, startY);
    }

    public PointF getEndPosition() {
        return new PointF(startX, startY);
    }

    public float getDistance() {
        return (float) (distance * IT_JIM_SCALE);
    }

    public boolean positionDetected() {
        return startX >= 0 && startY >= 0;
    }

    public void clear() {
        this.startX = -1.0f;
        this.startY = -1.0f;
        clearDestination();
    }
}
