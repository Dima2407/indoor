package com.kit.indornavigation.ui.detectors;

import android.graphics.PointF;
import android.view.GestureDetector;
import android.view.MotionEvent;

import com.github.alwayswannasleep.models.BeaconModel;
import com.kit.indornavigation.ui.view.IndoorMapRedactor;
import com.kit.indornavigation.utils.GeometryUtils;


public final class MoveBeaconDetector extends GestureDetector {
    public MoveBeaconDetector(final IndoorMapRedactor redactor) {
        super(redactor.getContext(), new SimpleOnGestureListener() {

            private BeaconModel selectedBeaconModel;

            @Override
            public boolean onDown(MotionEvent e) {
                selectedBeaconModel = redactor.getBeaconWithPoint(new PointF(e.getX(), e.getY()));

                return selectedBeaconModel != null;
            }

            @Override
            public boolean onScroll(MotionEvent e1, MotionEvent e2, float distanceX, float distanceY) {
                if (selectedBeaconModel == null) {
                    return false;
                }

                if (GeometryUtils.isCoordinatesInvalid(redactor, new PointF(e2.getX(), e2.getY()))) {
                    return false;
                }

                selectedBeaconModel.setPosition(redactor.viewToSourceCoord(e2.getX(), e2.getY()));
                redactor.invalidate();

                return true;
            }
        });
    }
}
