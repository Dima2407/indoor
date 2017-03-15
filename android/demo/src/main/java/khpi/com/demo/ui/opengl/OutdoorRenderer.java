package khpi.com.demo.ui.opengl;

import android.content.Context;
import android.os.Handler;
import android.os.Looper;

import khpi.com.demo.R;
import khpi.com.demo.model.Point;
import khpi.com.demo.model.Route;
import khpi.com.demo.model.Step;
import khpi.com.demo.n.NativeFacade;
import khpi.com.demo.utils.GeoUtils;
import khpi.com.demo.utils.GeometryUtils;
import com.hackoeur.jglm.Vec3;
import com.hackoeur.jglm.support.FastMath;

import java.util.ArrayList;
import java.util.List;

class OutdoorRenderer extends BaseRender {

    private static final float DYNAMIC_SCALE_DISTANCE_THRESHOLD = 1000;
    private boolean canChangeScene;

    private List<Point> poiList;
    private boolean updatePoi;

    private OnObjectPickedListener onObjectPickedListener;
    private Handler handler;

    private boolean useDynamicScaling;
    private boolean useMeshing;

    private Route previousRoute;
    private boolean useConverting;

    public OutdoorRenderer(Context context) {
        super(context, true);

        handler = new Handler(Looper.getMainLooper());
        updatePoi = true;

        poiList = new ArrayList<>();
        useDynamicScaling = true;
        useMeshing = true;
        useConverting = true;
    }

    @Override
    protected void initScene() {
        canChangeScene = true;
    }

    @Override
    protected void onObjectPicked(final SceneObject object) {
        if (onObjectPickedListener == null) {
            return;
        }

        handler.post(new Runnable() {
            @Override
            public void run() {
                onObjectPickedListener.onObjectPicked(object);
            }
        });
    }

    @Override
    protected void update() {
        if (!updatePoi) {
            return;
        }

        updatePoints();
    }

    private void updatePoints() {
        updatePoi = false;

        if (poiList.isEmpty()) {
            return;
        }

        getScene().removeAllElementsByClass(PoiTable.class);
        ObjectPicker.getInstance().removeAll();

        for (int i = 0; i < poiList.size(); i++) {
            Point point = poiList.get(i);

            float x = (float) point.getMercatorX();
            float z = (float) -point.getMercatorY();

            float translateX = x - getActiveCamera().getRealPosition().getX();
            float translateZ = z - getActiveCamera().getRealPosition().getZ();

            PoiTable poiTable = new PoiTable();
            poiTable.setTag(point);
            poiTable.translateObject(new Vec3(translateX, 1f, translateZ));

            float cameraX = getActiveCamera().getRealPosition().getX();
            float cameraY = -getActiveCamera().getRealPosition().getZ();

            float deltaX = (float) (cameraX - point.getMercatorX());
            float deltaY = (float) (cameraY - point.getMercatorY());

            float distance = FastMath.sqrtFast(deltaX * deltaX + deltaY * deltaY);

            poiTable.setTexture(getTextureManger().generatePoiTexture(point, distance));
            double rotationAngle = GeometryUtils.calcAngle(poiTable.getPosition(), getActiveCamera().getPosition());
            poiTable.rotateObject(rotationAngle, Axis.Y);

            if (useDynamicScaling) {
                poiTable.scaleObject(getScaleFactor(distance));
            } else {
                poiTable.scaleObject(0.35f);
            }

            ObjectPicker.getInstance().addObject(poiTable);

            getScene().addSceneObject(poiTable);
        }
    }

    private float getScaleFactor(float distance) {
        if (distance > DYNAMIC_SCALE_DISTANCE_THRESHOLD) {
            return 1;
        }

        if (distance < 5) {
            return 0.3f;
        }

        if (distance < 12.5) {
            return 0.6f;
        }

        if (distance < 25) {
            return 1;
        }

        if (distance < 50) {
            return 2;
        }

        if (distance < 100) {
            return 5;
        }

        if (distance < 200) {
            return 10;
        }

        if (distance < 250) {
            return 15;
        }

        if (distance < 300) {
            return 20;
        }

        if (distance < 400) {
            return 25;
        }

        if (distance < 500) {
            return 30;
        }

        if (distance < 600) {
            return 40;
        }

        if (distance < 700) {
            return 50;
        }

        if (distance < 800) {
            return 60;
        }

        return 75;
    }

    void onDeviceOrientationChanged(float azimuth, float pitch, float roll) {
        getActiveCamera().rotate(-azimuth, 0, roll);
    }

    void onCurrentPositionChanged(double x, double y) {
        if (!canChangeScene) {
            return;
        }

        Vec3 cameraPosition = new Vec3((float) x, 1.5f, (float) -y);

        getActiveCamera().moveCameraToPosition(cameraPosition);

        onNewRoute(previousRoute);
        updatePoi = true;
    }

    public void setPoiData(final List<Point> data) {
        poiList = data;
        updatePoi = true;
    }

    public void setOnObjectPickedListener(OnObjectPickedListener listener) {
        this.onObjectPickedListener = listener;
    }

    public void onNewRoute(final Route route) {
        if (!canChangeScene) {
            return;
        }

        getScene().removeAllElementsByClass(RoadElement.class);

        if (route == null) {
            previousRoute = null;
            return;
        }

        List<RoadElement> roadSteps = buildRoadElements(route);
        getScene().addSceneObjects(roadSteps, RoadElement.class);

        previousRoute = route;
    }

    private List<RoadElement> buildRoadElements(final Route route) {
        List<Step> steps = route.getSteps();

        if (steps == null) {
            return null;
        }

        float[][] stepsCoordinates = new float[steps.size() + 1][2];

        int index = 0;

        for (int i = 0; i < steps.size(); i++) {
            Step step = steps.get(i);

            double startLongitude = step.getStartLongitude();
            double startLatitude = step.getStartLatitude();
            double endLongitude = step.getEndLongitude();
            double endLatitude = step.getEndLatitude();

            float startX;
            float startZ;
            float endX;
            float endZ;

            if (useConverting) {
                startX = (float) GeoUtils.convertLongitudeToMercatorX(startLongitude);
                startZ = (float) -GeoUtils.convertLatitudeToMercatorY(startLatitude);
                endX = (float) GeoUtils.convertLongitudeToMercatorX(endLongitude);
                endZ = (float) -GeoUtils.convertLatitudeToMercatorY(endLatitude);
            } else {
                startX = (float) startLongitude;
                startZ = (float) -startLatitude;
                endX = (float) endLongitude;
                endZ = (float) -endLatitude;
            }

            float relativeStartX = startX - getActiveCamera().getRealPosition().getX();
            float relativeStartZ = startZ - getActiveCamera().getRealPosition().getZ();

            float relativeEndX = endX - getActiveCamera().getRealPosition().getX();
            float relativeEndZ = endZ - getActiveCamera().getRealPosition().getZ();

            if (i == 0) {
                stepsCoordinates[index][0] = relativeStartX;
                stepsCoordinates[index++][1] = relativeStartZ;
            }

            stepsCoordinates[index][0] = relativeEndX;
            stepsCoordinates[index++][1] = relativeEndZ;
        }

        return NativeFacade.meshing(stepsCoordinates, loadTexture(R.drawable.road_icn_8, "road"));
    }

    protected void setUseDynamicScaling(final boolean useDynamicScaling) {
        this.useDynamicScaling = useDynamicScaling;
    }

    protected void setUseMeshing(final boolean useMeshing) {
        this.useMeshing = useMeshing;
    }

    protected void setUseConverting(boolean b) {
        useConverting = b;
    }
}
