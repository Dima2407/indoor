package khpi.com.demo.ui.opengl;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

public final class RoadElement extends SceneObject {

    private static final float START_X = -0.5f;
    private static final float END_X = 0.5f;
    private static final float START_Y = 0.75f;
    private static final float END_Y = -0.75f;
    private static final float START_Z = 0.0f;
    private static final float END_Z = 0.0f;

    private static final float[] wrapperVertex = {
            START_X, START_Y, START_Z,
            1, 1, 1, 1,
            START_X, END_Y, END_Z,
            1, 1, 1, 1,
            END_X, START_Y, START_Z,
            1, 1, 1, 1,

            START_X, END_Y, END_Z,
            1, 1, 1, 1,
            END_X, END_Y, END_Z,
            1, 1, 1, 1,
            END_X, START_Y, START_Z,
            1, 1, 1, 1
    };

    private static final float[] texCoordinates = {
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f
    };

    private float[] wrapperVertexData = null;
    private float[] textureData = null;

    @Override
    protected FloatBuffer getTextureBuffer() {
        float[] texture = textureData == null ? texCoordinates : textureData;

        return ByteBuffer
                .allocateDirect(texture.length * BYTES_PER_FLOAT)
                .order(ByteOrder.nativeOrder())
                .asFloatBuffer()
                .put(texture);
    }

    @Override
    protected FloatBuffer getWrapperVertexBuffer() {
        float[] vertex = wrapperVertexData == null ? wrapperVertex : wrapperVertexData;

        return ByteBuffer
                .allocateDirect(vertex.length * BYTES_PER_FLOAT)
                .order(ByteOrder.nativeOrder())
                .asFloatBuffer()
                .put(vertex);
    }

    public void setWrapperVertexData(float[] wrapperVertex) {
        this.wrapperVertexData = wrapperVertex;
    }

    public void setTextureData(float[] textureData) {
        this.textureData = textureData;
    }
}
