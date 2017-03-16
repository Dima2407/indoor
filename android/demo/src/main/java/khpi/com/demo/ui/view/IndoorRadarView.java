package khpi.com.demo.ui.view;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.graphics.PointF;
import android.graphics.PorterDuff;
import android.graphics.PorterDuffXfermode;
import android.support.annotation.NonNull;
import android.util.AttributeSet;
import android.view.MotionEvent;

import khpi.com.demo.routing.IndoorMapView;

public class IndoorRadarView  extends IndoorMapView {


    public IndoorRadarView(Context context, AttributeSet attr) {
        super(context, attr);
    }

    public IndoorRadarView(Context context) {
        super(context);
    }

    @Override
    public void setCoordinates(double trilatX, double trilatY, double bx, double by) {
        super.setCoordinates(trilatX, trilatY, bx, by);
        setZoomEnabled(false);
        setScaleAndCenter(0.5f,new PointF((float)bx/pixelSize,(float)by/pixelSize));
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);

        Path path = new Path();
        path.addCircle(getWidth()/2, getWidth()/2, getWidth()/2, Path.Direction.CW);
        path.setFillType(Path.FillType.EVEN_ODD);


        Paint eraser = new Paint();
        eraser.setXfermode(new PorterDuffXfermode(PorterDuff.Mode.DST_IN));
        eraser.setColor(Color.WHITE);

        canvas.drawPath(path,eraser);
    }

    @Override
    public boolean onTouchEvent(@NonNull MotionEvent event) {
        return super.onTouchEvent(event);
    }
}
