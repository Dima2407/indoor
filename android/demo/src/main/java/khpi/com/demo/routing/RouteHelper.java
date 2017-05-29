package khpi.com.demo.routing;

import android.graphics.PointF;
import android.os.Handler;
import android.os.Looper;
import android.support.annotation.Nullable;
import android.support.annotation.WorkerThread;
import android.util.Log;

import khpi.com.demo.model.Floor;
import khpi.com.demo.model.Point;
import khpi.com.demo.model.Route;
import khpi.com.demo.model.Step;
import khpi.com.demo.routing.core.DijkstraAlgorithm;
import khpi.com.demo.routing.core.Edge;
import khpi.com.demo.routing.core.Graph;
import khpi.com.demo.routing.core.Vertex;
import pro.i_it.indoor.IndoorLocationManager;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import static java.lang.Math.PI;
import static java.lang.Math.atan2;
import static java.lang.Math.floor;
import static java.lang.Math.pow;
import static java.lang.Math.sqrt;

/**
 * Created by kit on 9/11/16.
 */
public class RouteHelper {


    private final double IT_JIM_SCALE = 0.007;
    private static final String N_PATERN = "N_%d:%d";
    private final ExecutorService routeExecutor;
    private List<Edge> edges;
    private float[] route;
    private PointF destinationPoint;
    private final double WALK_SPEED = 1.38;
    private float distance = 0;

    public List<Edge> getEdges() {
        return edges;
    }

    public void setEdges(List<Edge> edges) {
        this.edges = edges;
    }

    DecimalFormat df = new DecimalFormat("0.0");

    public RouteHelper() {
        routeExecutor = Executors.newSingleThreadExecutor();
    }

    public void initMapFromFile(final File file, final IndoorLocationManager instance, final MapProcessingListener listener) {
        final Handler handler = new Handler(Looper.myLooper());
        routeExecutor.execute(new Runnable() {
            @Override
            public void run() {
                try {
                    processFile(file, instance);
                    handler.post(new Runnable() {
                        @Override
                        public void run() {
                            listener.onMapProcessed();
                        }
                    });
                } catch (final IOException e) {;
                    e.printStackTrace();
                    handler.post(new Runnable() {
                        @Override
                        public void run() {
                            listener.onFailed(e);
                        }
                    });

                }
            }
        });
    }


    @WorkerThread
    private void processFile(File file, IndoorLocationManager instance) throws IOException {
        edges = new ArrayList<Edge>();

        InputStream ins = new FileInputStream(file);
        BufferedReader reader = new BufferedReader(new InputStreamReader(ins));

        String s;
        StringBuilder sb = new StringBuilder();
        boolean e = false;
        while ((s = reader.readLine()) != null) {
            sb.append(s).append("\n");
            if (s.contains("->GRAPH")) {
                e = false;
                continue;
            }
            if (s.contains("->EDGES")) {
                e = true;
                continue;
            }
            if (e) {
                String[] split = s.split(" ");
                if(split.length < 5){
                    continue;
                }
                double x1 = Double.parseDouble(split[0]);
                double y1 = Double.parseDouble(split[1]);
                double x2 = Double.parseDouble(split[2]);
                double y2 = Double.parseDouble(split[3]);
                double v = Double.parseDouble(split[4]);
                Vertex v1 = new Vertex(formatNode((int)x1, (int)y1), formatNode((int)x1, (int)y1), (int)x1, (int)y1);
                Vertex v2 = new Vertex(formatNode((int)x2, (int)y2), formatNode((int)x2, (int)y2), (int)x2, (int)y2);

                edges.add(new Edge(getEdgeName((int)x1, (int)y1, (int)x2, (int)y2), v1, v2, (int) v));
                edges.add(new Edge(getEdgeName((int)x2, (int)y2, (int)x1, (int)y1), v2, v1, (int) v));
            }
        }
        sb.deleteCharAt(sb.length() - 1);
        String str = sb.toString();

        instance.setGraphArraysFromFile(str, 1);
    }

    public void findPath(final PointF start, final PointF end, final IndoorLocationManager instance, final RouteListener listener) {
        final Handler handler = new Handler(Looper.getMainLooper());
        routeExecutor.execute(new Runnable() {
            @Override
            public void run() {
                if (end == null) {
                    handler.post(new Runnable() {
                        @Override
                        public void run() {
                            listener.onFail();
                        }
                    });
                    return;
                }

                float[] temp = findPath(start, end, instance);

                final float[] path = new float[temp.length + 4];
                path[0] = start.x;
                path[1] = start.y;
                System.arraycopy(temp, 0, path, 2, temp.length);
                path[path.length - 2] = end.x;
                path[path.length - 1] = end.y;

                handler.post(new Runnable() {
                    @Override
                    public void run() {
                        if (path.length > 0) {
                            listener.onRouteFound(path);
                        } else {
                            listener.onFail();
                        }
                    }
                });

                destinationPoint = end;
            }
        });
    }

    @WorkerThread
    private float[] findPath(PointF start, PointF end, IndoorLocationManager instance) {
        long s = System.currentTimeMillis();
        if (start == null) {
            Log.d("RouteHelper", "wrong start point");
            return new float[0];
        }

        double[] arrayRoute = instance.getRoute(start.x, start.y, end.x, end.y);

        if (arrayRoute != null && arrayRoute.length > 0) {
            distance = (float) (arrayRoute[0] * IT_JIM_SCALE);
            route = new float[arrayRoute.length - 1];
            for (int i = 1; i < arrayRoute.length; i++)
                route[i - 1] = (float) arrayRoute[i];
            return route;
        }
        else
            return new float[0];
    }


    private static String formatNode(int i, int j) {
        return String.format(N_PATERN, i, j);
    }

    private static String formatNode(float i, float j) {
        return formatNode((int) i, (int) j);
    }

    private static String formatNode(PointF p) {
        return formatNode(p.x, p.y);
    }

    private String getEdgeName(int i, int j, int x, int y) {
        return "E_" + i + ":" + j + "/" + x + ":" + y;
    }

    String[] speeds = new String[]{"sec", "min", "hour"};

    public Route buildRoute(final List<Motion> motions, Floor floor) {
        Route route = new Route();
        route.setStartAddress("Your location");
        route.setEndAddress("Destination point has been reached");
        route.setWarnings(new ArrayList<String>());
        route.setDuration(null);

        List<Step> steps = new ArrayList<>();

        for (int i = 0; i < motions.size(); i++) {
            Motion motion = motions.get(i);

            Step step = new Step(motion.start.x * floor.getPixelSize(), motion.start.y * floor.getPixelSize(), motion.end.x * floor.getPixelSize(), motion.end.y * floor.getPixelSize());

            double v = (motion.distance * floor.getPixelSize()) / WALK_SPEED;
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

            step.setDistance(df.format(motion.distance * floor.getPixelSize()) + " m");
            step.setDistanceF((float) (motion.distance * floor.getPixelSize()));
            steps.add(step);
        }

        double v = (distance) / WALK_SPEED;
        int i = 0;
        while (v > 60) {
            v = v / 60;
            i++;
        }

        route.setDistance(df.format(distance) + " m");
        route.setDuration(df.format(v) + " " + speeds[i]);
        route.setSteps(steps);

        return route;
    }

    public float[] getRoute() {
        return route;
    }

    public void clear() {
        route = new float[0];
        destinationPoint = null;
    }

    public void updateRoute(PointF currentPosition, IndoorLocationManager instance, RouteListener routeListener) {
        Log.i("locationManager", "updateRoute : dest.x = " + destinationPoint.x + " dest.y = " + destinationPoint.y);
        findPath(currentPosition, destinationPoint, instance, routeListener);
    }

    public interface MapProcessingListener {
        void onMapProcessed();

        void onFailed(@Nullable Throwable t);
    }

    public interface RouteListener {
        void onRouteFound(float[] route);

        void onFail();
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


    public class Motion {
        PointF start;
        PointF end;
        int angleDirection;
        float distance;

        public Motion(PointF p1, PointF p2, PointF p3) {


            pow((p2.x - p1.x), 2);
            distance = (float) sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));

            start = p1;
            end = p2;


            //if angle<0 -> right, if angle>0 left
            angleDirection = (int) (getAngle(p1, p2) - getAngle(p2, p3));

        }


        private float getAngle(PointF a, PointF b) {
            float deltaX = b.x - a.x;
            float deltaY = b.y - a.y;
            float angleInDegrees = (float) (atan2(deltaY, deltaX) * 180 / PI);
            return angleInDegrees;
        }


        @Override
        public String toString() {
            return "distance:" + distance + ">> angle:" + (angleDirection < 0 ? "right" : "left");
        }
    }

    public PointF getDestinationPoint() {
        return destinationPoint;
    }
}
