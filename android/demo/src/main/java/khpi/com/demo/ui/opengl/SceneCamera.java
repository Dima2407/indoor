package khpi.com.demo.ui.opengl;

import khpi.com.demo.utils.GeometryUtils;
import com.hackoeur.jglm.Mat4;
import com.hackoeur.jglm.Matrices;
import com.hackoeur.jglm.Vec3;

public final class SceneCamera {

    private static final float PROJECTION_NEAR = 0.1f;
    private static final float PROJECTION_FAR = 1000f;

    private static final float CAMERA_Y_POSITION_METERS = 1.5f;
    private static final float CAMERA_LOOK_AT_Y_METERS = -0.2f;
    private static final float CAMERA_LOOK_AT_Z_METERS = -1f;

    private Vec3 position;
    private Vec3 realPosition;
    private Vec3 direction;
    private Vec3 up;

    private Mat4 projectionMatrix;
    private float previousAzimuth;
    private float previousPitch;

    public SceneCamera() {
        final float eyeX = 0;
        final float eyeY = CAMERA_Y_POSITION_METERS;
        final float eyeZ = 0;

        final float lookX = 0;
        final float lookY = CAMERA_LOOK_AT_Y_METERS;
        final float lookZ = CAMERA_LOOK_AT_Z_METERS;

        final float upX = 0;
        final float upY = 1f;
        final float upZ = 0;

        position = new Vec3(eyeX, eyeY, eyeZ);
        direction = new Vec3(lookX, lookY, lookZ);
        up = new Vec3(upX, upY, upZ);

        realPosition = Vec3.VEC3_ZERO;
    }

    public void initProjection(double width, double height) {
        final float ratio = (float) (width / height);
        final float near = PROJECTION_NEAR;
        final float far = PROJECTION_FAR;

        projectionMatrix = Matrices.perspective(60, ratio, near, far);
    }

    public Mat4 getViewMatrix() {
        return Matrices.lookAt(position, position.add(direction), up);
    }

    public void moveCameraToPosition(Vec3 position) {
        this.realPosition = position;
    }

    public Vec3 getRealPosition() {
        return realPosition;
    }

    public void rotate(float azimuth, final float pitch, final float roll) {
        float deltaAzimuth = azimuth - previousAzimuth;
        float deltaPith = pitch - previousPitch;

        Vec3 cross = direction.cross(up);
        Mat4 mat4 = Matrices.rotate((float) Math.toRadians(deltaAzimuth), up).multiply(
                Matrices.rotate((float) Math.toRadians(deltaPith), cross)
        );

        direction = GeometryUtils.convert(mat4).multiply(direction);

        previousAzimuth = azimuth;
        previousPitch = pitch;
    }

    public Mat4 getProjectionMatrix() {
        return projectionMatrix;
    }

    public Vec3 getPosition() {
        return position;
    }
}
