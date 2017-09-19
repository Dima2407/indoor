package khpi.com.demo.ui.opengl;

import android.content.Context;
import android.location.Location;
import android.location.LocationManager;

import khpi.com.demo.model.Step;
import com.hackoeur.jglm.Vec3;

import java.util.List;

import static android.opengl.GLES20.glGetAttribLocation;
import static android.opengl.GLES20.glGetUniformLocation;

public final class DirectionRenderer extends BaseRender {

    private Arrow secondArrow;

    private Step step;
    private Location currentPosition= new Location(LocationManager.GPS_PROVIDER);
    private float azimuth;

    public DirectionRenderer(Context context) {
        super(context, false);
    }

    @Override
    protected void initScene() {
        int program = Shaders.loadShaders(Shaders.VERTEX_SHADER, Shaders.SIMPLE_FRAGMENT_SHADER_WITH_ATTRIBUTE);

        int positionHandle = glGetAttribLocation(program, "a_Position");
        int mvpMatrixHandle = glGetUniformLocation(program, "u_MVPMatrix");
        int colorHandle = glGetAttribLocation(program, "a_Color");

        setProgramHandle(program);

        getScene().initShaders(positionHandle, colorHandle, mvpMatrixHandle, -1, -1);

        List<SceneObject> objects = getScene().getObjects(Arrow.class);
        if (objects != null && objects.size() == 2) {
            return;
        }

        Arrow firstArrow = new Arrow();
        firstArrow.rotateObject(-90, Axis.X);
        firstArrow.rotateObject(-90, Axis.Z);
        firstArrow.scaleObject(0.37f, 0.5f, 0.7f);

        getScene().addSceneObject(firstArrow);

        secondArrow = new Arrow();
        secondArrow.rotateObject(-90, Axis.X);
        secondArrow.translateObject(new Vec3(0, 0, -2));
        secondArrow.scaleObject(0.45f, 0.5f, 0.7f);

        getScene().addSceneObject(secondArrow);
        getActiveCamera().moveCameraToPosition(new Vec3(0, 2.4f, 1f));
        getActiveCamera().rotate(0, -55f, 0);
    }

    @Override
    protected void onObjectPicked(SceneObject object) {

    }

    @Override
    protected void update() {
        if (currentPosition == null || step == null || secondArrow == null) {
            return;
        }

        Location location = new Location(LocationManager.GPS_PROVIDER);
        location.setLatitude(currentPosition.getLatitude());
        location.setLongitude(currentPosition.getLongitude());

        Location location1 = new Location(LocationManager.GPS_PROVIDER);
        location1.setLatitude(step.getEndLatitude());
        location1.setLongitude(step.getEndLongitude());

        float angle = location.bearingTo(location1);

        secondArrow.rotateObject(azimuth - angle - 90, Axis.Z);
    }

    public void setRouteStep(Step step) {
        this.step = step;
    }

    void onDeviceRotated(float azimuth, float pitch, float roll) {
        this.azimuth = azimuth;
    }

    void onCurrentPositionChanged(double longitude, double latitude) {
        currentPosition.setLatitude(latitude);
        currentPosition.setLongitude(longitude);
    }
}
