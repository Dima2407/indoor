package com.kit.indornavigation.utils;

import android.graphics.PointF;

import com.kit.indornavigation.ui.view.IndoorMapRedactor;


public final class GeometryUtils {

    public static double getPixelSizeInMeters(PointF point1, PointF point2, double distance) {
        return distance / distanceBetweenPoints(point1, point2);
    }

    public static boolean isCoordinatesInvalid(IndoorMapRedactor view, PointF point) {
        if (point == null || view == null) {
            return false;
        }

        PointF sPoint = view.viewToSourceCoord(point);

        float sX = sPoint.x;
        float sY = sPoint.y;

        return sX < 0 || sX > view.getSWidth() || sY < 0 || sY > view.getSHeight();
    }

    public static float calcAngle(PointF p1, PointF p2, float compensationAngle) {
        float angle = (float) Math.toDegrees(Math.atan2(p2.y - p1.y, p2.x - p1.x)) + compensationAngle;

        if (angle < 0) {
            angle += 360;
        }

        return angle;
    }

    public static double calcDistance(PointF p1, PointF p2, double pixelSize) {
        return distanceBetweenPoints(p1, p2) * pixelSize;
    }

    private static double distanceBetweenPoints(PointF p1, PointF p2) {
        double xPow = Math.pow(p1.x - p2.x, 2);
        double yPow = Math.pow(p1.y - p2.y, 2);
        return Math.sqrt(xPow + yPow);
    }
}