package khpi.com.demo.ui.opengl;

import com.hackoeur.jglm.Mat4;
import com.hackoeur.jglm.Vec3;

import java.nio.FloatBuffer;
import java.util.ArrayList;
import java.util.List;

public class RoadStep extends SceneObject {

    private List<RoadElement> roadElements;

    public RoadStep() {
        roadElements = new ArrayList<>();
    }

    public void setRoadElements(final List<RoadElement> roadElements) {
        this.roadElements = roadElements;
    }

    @Override
    protected FloatBuffer getTextureBuffer() {
        return null;
    }

    @Override
    protected FloatBuffer getWrapperVertexBuffer() {
        return null;
    }

    @Override
    public void draw(final Mat4 viewMatrix, final Mat4 projectionMatrix) {
        if (roadElements.isEmpty()) {
            return;
        }

        Mat4 parentRotScaleMatrix = getRotScaleMatrix();
        Vec3 parentPos = getPosition();

        for (RoadElement roadElement : roadElements) {
            roadElement.draw(parentPos, parentRotScaleMatrix, viewMatrix, projectionMatrix);
        }
    }

    public List<RoadElement> getRoadElements() {
        return roadElements;
    }
}
