package khpi.com.demo.ui.fragment;

import android.app.ProgressDialog;
import android.content.DialogInterface;
import android.graphics.PointF;
import android.os.Bundle;
import android.os.SystemClock;
import android.support.annotation.Nullable;
import android.support.design.widget.BottomSheetBehavior;
import android.support.design.widget.CoordinatorLayout;
import android.support.v4.app.Fragment;
import android.support.v7.app.AlertDialog;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RelativeLayout;
import android.widget.Toast;

import khpi.com.demo.R;
import khpi.com.demo.model.BeaconModel;
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
import khpi.com.demo.utils.ConverterUtil;
import khpi.com.demo.utils.FileUtil;
import khpi.com.demo.utils.ManeuverHelper;
import khpi.com.demo.utils.PixelsUtil;
import pro.i_it.indoor.IndoorLocationManager;
import pro.i_it.indoor.OnLocationUpdateListener;
import pro.i_it.indoor.region.BluetoothBeacon;
import pro.i_it.indoor.region.InMemoryBeaconsLoader;
import pro.i_it.indoor.region.SpaceBeacon;

//import com.indoor.beacon.IndoorPositionManager;
import com.squareup.picasso.Picasso;

import org.altbeacon.beacon.Beacon;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;

import static pro.i_it.indoor.DebugConfig.TAG;
import static pro.i_it.indoor.config.DebugConfig.IS_DEBUG;

/**
 * Created by kit on 9/15/16.
 */
public class IndoorMap2DFragment extends GenericFragment implements IndoorMapView.DestinationListener,
        /* IndoorPositionManager.PositionListener,
         IndoorPositionManager.ErrorListener,*/
        IndoorMapView.InpointClickListener,
        MapSwitcherView.ChangeMapListener {

    private IndoorMapView mapView;

    //private Building map;
    //private IndoorPositionManager instance;
    private IndoorLocationManager instance;
    private BottomSheet bottomSheet;
    private RecyclerView.OnScrollListener listener;
    private Floor floor;
    private View cameraBtn;
    public static PointF dest = new PointF();

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Bundle arguments = getArguments();
//        map = arguments.getParcelable("mapView");
        floor = arguments.getParcelable("mapView");
        //instance = IndoorPositionManager.getInstance(getActivity());
        instance = getActivityBridge().getProjectApplication().getLocalManager();
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        instance = null;
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_demo_map, container, false);
    }

    @Override
    public void onViewCreated(View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

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
        onMapSelected(1);
        mapView.setInpointClickListener(this);
        MapSwitcherView switcherView = (MapSwitcherView) view.findViewById(R.id.map_switcher);
        switcherView.setListener(this);
//        switcherView.setMap(map.getFloors());
//        if (map.getFloors().size() <= 1) {
//            switcherView.setVisibility(View.GONE);
//        }

        cameraBtn = view.findViewById(R.id.indoor_map_camera_btn);
        cameraBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(final View view) {
                //getActivityBridge().getLauncher().launchIndoorCameraFragment(floor);
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
        instance.start();
        instance.setOnLocationUpdateListener(new OnLocationUpdateListener() {
            @Override
            public void onLocationChanged(float[] position) {

                if (IS_DEBUG) {
                    Log.d(TAG, "onLocationChanged: " + SystemClock.elapsedRealtime() / 1000 + "  " + Arrays.toString(position));
                }
                applyNewCoordinate(position[0], position[1], 1, 1);
            }
        });
        Collection<SpaceBeacon> floorSpaceBeacons = new ArrayList<>();
        for(BeaconModel beacon : floor.getBeacons()){
                SpaceBeacon spaceBeacon = new BluetoothBeacon("todo", beacon.getMajor(), beacon.getMinor(),
                        beacon.getTxpower(), 2, beacon.getPositionX(), beacon.getPositionY(), beacon.getPositionZ());
            floorSpaceBeacons.add(spaceBeacon);
        }

        instance.setBeaconsInRegionLoader(new InMemoryBeaconsLoader(floorSpaceBeacons, 10));
//        instance.registerListener(this);
//        instance.registerErrorListener(this);
//        instance.startTrackPosition();
    }

    @Override
    public void onPause() {
        super.onPause();
        instance.stop();
//        instance.unregisterListener(this);
//        instance.unregisterErrorListener(this);
//        instance.startTrackPosition();
    }

    @Override
    public void onMapSelected(int position) {
        //map.setCurrentFloorIndex(position - 1);
//        floor = map.getFloors().get(position - 1);
        mapView.setRoute(new float[0]);
        mapView.initMapImage(FileUtil.getLocacPath(getActivity(), floor.getMapPath()).getAbsolutePath(), floor.getPixelSize());
        final ProgressDialog progressDialog = new ProgressDialog(getActivity());

        File path = FileUtil.getLocacPath(getActivity(), floor.getGraphPath());
        getActivityBridge().getRouteHelper().initMapFromFile(FileUtil.getLocacPath(getActivity(), floor.getGraphPath()), new RouteHelper.MapProcessingListener() {
            @Override
            public void onMapProcessed() {
                progressDialog.hide();
                mapView.setEdges(getActivityBridge().getRouteHelper().getEdges());
            }

            @Override
            public void onFailed(@Nullable Throwable t) {
                progressDialog.hide();
                Toast.makeText(getActivity(), t.getMessage(), Toast.LENGTH_SHORT).show();
            }
        });

        //instance.setBeaconsPosition(ConverterUtil.toBeaconsPosition(floor.getBeacons()));
        mapView.setBeacons(floor.getBeacons());
//        List<Integer> inpointIdList = floor.getInpointIdList();
//        List<Inpoint> inpoints = new ArrayList<>();
//        for(int i : inpointIdList){
//            inpoints.add(getActivityBridge().getDbBridge().getInpointById(i));
//        }
//        //List<Inpoint> inpointsByMapId = getActivityBridge().getDbBridge().getInpointsByBuildingAndFloorId(map.getId(), position);
//        mapView.setInpoints(inpoints);

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

    public static Fragment makeInstance(Floor map) {
        IndoorMap2DFragment fragment = new IndoorMap2DFragment();
        Bundle bundle = new Bundle();
        bundle.putParcelable("mapView", map);
        fragment.setArguments(bundle);
        return fragment;
    }

//    @Override
//    public void onPositionChanged(float x, float y, float tx, float ty) {
//        applyNewCoordinate(x, y, tx, ty);
//    }

    private void applyNewCoordinate(float x, float y, float tx, float ty) {
        if (getActivity() == null) {
            return;
        }
        mapView.setCoordinates(tx, ty, x, y);

        Log.wtf("For Alexey.", "Current coords : x = " + x + " ;y = " + y + " ;tx = " + tx + " ;ty = " + ty);

        if (dest.x == 0 && dest.y == 0) {
            mapView.setRoute(new float[0]);
            return;
        }

        getActivityBridge().getRouteHelper().findPath(new PointF((float) (x / floor.getPixelSize()), (float) (y / floor.getPixelSize())), dest, new RouteHelper.RouteListener() {
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

//    @Override
//    public void onError(Throwable t) {
//
//    }

    @Override
    public void onInpoictClicked(final Inpoint inpoint) {
        getActivityBridge().getRouteHelper().findPath(mapView.getCoordinates(), new PointF((float) inpoint.getX(), (float) inpoint.getY()), new RouteHelper.RouteListener() {
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

        bottomSheet.getBottomViewWrapper().setVisibility(View.GONE);
        bottomSheet.getCancelButton().setVisibility(View.GONE);
        bottomSheet.getHintContainer().setVisibility(View.GONE);
    }
}
