package khpi.com.demo.ui.opengl;

import android.content.Context;
import android.opengl.GLSurfaceView;

import com.hackoeur.jglm.Mat4;
import com.hackoeur.jglm.Vec3;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import static android.opengl.GLES20.GL_COLOR_BUFFER_BIT;
import static android.opengl.GLES20.GL_DEPTH_BUFFER_BIT;
import static android.opengl.GLES20.GL_DEPTH_TEST;
import static android.opengl.GLES20.GL_DITHER;
import static android.opengl.GLES20.GL_LESS;
import static android.opengl.GLES20.glClear;
import static android.opengl.GLES20.glClearColor;
import static android.opengl.GLES20.glDepthFunc;
import static android.opengl.GLES20.glDisable;
import static android.opengl.GLES20.glEnable;
import static android.opengl.GLES20.glGetAttribLocation;
import static android.opengl.GLES20.glGetUniformLocation;
import static android.opengl.GLES20.glUseProgram;
import static android.opengl.GLES20.glViewport;

public abstract class BaseRender implements GLSurfaceView.Renderer {

    private final Scene scene;

    private boolean tryPickObject;
    private Vec3 clickPosition;
    private TextureManager textureManager;

    private int programHandle;

    private boolean initializeObjectPicker;

    public BaseRender(Context context, boolean initializeObjectPicker) {
        this.initializeObjectPicker = initializeObjectPicker;

        scene = new Scene();
        textureManager = new TextureManager(context);
    }

    @Override
    public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
        glDisable(GL_DITHER);

        glClearColor(0f, 0f, 0f, 0.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        programHandle = Shaders.loadShaders(Shaders.VERTEX_SHADER, Shaders.FRAGMENT_SHADER);

        int mvpMatrixHandle = glGetUniformLocation(programHandle, "u_MVPMatrix");
        int positionHandle = glGetAttribLocation(programHandle, "a_Position");
        int colorHandle = glGetAttribLocation(programHandle, "a_Color");
        int textureCoordinateHandle = glGetAttribLocation(programHandle, "a_TexCoordinate");
        int textureHandle = glGetUniformLocation(programHandle, "u_Texture");

        scene.initShaders(positionHandle, colorHandle, mvpMatrixHandle, textureCoordinateHandle, textureHandle);

        initScene();
    }

    protected void setProgramHandle(int programHandle) {
        this.programHandle = programHandle;
    }

    public int getProgramHandle() {
        return programHandle;
    }

    protected abstract void initScene();

    @Override
    public void onSurfaceChanged(GL10 gl10, int width, int height) {
        glViewport(0, 0, width, height);

        if (initializeObjectPicker) {
            ObjectPicker.getInstance().initialize(height);
        }

        scene.onSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl10) {
        SceneCamera camera = scene.getCamera();
        Mat4 viewMatrix = camera.getViewMatrix();
        Mat4 projectionMatrix = camera.getProjectionMatrix();

        if (tryPickObject) {
            final SceneObject object = ObjectPicker.getInstance().tryPickObjectAtPosition(
                    clickPosition,
                    viewMatrix,
                    projectionMatrix
            );

            if (object != null) {
                onObjectPicked(object);
            }

            tryPickObject = false;
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        }

        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glUseProgram(programHandle);

        update();
        scene.draw(viewMatrix, projectionMatrix);
    }

    protected abstract void onObjectPicked(SceneObject object);

    protected abstract void update();

    public SceneCamera getActiveCamera() {
        return scene.getCamera();
    }

    public Scene getScene() {
        return scene;
    }

    public void onTouch(final float x, final float y) {
        tryPickObject = true;
        clickPosition = new Vec3(x, y, 0);
    }

    protected int loadTexture(final int texture, final String name) {
        return textureManager.loadTexture(texture, name);
    }

    protected TextureManager getTextureManger() {
        return textureManager;
    }

    public interface OnObjectPickedListener {

        void onObjectPicked(SceneObject pickedObject);
    }
}
