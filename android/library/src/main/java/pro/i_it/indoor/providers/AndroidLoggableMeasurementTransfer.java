package pro.i_it.indoor.providers;

import android.util.Log;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import pro.i_it.indoor.DebugConfig;
import pro.i_it.indoor.events.MeasurementEvent;
import pro.i_it.indoor.events.MeasurementType;

public class AndroidLoggableMeasurementTransfer implements MeasurementTransfer {

    private final MeasurementTransfer transfer;

    public AndroidLoggableMeasurementTransfer(MeasurementTransfer transfer) {
        this.transfer = transfer;
    }

    @Override
    public void deliver(MeasurementEvent event) {
        if (event.getType() == MeasurementType.SENSOR_VALUE) {
            try {

                saveToFile("/storage/emulated/0/Download/accelerometer.json", convertAccel(event));
                saveToFile("/storage/emulated/0/Download/angles.json", convertAngles(event));
            } catch (JSONException e) {
                Log.e(AndroidLoggableMeasurementTransfer.class.getSimpleName(), "deliver: ", e);
            }
        }
        transfer.deliver(event);
    }

    private JSONObject convertAngles(MeasurementEvent event) throws JSONException {
        return new JSONObject()
                .put("timestamp", event.getTimestamp())
                .put("azimuth", event.getData()[3])
                .put("pitch", event.getData()[4])
                .put("roll", event.getData()[5]);
    }

    private JSONObject convertAccel(MeasurementEvent event) throws JSONException {
        return new JSONObject()
                .put("timestamp", event.getTimestamp())
                .put("x", event.getData()[0])
                .put("y", event.getData()[1])
                .put("z", event.getData()[2]);
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
