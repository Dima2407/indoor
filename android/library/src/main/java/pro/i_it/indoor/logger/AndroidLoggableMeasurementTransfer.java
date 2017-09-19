package pro.i_it.indoor.logger;

import android.util.Log;

import org.json.JSONException;
import org.json.JSONObject;

import java.text.SimpleDateFormat;
import java.util.Date;

import pro.i_it.indoor.events.MeasurementEvent;
import pro.i_it.indoor.events.MeasurementType;

public class AndroidLoggableMeasurementTransfer extends FileLogger implements MeasurementTransferLogger {


    private static final String ACCELEROMETER_FILE = "%s/accelerometer.txt";
    private static final String ANGLES_FILE = "%s/angles.txt";
    private static final String BLE_FILE = "%s/ble.txt";
    private static final String POSITION_BLE_FILE = "%s/ble-position.txt";
    private static final String POSITION_SENSORS_FILE = "%s/sensors-position.txt";
    public static final String TAG = AndroidLoggableMeasurementTransfer.class.getSimpleName();

    private final SimpleDateFormat dateFormat = new SimpleDateFormat("dd-MM-yyyy hh-mm-ss");

    private final String accelerometerFile;
    private final String anglesFile;
    private final String bleFile;
    private final String blePositionFile;
    private final String sensorsPositionFile;

    public AndroidLoggableMeasurementTransfer() {
        String dateStr = dateFormat.format(new Date());
        accelerometerFile = String.format(ACCELEROMETER_FILE, dateStr);
        anglesFile = String.format(ANGLES_FILE, dateStr);
        bleFile = String.format(BLE_FILE, dateStr);
        blePositionFile = String.format(POSITION_BLE_FILE, dateStr);
        sensorsPositionFile = String.format(POSITION_SENSORS_FILE, dateStr);
    }


    @Override
    public void log(MeasurementEvent event, double[] position) {
        if (event.getType() == MeasurementType.SENSOR_VALUE) {
            try {
                appendToFile(accelerometerFile, accelFrom(event));
                appendToFile(anglesFile, anglesFrom(event));
                appendToFile(sensorsPositionFile, positionsFrom( event, position));
            } catch (Exception e) {
                Log.w(TAG, "deliver: ", e);
            }
        } else if (event.getType() == MeasurementType.BLUETOOTH_VALUE) {
            try {
                for (MeasurementEvent e : event.getNested()) {
                    appendToFile(bleFile, bleFrom(e));
                }
                appendToFile(blePositionFile, positionsFrom(event, position));
            } catch (Exception e) {
                Log.w(TAG, "deliver: ", e);
            }
        }
    }

    private String positionsFrom(MeasurementEvent event, double [] position) {
        return String.format("%d %f %f %f", event.getTimestamp(), position[0], position[1], position[2]);
    }

    private String bleFrom(MeasurementEvent event) {
        return String.format("%d %s %d %d %f %f", event.getTimestamp(), event.getUuid(),
                (int) event.getData()[0], (int) event.getData()[1], event.getData()[2], event.getData()[3]);
    }

    private String anglesFrom(MeasurementEvent event) {
        return String.format("%d %f %f %f", event.getTimestamp(), event.getData()[3],
                event.getData()[4], event.getData()[5]);
    }

    private String accelFrom(MeasurementEvent event) {
        return String.format("%d %f %f %f", event.getTimestamp(), event.getData()[0],
                event.getData()[1], event.getData()[2]);
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
