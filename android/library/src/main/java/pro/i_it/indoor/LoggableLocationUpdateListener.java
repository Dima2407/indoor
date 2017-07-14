package pro.i_it.indoor;

import android.util.Log;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import pro.i_it.indoor.providers.AndroidLoggableMeasurementTransfer;

public class LoggableLocationUpdateListener implements OnLocationUpdateListener {

    private OnLocationUpdateListener listener;

    public LoggableLocationUpdateListener(OnLocationUpdateListener listener) {
        this.listener = listener;
    }

    @Override
    public void onLocationChanged(float[] position) {
        try {
            JSONObject object = new JSONObject();
            object.put("x", position[0]);
            object.put("y", position[1]);
            saveToFile("/storage/emulated/0/Download/positions.json", object);
        } catch (Exception e) {
            Log.w(LoggableLocationUpdateListener.class.getSimpleName(), "onLocationChanged: ", e);
        }
        listener.onLocationChanged(position);
    }

    private void saveToFile(String path, JSONObject data) {
        File f = new File(path);
        boolean firstRecord = !f.exists();

        try (FileWriter fw = new FileWriter(f.getAbsoluteFile(), true);
             BufferedWriter bw = new BufferedWriter(fw)) {
            if (firstRecord) {
                bw.write(data.toString());
            } else {
                bw.write(",");
                bw.write(data.toString());
            }
            bw.flush();
        } catch (IOException e) {
            Log.e(AndroidLoggableMeasurementTransfer.class.getSimpleName(), "saveToFile: ", e);
        }
    }

}
