package khpi.com.demo.ui.fragment;

import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.graphics.PointF;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.design.widget.BottomSheetBehavior;
import android.support.design.widget.CoordinatorLayout;
import android.support.v4.app.Fragment;
import android.support.v7.app.AlertDialog;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.util.Pair;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.Toast;

import khpi.com.demo.R;
import khpi.com.demo.model.Floor;
import khpi.com.demo.model.Inpoint;
import khpi.com.demo.model.Route;
import khpi.com.demo.model.Step;
import khpi.com.demo.routing.IndoorMapView;
import khpi.com.demo.routing.RouteHelper;
import khpi.com.demo.ui.BottomSheet;
import khpi.com.demo.ui.activity.MainActivity;
import khpi.com.demo.ui.adapter.RouteDataAdapter;
import khpi.com.demo.ui.view.MapSwitcherView;
import khpi.com.demo.utils.FileUtil;
import khpi.com.demo.utils.ManeuverHelper;
import khpi.com.demo.utils.PixelsUtil;
import pro.i_it.indoor.IndoorLocationManager;
import pro.i_it.indoor.OnLocationUpdateListener;
import pro.i_it.indoor.config.NativeConfigMap;
import pro.i_it.indoor.masks.ResourcesMaskTableFetcher;
import pro.i_it.indoor.region.InMemoryBeaconsLoader;

import com.squareup.picasso.Picasso;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by kit on 9/15/16.
 */
public class IndoorMap2DFragment extends GenericFragment implements IndoorMapView.DestinationListener,
        IndoorMapView.InpointClickListener,
        MapSwitcherView.ChangeMapListener {

    private IndoorMapView mapView;
    private BottomSheet bottomSheet;
    private RecyclerView.OnScrollListener listener;
    private Floor floor;
    private View cameraBtn;

    public static String KEY_FLOOR_MAP = "floorMap";
    public static int REGION_RADIUS = 10;
    public static PointF dest = new PointF();

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Bundle arguments = getArguments();
        floor = arguments.getParcelable(KEY_FLOOR_MAP);
    }

    private IndoorLocationManager getLocalManager() {
        return getActivityBridge().getProjectApplication().getLocalManager();
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        Log.i("onLocationChanged", "IndoorMap : onCreateView");
        return inflater.inflate(R.layout.fragment_demo_map, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        Log.i("onLocationChanged", "IndoorMap : onViewCreated");
        listener = new RecyclerView.OnScrollListener() {
            @Override
            public void onScrolled(final RecyclerView recyclerView, final int dx, final int dy) {
                super.onScrolled(recyclerView, dx, dy);
                int firstVisibleItemPosition = ((LinearLayoutManager) recyclerView.getLayoutManager()).findFirstVisibleItemPosition();
                if (firstVisibleItemPosition == RecyclerView.NO_POSITION) {
                    return;
                }

                if (firstVisibleItemPosition > 0) {
                    ((CoordinatorLayout.LayoutParams) bottomSheet.getBottomViewWrapper().getLayoutParams()).setBehavior(null);
                } else {
                    ((CoordinatorLayout.LayoutParams) bottomSheet.getBottomViewWrapper().getLayoutParams()).setBehavior(bottomSheet.getBottomSheetBehavior());
                }
            }
        };

        bottomSheet = getActivityBridge().getBottomSheet();
        bottomSheet.getCancelButton().setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(final View view) {
                dest.x = 0;
                dest.y = 0;
                getActivityBridge().getRouteHelper().clear();
                bottomSheet.getBottomViewWrapper().setVisibility(View.GONE);
                bottomSheet.getHintContainer().setVisibility(View.GONE);
                bottomSheet.getCancelButton().setVisibility(View.GONE);
                mapView.setRoute(new float[0]);
                bottomSheet.getBottomSheetBehavior().setState(BottomSheetBehavior.STATE_COLLAPSED);
                RelativeLayout.LayoutParams layoutParams = (RelativeLayout.LayoutParams) cameraBtn.getLayoutParams();
                layoutParams.topMargin = PixelsUtil.dpToPx(16, getContext());
                cameraBtn.setLayoutParams(layoutParams);
                mapView.setRoute(new float[0]);
            }
        });

        mapView = (IndoorMapView) view.findViewById(R.id.map_view);
        mapView.setCoordinates(0, 0, 0, 0);
        mapView.setDestinationListener(this);
        onMapSelected();
        mapView.setInpointClickListener(this);
        MapSwitcherView switcherView = (MapSwitcherView) view.findViewById(R.id.map_switcher);
        switcherView.setListener(this);

        cameraBtn = view.findViewById(R.id.indoor_map_camera_btn);
        cameraBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(final View view) {
                getActivityBridge().getLauncher().launchIndoorCameraFragment(floor);
            }
        });

        ((MainActivity) getActivity()).getSupportActionBar().setDisplayHomeAsUpEnabled(true);
    }

    @Override
    public void onStart() {
        super.onStart();

        float[] route = getActivityBridge().getRouteHelper().getRoute();
        if (route != null && route.length != 0) {
            onNewRoute(route);
            dest = getActivityBridge().getRouteHelper().getDestinationPoint();
        }
    }

    @Override
    public void onResume() {
        super.onResume();
        Log.d("onLocationChanged", "onResume: ");
        final boolean useBinaryMask = getSharedHelper().useBinaryMask();


        NativeConfigMap configs = new NativeConfigMap();
        if(getSharedHelper().getActiveModeKey() == 0){
            configs.set(NativeConfigMap.KEY_USE_BEACONS, true);
            configs.set(NativeConfigMap.KEY_BEACONS, floor.getSpaceBeacons());
        } else if(getSharedHelper().getActiveModeKey() == 1) {
            configs.set(NativeConfigMap.KEY_USE_SENSORS, true);
            PointF initPosition = getSharedHelper().getInitPosition();
            configs.set(NativeConfigMap.KEY_INIT_X, initPosition.x);
            configs.set(NativeConfigMap.KEY_INIT_Y, initPosition.y);
        }else if(getSharedHelper().getActiveModeKey() == 2){
            configs.set(NativeConfigMap.KEY_USE_BEACONS, true);
            configs.set(NativeConfigMap.KEY_USE_SENSORS, true);
            configs.set(NativeConfigMap.KEY_BEACONS, floor.getSpaceBeacons());
        }
        configs.set(NativeConfigMap.KEY_USE_MASK, getSharedHelper().useBinaryMask());
        configs.set(NativeConfigMap.KEY_MESH_D_X, 0.3);
        configs.set(NativeConfigMap.KEY_MESH_D_Y, 0.3);
        configs.set(NativeConfigMap.KEY_MESH_X_0, 0.0);
        configs.set(NativeConfigMap.KEY_MESH_Y_0, 0.0);
        if (floor.getGraphPath().contains("/mapData/8/")) {
            //it-jim
            configs.set(NativeConfigMap.KEY_MAP_ANGLE, 20);
            if (useBinaryMask) {
                configs.set(NativeConfigMap.KEY_MESH_N_X, 36.0);
                configs.set(NativeConfigMap.KEY_MESH_N_Y, 24.0);
                configs.set(NativeConfigMap.KEY_MASK, new ResourcesMaskTableFetcher(getResources(), R.raw.masktable1));
            }
        } else {
            //kaa
            configs.set(NativeConfigMap.KEY_MAP_ANGLE, 0);
            if (useBinaryMask) {
                configs.set(NativeConfigMap.KEY_MESH_N_X, 22.0);
                configs.set(NativeConfigMap.KEY_MESH_N_Y, 44.0);
                configs.set(NativeConfigMap.KEY_MASK, new ResourcesMaskTableFetcher(getResources(), R.raw.masktable2));
            }
        }

        getLocalManager().setConfiguration(configs);

        getLocalManager().setOnLocationUpdateListener(new OnLocationUpdateListener() {
            @Override
            public void onLocationChanged(float[] position) {
                applyNewCoordinate(position[0], position[1], 1, 1);
            }
        });
        getLocalManager().start();
    }

    @Override
    public void onPause() {
        Log.d("onLocationChanged", "onPause: ");
        super.onPause();
        getLocalManager().stop();

    }

    @Override
    public void onMapSelected() {
        mapView.setRoute(new float[0]);
        final String absolutePath = FileUtil.getLocacPath(getActivity(), floor.getMaskPath()).getAbsolutePath();
        double pixelSize = floor.getPixelSize();
        if (pixelSize == 0.0073)
            pixelSize = 0.007;
        mapView.initMapImage(absolutePath, pixelSize);
        final ProgressDialog progressDialog = new ProgressDialog(getActivity());

        Log.i("IndMap", "floor.getGraphPath() = " + FileUtil.getLocacPath(getActivity(), floor.getGraphPath()));
        getActivityBridge().getRouteHelper().initMapFromFile(FileUtil.getLocacPath(getActivity(), floor.getGraphPath()), new RouteHelper.MapProcessingListener() {
            @Override
            public void onMapProcessed(Pair<String, Integer> graph) {
                getLocalManager().setGraph(graph.first, graph.second);
                progressDialog.hide();
                mapView.setEdges(getActivityBridge().getRouteHelper().getEdges());
            }

            @Override
            public void onFailed(@Nullable Throwable t) {
                progressDialog.hide();
                Toast.makeText(getActivity(), t.getMessage(), Toast.LENGTH_SHORT).show();
            }
        });

        mapView.setBeacons(floor.getBeacons());
        List<Integer> inpointIdList = floor.getInpointIdList();
        List<Inpoint> inpoints = new ArrayList<>();
        for (int i : inpointIdList) {
            inpoints.add(getActivityBridge().getDbBridge().getInpointById(i));
        }
        mapView.setInpoints(inpoints);

    }

    @Override
    public void onDestinationChanged(float x, float y) {
        Log.d("DemoIndorMapFragment", "x:" + x);
        Log.d("DemoIndorMapFragment", "y:" + y);
        dest.x = x;
        dest.y = y;
    }

    private void onNewRoute(float[] route) {
        if (getContext() == null) {
            return;
        }
        mapView.setRoute(route);

        bottomSheet.getBottomViewWrapper().setVisibility(View.VISIBLE);
        bottomSheet.getCancelButton().setVisibility(View.VISIBLE);

        RelativeLayout.LayoutParams layoutParams = (RelativeLayout.LayoutParams) cameraBtn.getLayoutParams();
        layoutParams.topMargin = PixelsUtil.dpToPx(72, getContext());
        cameraBtn.setLayoutParams(layoutParams);

        List<RouteHelper.Motion> motions = getActivityBridge().getRouteHelper().getMoutions(route);

        Route r = getActivityBridge().getRouteHelper().buildRoute(motions, floor);
        if (r == null || r.getSteps().isEmpty()) {
            return;
        }

        initHint(r);
        initTotalData(r);

        bottomSheet.getDataList().addOnScrollListener(listener);

        Step destinationStep = new Step();
        destinationStep.setHint(r.getEndAddress());

        List<Step> steps = new ArrayList<>(r.getSteps());
        steps.add(destinationStep);

        ((RouteDataAdapter) bottomSheet.getDataList().getAdapter()).putData(steps);
    }

    private void initHint(final Route route) {
        bottomSheet.getHintContainer().setVisibility(View.VISIBLE);

        Step first = route.getSteps().get(0);

        int icon = ManeuverHelper.getManeuverIcon(first.getManeuver());

        Picasso.with(getContext()).load(icon).into(bottomSheet.getHintIcon());
        bottomSheet.getHintText().setText(first.getHint().trim());
    }

    private void initTotalData(final Route route) {
        bottomSheet.getTotalDuration().setText(String.format("Total duration: %s", route.getDuration()));
        bottomSheet.getTotalDistance().setText(String.format("Total distance: %s", route.getDistance()));
    }

    public static Fragment makeInstance(Floor floor) {
        IndoorMap2DFragment fragment = new IndoorMap2DFragment();
        Bundle bundle = new Bundle();
        bundle.putParcelable(KEY_FLOOR_MAP, floor);
        fragment.setArguments(bundle);
        return fragment;
    }


    private void applyNewCoordinate(float x, float y, float tx, float ty) {
        if (getActivity() == null) {
            return;
        }
        mapView.setCoordinates(tx, ty, x, y);

        if (dest.x == 0 && dest.y == 0) {
            mapView.setRoute(new float[0]);
            return;
        }
        if (Float.isNaN(x) && Float.isNaN(x)) {
            mapView.setRoute(new float[0]);
            return;
        }
        Log.i("locationManager", "apply new coords : dest.x = " + dest.x + " dest.y = " + dest.y);

        getActivityBridge().getRouteHelper().findPath(new PointF((float) (x / floor.getPixelSize()), (float) (y / floor.getPixelSize())), dest, getLocalManager(), new RouteHelper.RouteListener() {
            @Override
            public void onRouteFound(float[] route) {
                onNewRoute(route);
            }

            @Override
            public void onFail() {
                Log.d("DemoIndorMapFragment", "No route to this point");
                if (dest.x == 0 && dest.y == 0) {
                    return;
                }
                mapView.setRoute(new float[0]);

                bottomSheet.getBottomViewWrapper().setVisibility(View.GONE);
                bottomSheet.getCancelButton().setVisibility(View.GONE);
                bottomSheet.getHintContainer().setVisibility(View.GONE);

                RelativeLayout.LayoutParams layoutParams = (RelativeLayout.LayoutParams) cameraBtn.getLayoutParams();
                layoutParams.topMargin = PixelsUtil.dpToPx(16, getContext());
                cameraBtn.setLayoutParams(layoutParams);
            }
        });
    }

    @Override
    public void onInpoictClicked(final Inpoint inpoint) {
        getActivityBridge().getRouteHelper().findPath(mapView.getCoordinates(), new PointF((float) inpoint.getX(), (float) inpoint.getY()), getLocalManager(), new RouteHelper.RouteListener() {
            @Override
            public void onRouteFound(float[] route) {
                Route r = getActivityBridge().getRouteHelper().buildRoute(getActivityBridge().getRouteHelper().getMoutions(route), floor);
                new AlertDialog.Builder(getActivity())
                        .setIcon(R.drawable.poi_big_icn)
                        .setTitle(inpoint.getTitle())
                        .setMessage(inpoint.getSubtitle() + "\n" + "Distance: " + r.getDistance() + "m" + "\n" + "Time: " + r.getDuration())
                        .setNegativeButton("Close", null)
                        .setPositiveButton("To point", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                onDestinationChanged((float) inpoint.getX(), (float) inpoint.getY());
                            }
                        })
                        .create().show();
            }

            @Override
            public void onFail() {
                new AlertDialog.Builder(getActivity())
                        .setTitle(inpoint.getTitle())
                        .setMessage(inpoint.getSubtitle())
                        .setNegativeButton("Close", null)
                        .setPositiveButton("To point", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                onDestinationChanged((float) inpoint.getX(), (float) inpoint.getY());
                            }
                        })
                        .create().show();
            }
        });
    }

    @Override
    public void onStop() {
        super.onStop();
        Log.i("onLocationChanged", "IndoorMap : onStop");
        bottomSheet.getBottomViewWrapper().setVisibility(View.GONE);
        bottomSheet.getCancelButton().setVisibility(View.GONE);
        bottomSheet.getCancelButton().callOnClick();
        bottomSheet.getHintContainer().setVisibility(View.GONE);
    }
}
