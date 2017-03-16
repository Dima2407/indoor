package khpi.com.demo.ui.opengl;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.GestureDetector;
import android.view.MotionEvent;

import khpi.com.demo.model.Point;
import khpi.com.demo.model.Route;
import khpi.com.demo.utils.GeoUtils;

import java.util.List;

public final class CameraMapOverlay extends GLSurfaceView {

    private OutdoorRenderer renderer;
    private GestureDetector gestureDetector;

    public CameraMapOverlay(Context context, AttributeSet attrs) {
        super(context, attrs);

        if (isInEditMode()) {
            return;
        }

        init();
    }

    private void init() {
        setClickable(true);

        setZOrderMediaOverlay(true);
        setEGLConfigChooser(8, 8, 8, 8, 16, 0);
        getHolder().setFormat(PixelFormat.TRANSLUCENT);
        setEGLContextClientVersion(2);

        renderer = new OutdoorRenderer(getContext());
        setRenderer(renderer);
        setRenderMode(RENDERMODE_WHEN_DIRTY);

        gestureDetector = new GestureDetector(getContext(), new GestureDetector.SimpleOnGestureListener() {
            @Override
            public boolean onSingleTapConfirmed(final MotionEvent e) {
                renderer.onTouch(e.getX(), e.getY());

                return super.onSingleTapConfirmed(e);
            }
        });
    }

    @Override
    public boolean onTouchEvent(final MotionEvent event) {
        gestureDetector.onTouchEvent(event);

        return super.onTouchEvent(event);
    }

    public void onCurrentPositionChanged(double longitude, double latitude) {
        renderer.onCurrentPositionChanged(GeoUtils.convertLongitudeToMercatorX(longitude), GeoUtils.convertLatitudeToMercatorY(latitude));
        queueEvent(new Runnable() {
            @Override
            public void run() {
                requestRender();
            }
        });
    }

    public void setPoiData(final List<Point> data) {
        renderer.setPoiData(data);
        queueEvent(new Runnable() {
            @Override
            public void run() {
                requestRender();
            }
        });
    }

    public void setOnObjectPickedListener(BaseRender.OnObjectPickedListener listener) {
        renderer.setOnObjectPickedListener(listener);
    }

    public void onDeviceRotated(float azimuth, float pitch, float roll) {
        renderer.onDeviceOrientationChanged(azimuth, pitch, roll);
        queueEvent(new Runnable() {
            @Override
            public void run() {
                requestRender();
            }
        });
    }

    public void onNewRoute(final Route route) {
        renderer.onNewRoute(route);
        queueEvent(new Runnable() {
            @Override
            public void run() {
                requestRender();
            }
        });
    }
}
