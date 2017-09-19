package khpi.com.demo.routing;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PointF;
import android.graphics.Rect;
import android.os.Handler;
import android.support.annotation.NonNull;
import android.util.AttributeSet;
import android.util.Log;
import android.util.TypedValue;
import android.view.GestureDetector;
import android.view.MotionEvent;

import com.davemorrissey.labs.subscaleview.ImageSource;
import com.davemorrissey.labs.subscaleview.SubsamplingScaleImageView;
import khpi.com.demo.R;
import khpi.com.demo.model.BeaconModel;
import khpi.com.demo.model.Inpoint;
import khpi.com.demo.routing.core.Edge;

import java.util.ArrayList;
import java.util.List;

public class IndoorMapView extends SubsamplingScaleImageView {

    private static final int TAP_SIZE = 15;
    private float DOT_RADIUS = 10f;
    private float BITMAP_SIZE = 10f;
    //bitmaps
    private Bitmap beaconBitmap;
    private Bitmap destPointBitmap;
    private Bitmap inpointBitmap;


    //Rects
    private Rect beaconRect;
    private Rect destPointRect;
    private Rect inpointPointRect;

    //Paints
    private Paint kalmanPaints;
    private Paint trilatPaint;
    private Paint inpointPaint;


    //Data
    private List<Inpoint> inpoints;
    private float[] calculatedRoute = new float[0];
    private short[][] calculatedMapNodes;
    private int nodeSize;
    private PointF destPoint;
    private PointF coordinates;
    protected float pixelSize;


    private List<Edge> edges;

    private GestureDetector gestureDetector = new GestureDetector(getContext(), new onPressGestureListener());

    //Listeners
    private DestinationListener destinationListener;
    private InpointClickListener inpointClickListener;
    private List<BeaconModel> beacons;
    private Bitmap positionBitmap;
    private Rect positionBitmapRect;
    private boolean isInitializationCompleted;


    public IndoorMapView(Context context, AttributeSet attr) {
        super(context, attr);
        init(context);
        initPaints();
    }

    public IndoorMapView(Context context) {
        super(context);
        init(context);
        initPaints();
        setMaxScale(1000);
    }

    private void init(Context context) {

        beaconBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.circle);
        beaconBitmap = Bitmap.createScaledBitmap(beaconBitmap, (int) dp2px(BITMAP_SIZE), (int) dp2px(BITMAP_SIZE), true);
        beaconRect = new Rect();

        destPointBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.ic_directions_white_24dp);
        destPointRect = new Rect();

        inpointBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.map_point_icn);
        inpointPointRect = new Rect();

        positionBitmap = BitmapFactory.decodeResource(context.getResources(), R.drawable.map_pin_icn);
        positionBitmapRect = new Rect();

        isInitializationCompleted = false;

        final Handler handler = new Handler();
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                postInvalidate();
                handler.postDelayed(this, 100);
            }
        }, 250);
    }

    public void setEdges(List<Edge> edges) {
        this.edges = edges;
    }

    private void initPaints() {
        kalmanPaints = new Paint(Paint.ANTI_ALIAS_FLAG);
        kalmanPaints.setColor(Color.BLUE);
        kalmanPaints.setStyle(Paint.Style.FILL_AND_STROKE);
        kalmanPaints.setStrokeWidth(dp2px(5));

        trilatPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
        trilatPaint.setColor(Color.BLUE);
        trilatPaint.setStyle(Paint.Style.FILL);


        inpointPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
        inpointPaint.setColor(Color.GREEN);
        inpointPaint.setAlpha(128);

    }

    public void initMapImage(String mapPath, double pixelSize) {
        this.pixelSize = (float) pixelSize;
        if (mapPath != null)
            setImage(ImageSource.uri(mapPath));
    }


    public void setInpoints(List<Inpoint> inpoints) {
        this.inpoints = inpoints;
    }

    public void setRoute(float[] route) {
        this.calculatedRoute = route;
    }

    public void setDestinationListener(DestinationListener destinationListener) {
        this.destinationListener = destinationListener;
    }

    public void setCalculatedMapNodes(short[][] vertexs, int threshold) {
        this.calculatedMapNodes = vertexs;
        this.nodeSize = threshold;
    }

    public DestinationListener getDestinationListener() {
        return destinationListener;
    }

    public void setInpointClickListener(InpointClickListener inpointClickListener) {
        this.inpointClickListener = inpointClickListener;
    }

    @Override
    public boolean onTouchEvent(@NonNull MotionEvent event) {
        if (gestureDetector != null) {
            gestureDetector.onTouchEvent(event);
        }
        return super.onTouchEvent(event);
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);

        if (!isReady()) {
            return;
        }
        Paint paint = new Paint();
        paint.setColor(Color.BLUE);
        paint.setAlpha(150);
        //Draw beacons
        if (beacons != null) {
            for (BeaconModel beacon : beacons) {
                int width = (int) (beaconBitmap.getWidth() / 2 * getScale());
                int height = (int) (beaconBitmap.getHeight() / 2 * getScale());

                PointF p = sourceToViewCoord(beacon.getPosition(pixelSize));
                beaconRect.set((int) p.x - width, (int) p.y - height, (int) p.x + width, (int) p.y + height);

                canvas.drawBitmap(beaconBitmap, null, beaconRect, null);
            }
        }

        // Draw route
        if (calculatedRoute != null && calculatedRoute.length >= 4) {
            PointF start = sourceToViewCoord(calculatedRoute[0], calculatedRoute[1]);
            for (int i = 2; i < calculatedRoute.length; i += 2) {
                float pointX = (calculatedRoute[i]);
                float pointY = (calculatedRoute[i + 1]);

                PointF end = sourceToViewCoord(pointX, pointY);

                canvas.drawLine(start.x, start.y, end.x, end.y, kalmanPaints);
                start = end;
            }
        }


        // draw coordinates
        if (coordinates != null && isInitializationCompleted) {
            PointF p = sourceToViewCoord(coordinates.x, coordinates.y);
            canvas.drawBitmap(positionBitmap, p.x - positionBitmap.getWidth()/2, p.y - positionBitmap.getHeight(), null);
        }


        if (destPoint != null) {
            PointF p = sourceToViewCoord(destPoint.x, destPoint.y);
            int destWidth = (int) (destPointBitmap.getWidth() * getScale());
            int destHeight = (int) (destPointBitmap.getHeight() * getScale());

            destPointRect.set(
                    (int) p.x - destWidth / 2,
                    (int) p.y - destHeight / 2,
                    (int) p.x + destHeight / 2,
                    (int) p.y + destHeight / 2
            );
        }

        if (inpoints != null) {
            for (Inpoint inpoint : inpoints) {
                Rect rect = new Rect();
                PointF p = sourceToViewCoord((float) inpoint.getX(), (float) inpoint.getY());
                rect.set(
                        (int) p.x - inpointBitmap.getWidth() / 2,
                        (int) p.y - inpointBitmap.getHeight() / 2,
                        (int) p.x + inpointBitmap.getWidth() / 2,
                        (int) p.y + inpointBitmap.getHeight() / 2);
                canvas.drawBitmap(inpointBitmap, null, rect, null);
            }
        }
    }

    public boolean isInitializationCompleted() {
        return isInitializationCompleted;
    }

    public void setInitializationCompleted(boolean initializationCompleted) {
        isInitializationCompleted = initializationCompleted;
    }

    public void setCoordinates(double trilatX, double trilatY, double bx, double by) {
        coordinates = createPoint(bx / pixelSize, by / pixelSize);
    }

    public PointF getCoordinates() {
        return coordinates;
    }

    public PointF getDestPoint() {
        return destPoint;
    }

    public void setDestinationPoint(int nearX, int nearY) {
        destPoint = new PointF(nearX, nearY);
        if (destinationListener != null) {
            destinationListener.onDestinationChanged(nearX, nearY);
        }
    }

    public void setBeacons(List<BeaconModel> beacons) {
        this.beacons = beacons;
    }

    public void setPoints() {

    }


    private class onPressGestureListener extends GestureDetector.SimpleOnGestureListener {

        @Override
        public boolean onSingleTapConfirmed(MotionEvent e) {
            float x = e.getX();
            float y = e.getY();

            PointF realPoint = viewToSourceCoord(x, y);
            if (realPoint.x < 0 || realPoint.x > getSWidth() || realPoint.y < 0 || realPoint.y > getSHeight()) {
                return false;
            }


            List<Inpoint> inpoints = checkNearInpoints(realPoint);
            if (!inpoints.isEmpty()) {
                Log.d("onPressGestureListener", inpoints.get(0).getTitle());
                if (inpointClickListener != null) {
                    inpointClickListener.onInpoictClicked(inpoints.get(0));
                }
                return true;
            }

            destPoint = realPoint;
            if (destinationListener != null) {
                destinationListener.onDestinationChanged(destPoint.x, destPoint.y);
            }

            return true;
        }

        private List<Inpoint> checkNearInpoints(PointF realPoint) {
            List<Inpoint> result = new ArrayList<>();
            if (inpoints == null) {
                return result;
            }
            for (Inpoint inpoint : inpoints) {
                if (GeometryUtils.calcDistance(realPoint, new PointF((float) inpoint.getX(), (float) inpoint.getY())) < dp2px(TAP_SIZE)) {
                    result.add(inpoint);
                }
            }
            return result;

        }
    }


    protected float dp2px(float dp) {
        return TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, dp, getResources().getDisplayMetrics());
    }


    public interface DestinationListener {
        void onDestinationChanged(float x, float y);
    }

    public interface InpointClickListener {
        void onInpoictClicked(Inpoint inpoint);
    }


    private PointF createPoint(double x, double y) {
        Log.d("applyNewCoordinate", "createPoint: " + x + " " + y);
        return new PointF((float) x, (float) y);
    }
}
