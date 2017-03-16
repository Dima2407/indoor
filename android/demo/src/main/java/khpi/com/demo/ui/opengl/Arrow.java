package khpi.com.demo.ui.opengl;

import com.hackoeur.jglm.Mat4;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import static android.opengl.GLES20.GL_FLOAT;
import static android.opengl.GLES20.GL_LINES;
import static android.opengl.GLES20.glDrawArrays;
import static android.opengl.GLES20.glLineWidth;
import static android.opengl.GLES20.glVertexAttribPointer;

/**
 * Created by vladk on 9/18/2016.
 */

public class Arrow extends SceneObject {

    private static final float[] triangleVerticesData = {
            //TOP
            -2.0f, 0.0f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, -1.2f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, 1.2f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, 0.6f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, -0.6f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            2f, 0.6f, 0.25f,
            0.0f, 0.0f, 1.0f, 1.0f,

            -0.4f, -0.6f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            2f, -0.6f, 0.25f,
            0.0f, 0.0f, 1.0f, 1.0f,

            2f, 0.6f, 0.25f,
            0.0f, 0.0f, 1.0f, 1.0f,

            //FRONT
            -0.4f, 1.2f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, 1.2f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -2.0f, 0.0f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, 1.2f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -2.0f, 0.0f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -2.0f, 0.0f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -2.0f, 0.0f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -2.0f, 0.0f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, -1.2f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -2.0f, 0.0f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, -1.2f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, -1.2f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, -1.2f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, -1.2f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, -0.6f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, -1.2f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, -0.6f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, -0.6f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, -0.6f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, -0.6f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            2f, -0.6f, 0.25f,
            0.0f, 0.0f, 1.0f, 1.0f,

            -0.4f, -0.6f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            2f, -0.6f, -0.25f,
            0.0f, 0.0f, 1.0f, 1.0f,

            2f, -0.6f, 0.25f,
            0.0f, 0.0f, 1.0f, 1.0f,

            2f, -0.6f, 0.25f,
            0.0f, 0.0f, 1.0f, 1.0f,

            2f, -0.6f, -0.25f,
            0.0f, 0.0f, 1.0f, 1.0f,

            2f, 0.6f, 0.25f,
            0.0f, 0.0f, 1.0f, 1.0f,

            2f, -0.6f, -0.25f,
            0.0f, 0.0f, 1.0f, 1.0f,

            2f, 0.6f, -0.25f,
            0.0f, 0.0f, 1.0f, 1.0f,

            2f, 0.6f, 0.25f,
            0.0f, 0.0f, 1.0f, 1.0f,

            2f, 0.6f, 0.25f,
            0.0f, 0.0f, 1.0f, 1.0f,

            2f, 0.6f, -0.25f,
            0.0f, 0.0f, 1.0f, 1.0f,

            -0.4f, 0.6f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            2f, 0.6f, -0.25f,
            0.0f, 0.0f, 1.0f, 1.0f,

            -0.4f, 0.6f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, 0.6f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, 0.6f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, 0.6f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, 1.2f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, 0.6f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, 1.2f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, 1.2f, 0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            //BOTTOM
            -2f, 0.0f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, -1.2f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, 1.2f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, 0.6f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            -0.4f, -0.6f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            2f, 0.6f, -0.25f,
            0.0f, 0.0f, 1.0f, 1.0f,

            -0.4f, -0.6f, -0.25f,
            0.0f, 1.0f, 0.0f, 1.0f,

            2f, -0.6f, -0.25f,
            0.0f, 0.0f, 1.0f, 1.0f,

            2f, 0.6f, -0.25f,
            0.0f, 0.0f, 1.0f, 1.0f,
    };

    private static final float[] bordersLinesData = {
            //TOP
            -2f, 0.0f, 0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
            -0.4f, -1.2f, 0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,

            -0.4f, -1.2f, 0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
            -0.4f, -0.6f, 0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,

            -0.4f, -0.6f, 0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
            2f, -0.6f, 0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,

            2f, -0.6f, 0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
            2f, 0.6f, 0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,

            2f, 0.6f, 0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
            -0.4f, 0.6f, 0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,

            -0.4f, 0.6f, 0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
            -0.4f, 1.2f, 0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,

            -0.4f, 1.2f, 0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
            -2f, 0.0f, 0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,

            //FRONT
            -2f, 0.0f, 0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
            -2f, 0.0f, -0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,

            -0.4f, -1.2f, 0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
            -0.4f, -1.2f, -0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,

            -0.4f, 1.2f, 0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
            -0.4f, 1.2f, -0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,

            2f, -0.6f, 0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
            2f, -0.6f, -0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,

            2f, 0.6f, 0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
            2f, 0.6f, -0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,

            //BOTTOM
            -2f, 0.0f, -0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
            -0.4f, -1.2f, -0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,

            -0.4f, -1.2f, -0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
            -0.4f, -0.6f, -0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,

            -0.4f, -0.6f, -0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
            2f, -0.6f, -0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,

            2f, -0.6f, -0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
            2f, 0.6f, -0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,

            2f, 0.6f, -0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
            -0.4f, 0.6f, -0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,

            -0.4f, 0.6f, -0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
            -0.4f, 1.2f, -0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,

            -0.4f, 1.2f, -0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
            -2f, 0.0f, -0.25f,
            0.0f, 0.0f, 0.0f, 1.0f,
    };

    private FloatBuffer linesVertices;
    private double previousAngle;

    public Arrow() {
        super();

        linesVertices = ByteBuffer
                .allocateDirect(bordersLinesData.length * BYTES_PER_FLOAT)
                .order(ByteOrder.nativeOrder())
                .asFloatBuffer()
                .put(bordersLinesData);
    }

    @Override
    protected FloatBuffer getTextureBuffer() {
        return null;
    }

    @Override
    protected FloatBuffer getWrapperVertexBuffer() {
        return ByteBuffer
                .allocateDirect(triangleVerticesData.length * BYTES_PER_FLOAT)
                .order(ByteOrder.nativeOrder())
                .asFloatBuffer()
                .put(triangleVerticesData);
    }

    @Override
    public void draw(Mat4 viewMatrix, Mat4 projectionMatrix) {
        super.draw(viewMatrix, projectionMatrix);

        linesVertices.position(0);
        glVertexAttribPointer(
                positionHandle,
                POSITION_DATA_SIZE,
                GL_FLOAT,
                false,
                STRIDE_BYTES,
                linesVertices
        );

        linesVertices.position(3);
        glVertexAttribPointer(
                colorHandle,
                COLOR_DATA_SIZE,
                GL_FLOAT,
                false,
                STRIDE_BYTES,
                linesVertices
        );

        glLineWidth(2f);
        glDrawArrays(GL_LINES, 0, bordersLinesData.length / 7);
    }

    @Override
    public void rotateObject(final double rotationAngle, final Axis axis) {
        double angleToRotate = rotationAngle;

        if (axis.equals(Axis.Z)) {
            angleToRotate = rotationAngle - previousAngle;

            previousAngle = rotationAngle;
        }

        super.rotateObject(angleToRotate, axis);
    }
}
