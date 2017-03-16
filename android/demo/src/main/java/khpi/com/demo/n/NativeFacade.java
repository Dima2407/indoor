package khpi.com.demo.n;

import khpi.com.demo.ui.opengl.Axis;
import khpi.com.demo.ui.opengl.RoadElement;
import com.hackoeur.jglm.Vec3;
import com.hackoeur.jglm.support.FastMath;

import java.util.ArrayList;
import java.util.List;

public class NativeFacade {

    static {
        System.loadLibrary("meshing");
    }

    public static List<RoadElement> meshing(float[][] coordinates, int texture) {
        if (coordinates.length == 0) {
            return new ArrayList<>();
        }

        int resultSize = calculateMeshing(coordinates);

        float[][] calculatedData = new float[resultSize][3];
        getData(calculatedData);

        List<RoadElement> roadElements = new ArrayList<>(resultSize);

        for (float[] elementData : calculatedData) {
            RoadElement element = new RoadElement();
            element.translateObject(new Vec3(elementData[0], -1, elementData[1]));
            element.scaleObject(1, 1, 1);
            element.rotateObject(90, Axis.X);
            element.rotateObject(FastMath.toDegrees(elementData[2]) - 90, Axis.Z);
            element.setTexture(texture);

            roadElements.add(element);
        }

        return roadElements;
    }

    private static native int calculateMeshing(float[][] coordinates);

    private static native void getData(float[][] data);
}