package com.kit.indornavigation.ui.detectors;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.graphics.PointF;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.widget.ArrayAdapter;

import com.github.alwayswannasleep.models.BeaconModel;
import com.kit.indornavigation.R;
import com.kit.indornavigation.core.App;
import com.kit.indornavigation.ui.view.IndoorMapRedactor;
import com.kit.indornavigation.utils.GeometryUtils;

import java.util.ArrayList;
import java.util.List;

public final class AddBeaconDetector extends GestureDetector {

    public AddBeaconDetector(final IndoorMapRedactor view) {
        super(view.getContext(), new SimpleOnGestureListener() {

            private boolean isEditMode;

            @SuppressWarnings("ConstantConditions")
            @Override
            public boolean onSingleTapConfirmed(final MotionEvent e) {
                final PointF gesturePoint = new PointF(e.getX(), e.getY());
                if (GeometryUtils.isCoordinatesInvalid(view, gesturePoint)) {
                    return false;
                }

                final BeaconModel beaconWithPoint = view.getBeaconWithPoint(gesturePoint);
                isEditMode = beaconWithPoint != null;

                AlertDialog.Builder dialog = new AlertDialog.Builder(view.getContext())
                        .setTitle(isEditMode ? "Edit beacon with " + String.format("major: 0x%X; minor: 0x%X", beaconWithPoint.getMajor(), beaconWithPoint.getMinor()) :
                                "Choose beacon model: ");

                final App application = (App) view.getContext().getApplicationContext();
                final List<BeaconModel> beacons = application.getBeaconSearcher().getBeacons();
                beacons.removeAll(view.getBeaconModels());
                if (!beacons.isEmpty()) {
                    final List<String> strings = new ArrayList<>();

                    for (BeaconModel beacon : beacons) {
                        strings.add(String.format("major: 0x%X; minor: 0x%X", beacon.getMajor(), beacon.getMinor()));
                    }

                    final ArrayAdapter<String> adapter = new ArrayAdapter<>(
                            view.getContext(),
                            R.layout.item_simple_beacon,
                            strings);

                    dialog.setAdapter(adapter, new DialogInterface.OnClickListener() {
                        @Override
                        public void onClick(DialogInterface dialogInterface, int i) {
                            final BeaconModel beacon = new BeaconModel(beacons.get(i));

                            beacon.setPosition(view.viewToSourceCoord(gesturePoint));

                            if (isEditMode) {
                                view.updateBeacon(beacon, beaconWithPoint);
                            } else {
                                view.addBeacon(beacon);
                            }
                        }
                    });
                } else {
                    dialog.setMessage("No beacons near");
                    dialog.setNegativeButton("Cancel", null);
                }

                dialog.show();
                return false;
            }
        });
    }
}
