package pro.i_it.indoor.logger;

import android.util.Log;

import org.json.JSONObject;

import pro.i_it.indoor.OnLocationUpdateListener;

public class LoggableLocationUpdateListener extends FileLogger implements OnLocationUpdateListener {

    private static final String POSITIONS_JSON = "positions.json";
    private OnLocationUpdateListener listener;

    public LoggableLocationUpdateListener(OnLocationUpdateListener listener) {
        this.listener = listener;
        delete(POSITIONS_JSON);
    }

    @Override
    public void onLocationChanged(float[] position) {
        try {
            JSONObject object = new JSONObject();
            object.put("x", position[0]);
            object.put("y", position[1]);
            appendToFile(POSITIONS_JSON, object);
        } catch (Exception e) {
            Log.w(LoggableLocationUpdateListener.class.getSimpleName(), "onLocationChanged: ", e);
        }
        listener.onLocationChanged(position);
    }

}
