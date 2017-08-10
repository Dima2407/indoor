package khpi.com.demo.routing;

import android.graphics.PointF;
import android.os.Handler;
import android.os.Looper;
import android.support.annotation.Nullable;
import android.support.annotation.WorkerThread;
import android.util.Log;

import android.util.Pair;
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
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
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

    public List<Edge> getEdges() {
        return edges;
    }

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
                } catch (final Exception e) {
                    ;
                    Log.e(RouteHelper.class.getSimpleName(), "run: ", e);
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
        edges = new ArrayList<Edge>();

        InputStream ins = new FileInputStream(file);
        BufferedReader reader = new BufferedReader(new InputStreamReader(ins));

        String s;
        boolean e = false;
        while ((s = reader.readLine()) != null) {
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

    public interface MapProcessingListener {
        void onMapProcessed();

        void onFailed(@Nullable Throwable t);
    }
}
