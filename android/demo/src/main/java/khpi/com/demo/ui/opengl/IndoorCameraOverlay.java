package khpi.com.demo.ui.opengl;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.GestureDetector;
import android.view.MotionEvent;

import khpi.com.demo.model.Floor;
import khpi.com.demo.model.Inpoint;
import khpi.com.demo.model.Point;
import pro.i_it.indoor.routing.Route;

import java.util.ArrayList;
import java.util.List;

public final class IndoorCameraOverlay extends GLSurfaceView {

    private IndoorRenderer renderer;
    private GestureDetector gestureDetector;

    public IndoorCameraOverlay(final Context context, AttributeSet attrs) {
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

        renderer = new IndoorRenderer(getContext());
        setRenderer(renderer);
        setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);

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

    public void setOnObjectPickedListener(BaseRender.OnObjectPickedListener listener) {
        renderer.setOnObjectPickedListener(listener);
    }

    public void onCurrentPositionChanged(final double x, final double y) {
        renderer.onCurrentPositionChanged(x, y);
        queueEvent(new Runnable() {
            @Override
            public void run() {
                requestRender();
            }
        });
    }

    public void onOrientationChanged(final float azimuth, final float pitch, final float roll) {
        renderer.onDeviceOrientationChanged(azimuth, pitch, roll);
        queueEvent(new Runnable() {
            @Override
            public void run() {
                requestRender();
            }
        });
    }

    public void updateInpoints(final List<Inpoint> inpoints, final Floor floor) {
        List<Point> points = new ArrayList<>(inpoints.size());

        for (Inpoint inpoint : inpoints) {
            Point point = new Point();
            point.setMercatorX(inpoint.getX() * floor.getPixelSize());
            point.setMercatorY(inpoint.getY() * floor.getPixelSize());
            point.setTitle(inpoint.getTitle());
            point.setDescription(inpoint.getDescription());

            points.add(point);
        }

        renderer.setPoiData(points);
        queueEvent(new Runnable() {
            @Override
            public void run() {
                requestRender();
            }
        });
    }

    public void setPoiData(List<Point> data) {
        renderer.setPoiData(data);
        queueEvent(new Runnable() {
            @Override
            public void run() {
                requestRender();
            }
        });
    }

    public void onNewRoute(Route r) {
        renderer.onNewRoute(r);
        queueEvent(new Runnable() {
            @Override
            public void run() {
                requestRender();
            }
        });
    }
}
