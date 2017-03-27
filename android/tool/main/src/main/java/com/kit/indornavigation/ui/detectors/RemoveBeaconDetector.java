package com.kit.indornavigation.ui.detectors;

import android.graphics.PointF;
import android.view.GestureDetector;
import android.view.MotionEvent;

import com.kit.indornavigation.ui.view.IndoorMapRedactor;
import com.kit.indornavigation.utils.GeometryUtils;


public final class RemoveBeaconDetector extends GestureDetector {

    public RemoveBeaconDetector(final IndoorMapRedactor view) {
        super(view.getContext(), new SimpleOnGestureListener() {

            @Override
            public void onLongPress(MotionEvent e) {
                onSingleTapConfirmed(e);
            }

            @Override
            public boolean onSingleTapConfirmed(MotionEvent e) {
                final PointF gesturePoint = new PointF(e.getX(), e.getY());
                if (GeometryUtils.isCoordinatesInvalid(view, gesturePoint)) {
                    return false;
                }

                view.tryRemoveBeacon(gesturePoint);

                return super.onSingleTapConfirmed(e);
            }
        });
    }
}
