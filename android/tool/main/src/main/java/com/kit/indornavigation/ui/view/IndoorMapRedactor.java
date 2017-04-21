package com.kit.indornavigation.ui.view;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PointF;
import android.graphics.PorterDuff;
import android.graphics.PorterDuffColorFilter;
import android.graphics.Rect;
import android.support.annotation.NonNull;
import android.util.AttributeSet;
import android.view.GestureDetector;
import android.view.MotionEvent;

import com.davemorrissey.labs.subscaleview.SubsamplingScaleImageView;
import com.github.alwayswannasleep.models.BeaconModel;
import com.kit.indornavigation.R;
import com.kit.indornavigation.model.CalibrationResult;

import java.util.ArrayList;
import java.util.List;

public final class IndoorMapRedactor extends SubsamplingScaleImageView {

    private static final float DEFAULT_TAP_POINT_POSITION = -1;

    private Bitmap beaconBitmap;
    private Rect beaconRect;

    private List<BeaconModel> beaconModels;
    private List<PointF> distancePoints;
    private List<GestureDetector> gestureDetectors;

    private float tapPointY;
    private float tapPointX;
    private CurrentPositionDetector positionDetector;
    private Bitmap currentPointBitmap;
    private Rect currentPointRect;
    private Paint calibratedFilter;
    private Paint unCalibratedFilter;
    private Paint lastCalibratedFilter;

    private List<CalibrationResult> calibrationResults;
    private List<CalibrationResult> lastSessionCalibrationResults;

    public IndoorMapRedactor(Context context, AttributeSet attr) {
        super(context, attr);

        init(context);
        initPaints();
    }

    public IndoorMapRedactor(Context context) {
        super(context);

        init(context);
        initPaints();
    }

    private void init(Context context) {
        calibrationResults = new ArrayList<>();
        lastSessionCalibrationResults = new ArrayList<>();
        distancePoints = new ArrayList<>(2);
        beaconModels = new ArrayList<>();
        gestureDetectors = new ArrayList<>();

        beaconBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.beacon_ic);
        beaconRect = new Rect();

        currentPointBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.ic_adjust_black_24dp);
        currentPointRect = new Rect();

        tapPointX = DEFAULT_TAP_POINT_POSITION;
        tapPointY = DEFAULT_TAP_POINT_POSITION;
    }

    private void initPaints() {
        unCalibratedFilter = new Paint(Paint.FILTER_BITMAP_FLAG);
        unCalibratedFilter.setColorFilter(new PorterDuffColorFilter(Color.RED, PorterDuff.Mode.MULTIPLY));

        calibratedFilter = new Paint(Paint.FILTER_BITMAP_FLAG);
        calibratedFilter.setColorFilter(new PorterDuffColorFilter(Color.GREEN, PorterDuff.Mode.MULTIPLY));

        lastCalibratedFilter = new Paint(Paint.FILTER_BITMAP_FLAG);
        lastCalibratedFilter.setColorFilter(new PorterDuffColorFilter(Color.BLUE,
                                                                      PorterDuff.Mode.MULTIPLY));
    }

    @Override
    public boolean onTouchEvent(@NonNull MotionEvent event) {
        boolean consumed = false;

        for (GestureDetector gestureDetector : gestureDetectors) {
            if (gestureDetector.onTouchEvent(event)) {
                consumed = true;
            }
        }

        return consumed || super.onTouchEvent(event);
    }

    public void addGestureDetector(GestureDetector gestureDetector) {
        if (gestureDetector == null) {
            return;
        }

        gestureDetectors.add(gestureDetector);
    }

    public void removeGestureDetector(GestureDetector gestureDetector) {
        if (gestureDetector == null) {
            return;
        }

        gestureDetectors.remove(gestureDetector);
    }

    public void addBeacon(BeaconModel beaconModel) {
        beaconModels.add(beaconModel);
        invalidate();
    }

    public void removeBeacon(BeaconModel beaconModel) {
        beaconModels.remove(beaconModel);
        invalidate();
    }

    public List<BeaconModel> getBeaconModels() {
        return beaconModels;
    }

    public void addDistancePoint(PointF point) {
        distancePoints.add(point);
        invalidate();
    }

    public void setBeaconModels(List<BeaconModel> beaconModels, double pixelSize) {
        for (BeaconModel beaconModel : beaconModels) {
            beaconModel.setPosition(new PointF(((float) (beaconModel.getPosition().x / pixelSize)), (float) (beaconModel.getPosition().y / pixelSize)));
        }

        this.beaconModels = beaconModels;
    }

    public void setDistancePoints(List<PointF> distancePoints) {
        this.distancePoints = distancePoints;
    }

    public void clearDistancePoints() {
        distancePoints.clear();
        invalidate();
    }

    public List<PointF> getDistancePoints() {
        return distancePoints;
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);

        if (!isReady()) {
            return;
        }

        for (BeaconModel beaconModel : beaconModels) {
            int width = (int) (beaconBitmap.getWidth() / 2 * getScale());
            int height = (int) (beaconBitmap.getHeight() / 2 * getScale());

            PointF p = sourceToViewCoord(beaconModel.getPosition());
            beaconRect.set((int) p.x - width, (int) p.y - height, (int) p.x + width, (int) p.y + height);

            canvas.drawBitmap(beaconBitmap,
                              null,
                              beaconRect,
                              CalibrationResult.listContainsBeacon(lastSessionCalibrationResults,
                                                                   beaconModel) ? lastCalibratedFilter : isCalibrated(
                                      beaconModel) ? calibratedFilter : unCalibratedFilter);
        }

        if (tapPointX != DEFAULT_TAP_POINT_POSITION) {
            int width = (int) (currentPointBitmap.getWidth() / 2 * getScale());
            int height = (int) (currentPointBitmap.getHeight() / 2 * getScale());

            PointF p = sourceToViewCoord(tapPointX, tapPointY);

            currentPointRect.set((int) p.x - width, (int) p.y - height, (int) p.x + width, (int) p.y + height);
            canvas.drawBitmap(currentPointBitmap, null, currentPointRect, null);
        }
    }

    public BeaconModel getBeaconWithPoint(PointF point) {
        int width = (int) (beaconBitmap.getWidth() / 2 * getScale());
        int height = (int) (beaconBitmap.getHeight() / 2 * getScale());

        for (BeaconModel beaconModel : beaconModels) {
            PointF position = sourceToViewCoord(beaconModel.getPosition());

            float startX = position.x - width;
            float startY = position.y - height;
            float endX = position.x + width;
            float endY = position.y + height;

            if (point.x >= startX && point.x <= endX && point.y >= startY && point.y <= endY) {
                return beaconModel;
            }
        }

        return null;
    }

    public void updateBeacon(BeaconModel beaconModel, BeaconModel beaconModelWithPoint) {
        beaconModels.remove(beaconModelWithPoint);
        beaconModel.setPosition(beaconModelWithPoint.getPosition());
        beaconModels.add(beaconModel);
        invalidate();
    }

    public void tryRemoveBeacon(PointF gesturePoint) {
        BeaconModel beaconModelWithPoint = getBeaconWithPoint(gesturePoint);

        if (beaconModelWithPoint == null) {
            return;
        }

        beaconModels.remove(beaconModelWithPoint);
        invalidate();
    }

    public PointF getTapPoint() {
        return new PointF(tapPointX, tapPointY);
    }

    public void setCurrentPositionDetector() {
        if (positionDetector == null) {
            positionDetector = new CurrentPositionDetector();
        }

        addGestureDetector(positionDetector);
    }

    public void removeCurrentPositionDetector() {
        removeGestureDetector(positionDetector);
    }

    public void removeTapPoint() {
        tapPointY = tapPointX = DEFAULT_TAP_POINT_POSITION;

        invalidate();
    }

    public void setCalibrationData(final List<CalibrationResult> calibrationResults) {
        this.calibrationResults.clear();

        if (calibrationResults != null) {
            this.calibrationResults.addAll(calibrationResults);
        }

        invalidate();
    }

    private boolean isCalibrated(BeaconModel beacon) {
        return CalibrationResult.listContainsBeacon(calibrationResults, beacon);
    }

    public List<BeaconModel> getBeaconModelsForSaving(double pixelSize) {
        List<BeaconModel> result = new ArrayList<>();

        for (BeaconModel model : beaconModels) {
            BeaconModel clone = model.clone();

            clone.setPosition(new PointF((float) (clone.getPosition().x * pixelSize), (float) (clone.getPosition().y * pixelSize)));
            result.add(clone);

            if (calibrationResults.isEmpty()) {
                clone.setDefaultCalibrationData();
            }
        }

        return result;
    }

    public void setLastSessionCalibrationResults(final List<CalibrationResult> lastSessionCalibrationResults) {
        this.lastSessionCalibrationResults.addAll(lastSessionCalibrationResults);
    }

    public void clearLastSessionCalibrationResults() {
        this.lastSessionCalibrationResults.clear();
    }

    public boolean hasTapPoint() {
        return tapPointX != DEFAULT_TAP_POINT_POSITION && tapPointY != DEFAULT_TAP_POINT_POSITION;
    }

    private final class CurrentPositionDetector extends GestureDetector {

        CurrentPositionDetector() {
            super(getContext(), new SimpleOnGestureListener() {
                @Override
                public boolean onSingleTapConfirmed(MotionEvent e) {
                    float x = e.getX();
                    float y = e.getY();

                    PointF pointF = viewToSourceCoord(x, y);
                    if (pointF.x < 0 || pointF.x > getSWidth() || pointF.y < 0 || pointF.y > getSHeight()) {
                        return false;
                    }

                    tapPointX = pointF.x;
                    tapPointY = pointF.y;
                    invalidate();

                    return true;
                }
            });
        }
    }
}
