package com.kit.indornavigation.ui.detectors;

import android.content.DialogInterface;
import android.graphics.PointF;
import android.support.v7.app.AlertDialog;
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
                AlertDialog.Builder builder = new AlertDialog.Builder(view.getContext())
                        .setTitle("The beacon is ready to be removed")
                        .setPositiveButton("OK", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int which) {
                                view.tryRemoveBeacon(gesturePoint);
                            }
                        })
                        .setNegativeButton("Cancel", null);
                builder.show();
                return super.onSingleTapConfirmed(e);
            }
        });
    }
}
