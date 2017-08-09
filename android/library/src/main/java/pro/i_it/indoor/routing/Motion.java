package pro.i_it.indoor.routing;

import android.graphics.PointF;

import static java.lang.Math.PI;
import static java.lang.Math.atan2;
import static java.lang.Math.pow;
import static java.lang.Math.sqrt;

public class Motion {
    PointF start;
    PointF end;
    public final int angleDirection;
    public final float distance;

    public Motion(PointF p1, PointF p2, PointF p3) {


        pow((p2.x - p1.x), 2);
        distance = (float) sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));

        start = p1;
        end = p2;


        //if angle<0 -> right, if angle>0 left
        angleDirection = (int) (getAngle(p1, p2) - getAngle(p2, p3));

    }


    private float getAngle(PointF a, PointF b) {
        float deltaX = b.x - a.x;
        float deltaY = b.y - a.y;
        float angleInDegrees = (float) (atan2(deltaY, deltaX) * 180 / PI);
        return angleInDegrees;
    }


    @Override
    public String toString() {
        return "distance:" + distance + ">> angle:" + (angleDirection < 0 ? "right" : "left");
    }
}
