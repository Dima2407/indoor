package pro.i_it.indoor.logger;

import android.util.Log;

import org.json.JSONException;
import org.json.JSONObject;

import pro.i_it.indoor.events.MeasurementEvent;
import pro.i_it.indoor.events.MeasurementType;
import pro.i_it.indoor.providers.MeasurementTransfer;

public class AndroidLoggableMeasurementTransfer extends FileLogger implements MeasurementTransfer {


    private static final String ACCELEROMETER_JSON = "accelerometer.json";
    private static final String ANGLES_JSON = "angles.json";
    private final MeasurementTransfer transfer;

    public AndroidLoggableMeasurementTransfer(MeasurementTransfer transfer) {
        this.transfer = transfer;
        delete(ACCELEROMETER_JSON);
        delete(ANGLES_JSON);
    }

    @Override
    public void deliver(MeasurementEvent event) {
        if (event.getType() == MeasurementType.SENSOR_VALUE) {
            try {
                appendToFile(ACCELEROMETER_JSON, convertAccel(event));
                appendToFile(ANGLES_JSON, convertAngles(event));
            } catch (Exception e) {
                Log.w(AndroidLoggableMeasurementTransfer.class.getSimpleName(), "deliver: ", e);
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
}
