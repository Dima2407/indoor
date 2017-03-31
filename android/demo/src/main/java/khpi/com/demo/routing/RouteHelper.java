package khpi.com.demo.routing;

import android.graphics.PointF;
import android.os.Handler;
import android.os.Looper;
import android.support.annotation.Nullable;
import android.support.annotation.WorkerThread;
import android.util.Log;

import khpi.com.demo.model.Floor;
import khpi.com.demo.model.Route;
import khpi.com.demo.model.Step;
import khpi.com.demo.routing.core.DijkstraAlgorithm;
import khpi.com.demo.routing.core.Edge;
import khpi.com.demo.routing.core.Graph;
import khpi.com.demo.routing.core.Vertex;

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
import static java.lang.Math.pow;
import static java.lang.Math.sqrt;

/**
 * Created by kit on 9/11/16.
 */
public class RouteHelper {


    private static final String N_PATERN = "N_%d:%d";
    private final ExecutorService routeExecutor;
    private List<Vertex> nodes;
    private List<Edge> edges;
    private DijkstraAlgorithm algorithm;
    private float[] route;
    private PointF destinationPoint;
    private final double WALK_SPEED = 1.38;

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

    public void initMapFromFile(final File file, final MapProcessingListener listener) {
        final Handler handler = new Handler(Looper.myLooper());
        routeExecutor.execute(new Runnable() {
            @Override
            public void run() {
                try {
                    processFile(file);
                    handler.post(new Runnable() {
                        @Override
                        public void run() {
                            listener.onMapProcessed();
                        }
                    });
                } catch (final IOException e) {
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
    private void processFile(File file) throws IOException {
        nodes = new ArrayList<Vertex>();
        edges = new ArrayList<Edge>();
        Set<Vertex> realPoints = new HashSet<>();

        InputStream ins = new FileInputStream(file);
        BufferedReader reader = new BufferedReader(new InputStreamReader(ins));

        String s;
        boolean e = false;
        while (true) {
            s = reader.readLine();
            if (s == null) {
                break;
            }
            if (s.contains("->GRAPH")) {
                e = false;
                continue;
            }
            if (s.contains("->EDGES")) {
                e = true;
                continue;
            }
            if (!e) {
                String[] split = s.split(" ");
                int x = Integer.parseInt(split[0]);
                int y = Integer.parseInt(split[1]);
                Vertex location = new Vertex(formatNode(x, y), formatNode(x, y), x, y);
                nodes.add(location);
                continue;
            }
            if (e) {
                String[] split = s.split(" ");
                int x1 = Integer.parseInt(split[0]);
                int y1 = Integer.parseInt(split[1]);
                int x2 = Integer.parseInt(split[2]);
                int y2 = Integer.parseInt(split[3]);
                float v = Float.parseFloat(split[4]);
                Vertex v1 = new Vertex(formatNode(x1, y1), formatNode(x1, y1), x1, y1);
                Vertex v2 = new Vertex(formatNode(x2, y2), formatNode(x2, y2), x2, y2);
                realPoints.add(v1);
                realPoints.add(v2);
                edges.add(new Edge(getEdgeName(x1, y1, x2, y2), v1, v2, (int) v));
                edges.add(new Edge(getEdgeName(x2, y2, x1, y1), v2, v1, (int) v));
            }
        }

        Graph graph = new Graph(nodes, edges);
        algorithm = new DijkstraAlgorithm(graph);
    }

    public void findPath(final PointF start, final PointF end, final RouteListener listener) {
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

                float[] temp = findPath(findClosest(nodes, start), findClosest(nodes, end));

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
    private float[] findPath(PointF start, PointF end) {
        long s = System.currentTimeMillis();
        if(start==null){
            Log.d("RouteHelper", "wrong start point");
            return new float[0];
        }
        Vertex startPoint = getDestNodeByName(formatNode(start));

        if (startPoint == null) {
            Log.d("RouteHelper", "wrong start point");
            Log.d("RouteHelper", "pressed point: " + end);
            return new float[0];
        }
        Vertex endPoint = getDestNodeByName(formatNode(end));
        if (endPoint == null) {
            Log.d("RouteHelper", "wrong end point: x" + end);
            return new float[0];
        }
        algorithm.execute(startPoint);
        LinkedList<Vertex> points = algorithm.getPath(endPoint);
        if (points != null && points.size() > 0) {
            Log.d("RouteHelper", "end point: x" + end);
            route = new float[points.size() * 2];
            for (int i = 0; i < points.size(); i++) {
                Vertex vertex = points.get(i);
                route[i * 2] = vertex.getX();
                route[i * 2 + 1] = vertex.getY();
            }
            return route;
        } else {
            Log.d("RouteHelper", "route not found");
            route = new float[0];
            return route;
        }
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

    private static PointF findClosest(List<Vertex> points, PointF dest) {
        double result = Integer.MAX_VALUE;
        PointF closest = null;
        for (Vertex point : points) {
            double distance = GeometryUtils.calcDistance(point.toPoint(), dest);
            if (distance < result) {
                closest = point.toPoint();
                result = (int) distance;
            }
        }
        return closest;
    }

    private String getEdgeName(int i, int j, int x, int y) {
        return "E_" + i + ":" + j + "/" + x + ":" + y;
    }

    private Vertex getDestNodeByName(String dest) {
        for (Vertex node : nodes) {
            if (node.getName().endsWith(dest)) {
                return node;
            }
        }

        return null;
    }

    public static double routeLenght(float[] route, float pixelsize) {

        double l = 0;
        PointF p1 = new PointF(route[0], route[1]);
        PointF p2;
        for (int i = 2; i < route.length / 2; i++) {
            float x = route[i * 2];
            float y = route[i * 2 + 1];
            p2 = new PointF(route[i * 2], route[i * 2 + 1]);
            l += GeometryUtils.calcDistance(p1, p2, pixelsize);
            p1 = p2;
        }
        return l;
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

        float distance = 0;

        for (Step step : steps) {
            distance += step.getDistanceF();
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

    public void updateRoute(PointF currentPosition, RouteListener routeListener) {
        findPath(currentPosition, destinationPoint, routeListener);
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
