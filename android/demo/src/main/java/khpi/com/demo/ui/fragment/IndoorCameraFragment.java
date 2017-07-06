package khpi.com.demo.ui.fragment;

import android.graphics.PointF;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.support.annotation.Nullable;
import android.support.design.widget.CoordinatorLayout;
import android.support.v4.app.Fragment;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.RelativeLayout;
import android.widget.Toast;

import khpi.com.demo.R;
import khpi.com.demo.core.bridge.OrientationBridge;
import khpi.com.demo.model.Floor;
import khpi.com.demo.model.Inpoint;
import khpi.com.demo.model.Point;
import khpi.com.demo.model.Route;
import khpi.com.demo.model.Step;
import khpi.com.demo.routing.RouteHelper;
import khpi.com.demo.ui.BottomSheet;
import khpi.com.demo.ui.adapter.RouteDataAdapter;
import khpi.com.demo.ui.opengl.BaseRender;
import khpi.com.demo.ui.opengl.IndoorCameraOverlay;
import khpi.com.demo.ui.opengl.SceneObject;
import khpi.com.demo.ui.view.CameraPreview;
import khpi.com.demo.ui.view.IndoorRadarView;
import khpi.com.demo.utils.FileUtil;
import khpi.com.demo.utils.ManeuverHelper;
import khpi.com.demo.utils.PixelsUtil;
import pro.i_it.indoor.IndoorLocationManager;
import pro.i_it.indoor.OnLocationUpdateListener;
import pro.i_it.indoor.masks.ResourcesMaskTableFetcher;
import pro.i_it.indoor.mesh.MeshConfig;

import com.squareup.picasso.Picasso;

import java.util.ArrayList;
import java.util.List;

public final class IndoorCameraFragment extends BaseCameraFragment {

    private OrientationBridge.DeviceOrientationListener deviceOrientationListener;
    private IndoorCameraOverlay indoorCameraOverlay;
    private CameraPreview cameraPreview;
    private Floor floor;

    private IndoorLocationManager instance;
    private IndoorRadarView radarView;

    private BottomSheet bottomSheet;
    private RecyclerView.OnScrollListener scrollListener;
    private Point destinationPoint;

    public static String KEY_PARCELABLE_FLOOR = "floor";

    public static Fragment makeInstance(Floor floor){
        IndoorCameraFragment fragment = new IndoorCameraFragment();
        Bundle bundle = new Bundle();
        bundle.putParcelable(KEY_PARCELABLE_FLOOR, floor);
        fragment.setArguments(bundle);
        return fragment;
    }

    @Override
    public void onCreate(@Nullable final Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        floor = getArguments().getParcelable(KEY_PARCELABLE_FLOOR);
        instance = getActivityBridge().getProjectApplication().getLocalManager();
    }

    @Nullable
    @Override
    public View onCreateView(final LayoutInflater inflater, @Nullable final ViewGroup container, @Nullable final Bundle savedInstanceState) {
        return inflater.inflate(R.layout.indoor_camera_fragment, container, false);
    }

    @Override
    public void onViewCreated(final View view, @Nullable final Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        bottomSheet = getActivityBridge().getBottomSheet();
        bottomSheet.getCancelButton().setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                getActivityBridge().getRouteHelper().clear();

                bottomSheet.getBottomViewWrapper().setVisibility(View.GONE);
                bottomSheet.getHintContainer().setVisibility(View.GONE);
                bottomSheet.getCancelButton().setVisibility(View.GONE);

                radarView.setRoute(new float[0]);

                destinationPoint = null;

                IndoorMap2DFragment.dest.x = 0;
                IndoorMap2DFragment.dest.y = 0;

                RelativeLayout.LayoutParams layoutParams = (RelativeLayout.LayoutParams) radarView.getLayoutParams();
                layoutParams.bottomMargin = PixelsUtil.dpToPx(16, getContext());
                radarView.setLayoutParams(layoutParams);
            }
        });

        scrollListener = new RecyclerView.OnScrollListener() {
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

        indoorCameraOverlay = (IndoorCameraOverlay) view.findViewById(R.id.indoor_camera_map_overlay);
        cameraPreview = new CameraPreview(getContext());
        radarView = (IndoorRadarView) view.findViewById(R.id.radar);
        radarView.setVisibility(getActivityBridge().getProjectApplication().getSharedHelper().drawInRadar() ? View.VISIBLE : View.GONE);
        ((FrameLayout) view.findViewById(R.id.outdoor_camera_preview)).addView(cameraPreview);

        view.findViewById(R.id.indoor_camera_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(final View view) {
                getActivityBridge().getLauncher().launchIndoorMapFragment(floor);
            }
        });
    }

    @Override
    public void onStart() {
        super.onStart();

        initCamera();
        cameraPreview.updateCamera(getCamera());

        final boolean useBinaryMask = getActivityBridge().getProjectApplication().getSharedHelper().useBinaryMask();
        instance.setMode(useBinaryMask ? IndoorLocationManager.Mode.STANDARD_BEACON_NAVIGATOR : IndoorLocationManager.Mode.SENSOR_BEACON_NAVIGATOR);

        if (floor.getGraphPath().contains("/mapData/8/")) {
            //it-jim
            instance.useMask(new MeshConfig(36,24,0.3,0.3), new ResourcesMaskTableFetcher(getResources(), R.raw.masktable1));
        }else {
            //kaa
            instance.useMask(new MeshConfig(22,44,0.3,0.3), new ResourcesMaskTableFetcher(getResources(), R.raw.masktable2));
        }
        instance.start();
        instance.setOnLocationUpdateListener(new OnLocationUpdateListener() {
            @Override
            public void onLocationChanged(float[] position) {
                onNewPosition(position[0], position[1]);
            }
        });

        deviceOrientationListener = new OrientationBridge.DeviceOrientationListener() {
            @Override
            public void onOrientationUpdated(final float azimuth, final float pitch, final float roll) {
                indoorCameraOverlay.onOrientationChanged(azimuth, pitch, roll);
            }
        };

        indoorCameraOverlay.setOnObjectPickedListener(new BaseRender.OnObjectPickedListener() {
            @Override
            public void onObjectPicked(SceneObject pickedObject) {
                destinationPoint = (Point) pickedObject.getTag();

                Toast.makeText(getContext(), "You selected " + destinationPoint.getTitle(), Toast.LENGTH_SHORT).show();
            }
        });

        getActivityBridge().getOrientationBridge().startOrientationTracking(deviceOrientationListener);

        radarView.setRoute(new float[0]);
        radarView.initMapImage(FileUtil.getLocacPath(getActivity(), floor.getMapPath()).getAbsolutePath(), floor.getPixelSize());
    }

    private void onNewPosition(final float x, final float y) {
        if (getContext() == null) {
            return;
        }
        indoorCameraOverlay.onCurrentPositionChanged(x * floor.getPixelSize(), y * floor.getPixelSize());

        List<Inpoint> inpoints = getActivityBridge().getDbBridge().getInpointByFloorId(floor.getId());
        if (destinationPoint == null) {
            indoorCameraOverlay.updateInpoints(inpoints, floor);
        } else {
            ArrayList<Point> data = new ArrayList<>();
            data.add(destinationPoint);
            indoorCameraOverlay.setPoiData(data);
        }

        radarView.setInpoints(inpoints);
        getActivity().runOnUiThread(new Runnable() {
            @Override
            public void run() {
                radarView.setCoordinates(0, 0, x, y);
            }
        });
        RouteHelper.RouteListener routeListener = new RouteHelper.RouteListener() {
            @Override
            public void onRouteFound(final float[] route) {
                if (getContext() == null) {
                    return;
                }
                radarView.setRoute(route);

                new Handler(Looper.getMainLooper()).post(new Runnable() {
                    @Override
                    public void run() {
                        onNewRoute(route);
                    }
                });
            }

            @Override
            public void onFail() {
                if (getContext() == null) {
                    return;
                }
                bottomSheet.getHintContainer().setVisibility(View.GONE);
                bottomSheet.getBottomViewWrapper().setVisibility(View.GONE);
                bottomSheet.getCancelButton().setVisibility(View.GONE);
                radarView.setRoute(new float[0]);
                getActivityBridge().getRouteHelper().clear();
                RelativeLayout.LayoutParams layoutParams = (RelativeLayout.LayoutParams) radarView.getLayoutParams();
                layoutParams.bottomMargin = PixelsUtil.dpToPx(16, getContext());
                radarView.setLayoutParams(layoutParams);
            }
        };

        PointF currentPosition = new PointF((float) (x / floor.getPixelSize()), (float) (y / floor.getPixelSize()));

        if (destinationPoint != null) {
            getActivityBridge().getRouteHelper().findPath(currentPosition, new PointF((float) (destinationPoint.getMercatorX() / floor.getPixelSize()), (float) (destinationPoint.getMercatorY() / floor.getPixelSize())), instance, routeListener);
        } else {
            getActivityBridge().getRouteHelper().updateRoute(currentPosition, instance, routeListener);
        }
    }

    @Override
    public void onResume() {
        super.onResume();

        indoorCameraOverlay.onResume();
    }

    private void onNewRoute(float[] route) {
        radarView.setRoute(route);

        bottomSheet.getBottomViewWrapper().setVisibility(View.VISIBLE);
        bottomSheet.getCancelButton().setVisibility(View.VISIBLE);

        RelativeLayout.LayoutParams layoutParams = (RelativeLayout.LayoutParams) radarView.getLayoutParams();
        layoutParams.bottomMargin = PixelsUtil.dpToPx(96, getContext());
        radarView.setLayoutParams(layoutParams);

        List<RouteHelper.Motion> motions = getActivityBridge().getRouteHelper().getMoutions(route);

        final Route r = getActivityBridge().getRouteHelper().buildRoute(motions, floor);

        indoorCameraOverlay.queueEvent(new Runnable() {
            @Override
            public void run() {
                indoorCameraOverlay.onNewRoute(r);
            }
        });

        if (r == null || r.getSteps().isEmpty()) {
            return;
        }


        initHint(r);
        initTotalData(r);

        bottomSheet.getDataList().addOnScrollListener(scrollListener);

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

    @Override
    public void onPause() {
        super.onPause();
        instance.stop();
        indoorCameraOverlay.onPause();
    }

    @Override
    public void onStop() {
        super.onStop();
        bottomSheet.getBottomViewWrapper().setVisibility(View.GONE);
        bottomSheet.getHintContainer().setVisibility(View.GONE);
        bottomSheet.getCancelButton().setVisibility(View.GONE);

        getActivityBridge().getOrientationBridge().stopOrientationTracking(deviceOrientationListener);

        getActivityBridge().getBottomSheet().getDataList().removeOnScrollListener(scrollListener);
    }
}
