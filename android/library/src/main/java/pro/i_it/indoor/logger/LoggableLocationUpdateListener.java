package pro.i_it.indoor.logger;

import android.graphics.PointF;
import android.util.Log;

import org.json.JSONObject;

import java.text.SimpleDateFormat;
import java.util.Date;

import pro.i_it.indoor.OnLocationUpdateListener;

public class LoggableLocationUpdateListener extends FileLogger implements OnLocationUpdateListener {

    private static final String POSITIONS_CSV = "positions-%s.txt";
    private final SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd hh-mm-ss");
    private final String fileName = getFileName();

    private OnLocationUpdateListener listener;

    public LoggableLocationUpdateListener(OnLocationUpdateListener listener) {
        this.listener = listener;
        delete(fileName);
    }

    @Override
    public void onLocationChanged(PointF position, float[] route) {
        try {
            String measurementStr = String.format("%d %f %f", System.currentTimeMillis(), position.x, position.y);
            appendToFile(fileName, measurementStr);
        } catch (Exception e) {
            Log.w(LoggableLocationUpdateListener.class.getSimpleName(), "onLocationChanged: ", e);
        }
        listener.onLocationChanged(position, route);
    }

    private String getFileName() {
        String dateStr = dateFormat.format(new Date());
        String fileName = String.format(POSITIONS_CSV, dateStr);
        return fileName;
    }

}
