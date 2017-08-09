package pro.i_it.indoor;

import android.graphics.PointF;

public interface OnLocationUpdateListener {
    void onLocationChanged(PointF position, float [] route);
}
