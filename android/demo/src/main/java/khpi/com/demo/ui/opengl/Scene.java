package khpi.com.demo.ui.opengl;

import com.hackoeur.jglm.Mat4;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@SuppressWarnings("WeakerAccess")
public class Scene {

    private SceneCamera camera;

    private Map<Class<? extends SceneObject>, List<SceneObject>> objects;

    private int positionHandle;
    private int colorHandle;
    private int mvpMatrixHandle;
    private int textureCoordinateHandle;
    private int textureHandle;

    Scene() {
        camera = new SceneCamera();

        objects = new HashMap<>();
    }

    public void onSurfaceChanged(int displayWidth, int displayHeight) {
        camera.initProjection(displayWidth, displayHeight);
    }

    public List<SceneObject> getObjects(Class<? extends SceneObject> objectClass) {
        return objects.get(objectClass);
    }

    public SceneCamera getCamera() {
        return camera;
    }

    public synchronized void addSceneObject(SceneObject object) {
        object.setShaderPointers(
                positionHandle,
                colorHandle,
                mvpMatrixHandle,
                textureCoordinateHandle,
                textureHandle
        );

        List<SceneObject> sceneObjects = objects.get(object.getClass());

        if (sceneObjects == null) {
            sceneObjects = new ArrayList<>();
            objects.put(object.getClass(), sceneObjects);
        }

        sceneObjects.add(object);
    }

    public synchronized void removeAllElementsByClass(Class<? extends SceneObject> elementClass) {
        objects.remove(elementClass);
    }

    public void draw(Mat4 viewMatrix, Mat4 projectionMatrix) {
        Collection<List<SceneObject>> values = objects.values();

        if (objects.containsKey(PoiTable.class)) {
            List<SceneObject> sceneObjects = objects.get(PoiTable.class);

            if (sceneObjects != null) {
                for (int i = 0; i < sceneObjects.size(); i++) {
                    sceneObjects.get(i).draw(viewMatrix, projectionMatrix);
                }
            }
        }

        if (objects.containsKey(RoadStep.class)) {
            List<SceneObject> sceneObjects = objects.get(RoadStep.class);

            if (sceneObjects != null) {
                for (int i = 0; i < sceneObjects.size(); i++) {
                    sceneObjects.get(i).draw(viewMatrix, projectionMatrix);
                }
            }
        }

        List<List<SceneObject>> objects = new ArrayList<>(values);
        int size = values.size();
        for (int i = 0; i < size; i++) {
            List<SceneObject> sceneObjects = objects.get(i);

            if (RoadStep.class.isAssignableFrom(sceneObjects.get(0).getClass())) {
                continue;
            }

            if (PoiTable.class.isAssignableFrom(sceneObjects.get(0).getClass())) {
                continue;
            }

            for (int j = 0; j < sceneObjects.size(); j++) {
                sceneObjects.get(j).draw(viewMatrix, projectionMatrix);
            }
        }
    }

    public void initShaders(
            int positionHandle,
            int colorHandle,
            int mvpMatrixHandle,
            int textureCoordinateHandle,
            int textureHandle
    ) {
        this.positionHandle = positionHandle;
        this.colorHandle = colorHandle;
        this.mvpMatrixHandle = mvpMatrixHandle;
        this.textureCoordinateHandle = textureCoordinateHandle;
        this.textureHandle = textureHandle;
    }

    public void addSceneObjects(final List<? extends SceneObject> roadElements, Class<? extends SceneObject> clazz) {
        if (!objects.containsKey(clazz)) {
            objects.put(clazz, (List<SceneObject>) roadElements);
            return;
        }

        objects.get(clazz).addAll(roadElements);
    }
}
