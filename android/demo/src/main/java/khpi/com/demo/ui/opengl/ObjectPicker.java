package khpi.com.demo.ui.opengl;

import android.opengl.GLES20;
import android.support.annotation.Nullable;

import com.hackoeur.jglm.Mat4;
import com.hackoeur.jglm.Vec3;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.util.ArrayList;
import java.util.List;

import static android.opengl.GLES20.GL_COLOR_BUFFER_BIT;
import static android.opengl.GLES20.GL_DEPTH_BUFFER_BIT;
import static android.opengl.GLES20.GL_RGBA;
import static android.opengl.GLES20.GL_TRIANGLES;
import static android.opengl.GLES20.GL_UNPACK_ALIGNMENT;
import static android.opengl.GLES20.GL_UNSIGNED_BYTE;
import static android.opengl.GLES20.glClear;
import static android.opengl.GLES20.glClearColor;
import static android.opengl.GLES20.glDisableVertexAttribArray;
import static android.opengl.GLES20.glDrawArrays;
import static android.opengl.GLES20.glEnableVertexAttribArray;
import static android.opengl.GLES20.glFinish;
import static android.opengl.GLES20.glFlush;
import static android.opengl.GLES20.glGetAttribLocation;
import static android.opengl.GLES20.glGetUniformLocation;
import static android.opengl.GLES20.glPixelStorei;
import static android.opengl.GLES20.glReadPixels;
import static android.opengl.GLES20.glUniform4f;
import static android.opengl.GLES20.glUniformMatrix4fv;
import static android.opengl.GLES20.glUseProgram;
import static android.opengl.GLES20.glVertexAttribPointer;

public final class ObjectPicker {

    private final List<SceneObject> sceneObjects;

    private int mvpHandle;
    private int colorHandle;
    private int positionHandle;

    private int programHandle;
    private int height;

    public static ObjectPicker getInstance() {
        return InstanceHolder.instance;
    }

    public void removeAll() {
        sceneObjects.clear();
    }

    private static final class InstanceHolder {

        private static ObjectPicker instance = new ObjectPicker();
    }

    private ObjectPicker() {
        sceneObjects = new ArrayList<>();
    }

    public void initialize(final int height) {
        programHandle = Shaders.loadShaders(Shaders.SIMPLE_VERTEX_SHADER, Shaders.SIMPLE_FRAGMENT_SHADER);

        mvpHandle = glGetUniformLocation(programHandle, "u_MVPMatrix");
        colorHandle = glGetUniformLocation(programHandle, "u_Color");
        positionHandle = glGetAttribLocation(programHandle, "a_Position");

        this.height = height;
    }

    public void addObject(SceneObject object) {
        sceneObjects.add(object);
    }

    public void removeObject(SceneObject object) {
        sceneObjects.remove(object);
    }

    @Nullable
    public SceneObject tryPickObjectAtPosition(Vec3 position, Mat4 viewMatrix, Mat4 projectionMatrix) {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(programHandle);

        glEnableVertexAttribArray(positionHandle);

        for (int i = 0; i < sceneObjects.size(); i++) {
            SceneObject object = sceneObjects.get(i);

            Mat4 mvp = projectionMatrix.multiply(viewMatrix.multiply(object.getModelMatrix()));

            glUniformMatrix4fv(mvpHandle, 1, false, mvp.getBuffer());

            float r = (i & 0x000000FF) / 255.0f;
            float g = ((i & 0x0000FF00) >> 8) / 255.0f;
            float b = ((i & 0x00FF0000) >> 16) / 255.0f;

            glUniform4f(colorHandle, r, g, b, 1f);

            FloatBuffer wrapperVertexBuffer = object.getWrapperVertexBuffer();

            wrapperVertexBuffer.position(0);
            glVertexAttribPointer(
                    positionHandle,
                    3,
                    GLES20.GL_FLOAT,
                    false,
                    28,
                    wrapperVertexBuffer
            );

            glDrawArrays(GL_TRIANGLES, 0, wrapperVertexBuffer.capacity() / 7);
        }

        glDisableVertexAttribArray(positionHandle);

        glFlush();
        glFinish();

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        byte[] color = new byte[4];
        ByteBuffer colorBuffer = ByteBuffer.wrap(color)
                .order(ByteOrder.nativeOrder());

        colorBuffer.position(0);

        glReadPixels((int) position.getX(), height - (int) position.getY(), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, colorBuffer);

        int pickedId = color[0] + color[1] * 256 + color[2] * 256 * 256;

        if (pickedId < 0) {
            return null;
        }

        return sceneObjects.get(pickedId);
    }
}
