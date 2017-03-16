package khpi.com.demo.ui.opengl;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

import khpi.com.demo.model.Step;

public final class DirectionMapOverlay extends GLSurfaceView {

    private final DirectionRenderer renderer;

    public DirectionMapOverlay(Context context, AttributeSet attrs) {
        super(context, attrs);

        setZOrderMediaOverlay(true);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        getHolder().setFormat(PixelFormat.TRANSLUCENT);
        setEGLContextClientVersion(2);

        renderer = new DirectionRenderer(context);
        setRenderer(renderer);
    }

    public void onDeviceRotated(float azimuth, float pitch, float roll) {
        renderer.onDeviceRotated(azimuth, pitch, roll);
    }

    public void onCurrentPositionChanged(double longitude, double latitude) {
        renderer.onCurrentPositionChanged(longitude, latitude);
    }

    public void setRouteFirst(Step step) {
        renderer.setRouteStep(step);
    }
}
