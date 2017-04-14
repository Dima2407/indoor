package khpi.com.demo.ui.opengl;

import com.hackoeur.jglm.Mat4;
import com.hackoeur.jglm.Matrices;
import com.hackoeur.jglm.Vec3;

import java.nio.FloatBuffer;

import static android.opengl.GLES20.GL_FLOAT;
import static android.opengl.GLES20.GL_TEXTURE0;
import static android.opengl.GLES20.GL_TEXTURE_2D;
import static android.opengl.GLES20.GL_TRIANGLES;
import static android.opengl.GLES20.glActiveTexture;
import static android.opengl.GLES20.glBindTexture;
import static android.opengl.GLES20.glDrawArrays;
import static android.opengl.GLES20.glEnableVertexAttribArray;
import static android.opengl.GLES20.glUniform1i;
import static android.opengl.GLES20.glUniformMatrix4fv;
import static android.opengl.GLES20.glVertexAttribPointer;

public abstract class SceneObject {

    private static final int POSITION_OFFSET = 0;
    protected static final int POSITION_DATA_SIZE = 3;
    private static final int COLOR_OFFSET = POSITION_DATA_SIZE;
    protected static final int COLOR_DATA_SIZE = 4;

    private static final int TEXTURE_DATA_SIZE = 2;

    protected static final int BYTES_PER_FLOAT = 4;
    protected static final int STRIDE_BYTES = (POSITION_DATA_SIZE + COLOR_DATA_SIZE) * BYTES_PER_FLOAT;

    protected static int positionHandle;
    protected static int colorHandle;

    static private int mvpMatrixHandle;

    private static int textureHandle;
    private static int textureCoordHandle;

    private int textureDataHandle;

    private Mat4 modelMatrix;

    private Vec3 scenePosition;
    private Mat4 scaleMatrix;
    private Mat4 rotationMatrix;

    private Object tag;

    protected SceneObject() {
        modelMatrix = Mat4.MAT4_IDENTITY;
        rotationMatrix = Mat4.MAT4_IDENTITY;
        scaleMatrix = Mat4.MAT4_IDENTITY;

        scenePosition = Vec3.VEC3_ZERO;
    }

    protected abstract FloatBuffer getTextureBuffer();

    protected abstract FloatBuffer getWrapperVertexBuffer();

    public void translateObject(Vec3 position) {
        modelMatrix = modelMatrix.translate(scenePosition.getNegated());
        scenePosition = position;
        modelMatrix = modelMatrix.translate(scenePosition);
    }

    public void setTexture(int texture) {
        textureDataHandle = texture;
    }

    public void setShaderPointers(
            int positionHandle,
            int colorHandle,
            int mvpMatrixHandle,
            int textureCoordinateHandle,
            int textureHandle
    ) {

        SceneObject.positionHandle = positionHandle;
        SceneObject.colorHandle = colorHandle;
        SceneObject.mvpMatrixHandle = mvpMatrixHandle;
        SceneObject.textureHandle = textureHandle;
        SceneObject.textureCoordHandle = textureCoordinateHandle;
    }

    public Mat4 getModelMatrix() {
        return Mat4.MAT4_IDENTITY.translate(scenePosition).multiply(rotationMatrix.multiply(scaleMatrix));
    }

    public void rotateObject(double rotationAngle, Axis axis) {
        rotationMatrix = rotationMatrix.multiply(Matrices.rotate((float) Math.toRadians(rotationAngle), axis.getAxis()));
    }

    public void scaleObject(float scaleFactor) {
        scaleObject(scaleFactor, scaleFactor, scaleFactor);
    }

    public void scaleObject(float x, float y, float z) {
        scaleMatrix = new Mat4(
                x, 0, 0, 0,
                0, y, 0, 0,
                0, 0, z, 0,
                0, 0, 0, 1
        );
    }

    public Vec3 getPosition() {
        return scenePosition;
    }

    public Mat4 getRotScaleMatrix() {
        return rotationMatrix.multiply(scaleMatrix);
    }

    public Object getTag() {
        return tag;
    }

    public void setTag(final Object tag) {
        this.tag = tag;
    }

    public void draw(Mat4 viewMatrix, Mat4 projectionMatrix) {
        draw(Vec3.VEC3_ZERO, Mat4.MAT4_IDENTITY, viewMatrix, projectionMatrix);
    }

    public void draw(final Vec3 parentPos, Mat4 parentRotScaleMatrix, final Mat4 viewMatrix, final Mat4 projectionMatrix) {
        final Mat4 mvpMatrix = projectionMatrix.multiply(viewMatrix.multiply(
                Mat4.MAT4_IDENTITY.translate(parentPos).multiply(parentRotScaleMatrix.multiply(getModelMatrix())
                )));

        FloatBuffer wrapperVertexBuffer = getWrapperVertexBuffer();
        FloatBuffer textureBuffer = getTextureBuffer();

        glUniformMatrix4fv(mvpMatrixHandle, 1, false, mvpMatrix.getBuffer());

        wrapperVertexBuffer.position(POSITION_OFFSET);
        glVertexAttribPointer(
                positionHandle,
                POSITION_DATA_SIZE,
                GL_FLOAT,
                false,
                STRIDE_BYTES,
                wrapperVertexBuffer
        );
        glEnableVertexAttribArray(positionHandle);

        wrapperVertexBuffer.position(COLOR_OFFSET);
        glVertexAttribPointer(
                colorHandle,
                COLOR_DATA_SIZE,
                GL_FLOAT,
                false,
                STRIDE_BYTES,
                wrapperVertexBuffer
        );
        glEnableVertexAttribArray(colorHandle);

        if (textureHandle != -1 && textureBuffer != null) {
            glActiveTexture(GL_TEXTURE0);
            glUniform1i(textureHandle, 0);

            glBindTexture(GL_TEXTURE_2D, textureDataHandle);

            textureBuffer.position(0);
            glVertexAttribPointer(
                    textureCoordHandle,
                    TEXTURE_DATA_SIZE,
                    GL_FLOAT,
                    false,
                    0,
                    textureBuffer
            );
            glEnableVertexAttribArray(textureCoordHandle);
        }

        glDrawArrays(GL_TRIANGLES, 0, wrapperVertexBuffer.capacity() / 7);
    }
}