package khpi.com.demo.utils;

import com.hackoeur.jglm.Mat3;
import com.hackoeur.jglm.Mat4;
import com.hackoeur.jglm.Vec3;
import com.hackoeur.jglm.Vec4;

import java.util.ArrayList;
import java.util.List;

public final class GeometryUtils {

    public static double calcAngle(final Vec3 position, final Vec3 cameraPosition) {
        if (position.getX() == cameraPosition.getX()) {
            if (position.getZ() < cameraPosition.getZ()) {
                return 0;
            } else {
                return 180;
            }
        }

        if (position.getZ() == cameraPosition.getZ()) {
            if (position.getX() < cameraPosition.getX()) {
                return 90;
            } else {
                return -90;
            }
        }

        Vec3 v1 = new Vec3(position.getX(), position.getY(), position.getZ() + 1).subtract(position);
        Vec3 v2 = cameraPosition.subtract(position);

        float angle = (float) Math.toDegrees(v1.angleInRadians(v2));

        if (position.getX() > cameraPosition.getX()) {
            angle = -angle;
        }

        return angle;
    }

    public static Mat3 convert(Mat4 mat4) {
        List<Vec3> vectors = new ArrayList<>();

        for (int i = 0; i < 3; i++) {
            Vec4 v = mat4.getColumn(i);
            vectors.add(new Vec3(v.getX(), v.getY(), v.getZ()));
        }

        return new Mat3(vectors.get(0), vectors.get(1), vectors.get(2));
    }
}
