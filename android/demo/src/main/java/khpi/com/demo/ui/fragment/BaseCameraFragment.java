package khpi.com.demo.ui.fragment;

import android.hardware.Camera;
import android.widget.Toast;

abstract class BaseCameraFragment extends GenericFragment {

    private Camera camera;

    protected void initCamera() {
        camera = getCameraInstance();

        if (camera == null) {
            return;
        }

        Camera.Parameters parameters = camera.getParameters();
        parameters.setFocusMode(Camera.Parameters.FOCUS_MODE_CONTINUOUS_VIDEO);
        camera.setParameters(parameters);
    }

    private Camera getCameraInstance() {
        if (camera != null) {
            return camera;
        }
        Camera c = null;
        try {
            c = Camera.open();
        } catch (Exception e) {
            Toast.makeText(getContext(), "Camera is not available.", Toast.LENGTH_SHORT).show();
        }
        return c;
    }

    @Override
    public void onStop() {
        super.onStop();

        if (camera == null) {
            return;
        }

        camera.stopPreview();
        camera.release();
        camera = null;
    }

    protected Camera getCamera() {
        return camera;
    }
}
