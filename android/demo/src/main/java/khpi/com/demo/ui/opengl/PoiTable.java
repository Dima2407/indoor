package khpi.com.demo.ui.opengl;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

public final class PoiTable extends SceneObject {

    private static final float[] vertexWrapper = {
            -2, 1f, 0,
            1, 1, 1, 1,
            -2, -1f, 0,
            1, 1, 1, 1,
            2, 1f, 0,
            1, 1, 1, 1,

            -2, -1f, 0,
            1, 1, 1, 1,
            2, -1f, 0,
            1, 1, 1, 1,
            2, 1f, 0,
            1, 1, 1, 1
    };

    private static final float[] texCoordinates = {
            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f
    };

    @Override
    protected FloatBuffer getTextureBuffer() {
        return ByteBuffer
                .allocateDirect(texCoordinates.length * BYTES_PER_FLOAT)
                .order(ByteOrder.nativeOrder())
                .asFloatBuffer()
                .put(texCoordinates);
    }

    @Override
    protected FloatBuffer getWrapperVertexBuffer() {
        return ByteBuffer
                .allocateDirect(vertexWrapper.length * BYTES_PER_FLOAT)
                .order(ByteOrder.nativeOrder())
                .asFloatBuffer()
                .put(vertexWrapper);
    }
}
