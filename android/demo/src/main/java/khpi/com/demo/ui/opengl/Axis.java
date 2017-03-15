package khpi.com.demo.ui.opengl;

import com.hackoeur.jglm.Vec3;

public final class Axis {

    private final Vec3 axis;

    public static final Axis X = new Axis(new Vec3(1, 0, 0));
    public static final Axis Y = new Axis(new Vec3(0, 1, 0));
    public static final Axis Z = new Axis(new Vec3(0, 0, 1));

    private Axis(Vec3 vec3) {
        axis = vec3;
    }

    public Vec3 getAxis() {
        return axis;
    }
}
