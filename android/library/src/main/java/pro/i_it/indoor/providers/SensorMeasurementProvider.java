package pro.i_it.indoor.providers;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.util.Pair;
import android.view.Display;
import android.view.Surface;
import android.view.WindowManager;
import pro.i_it.indoor.events.MeasurementEvent;

public class SensorMeasurementProvider extends MeasurementProvider {

    private static final int SENSOR_RATE = SensorManager.SENSOR_DELAY_GAME;
    private final SensorManager sensorManager;
    private final Context context;
    private Pair<Integer, Integer> axis;
    private float[] magneticValues;
    private float[] accelerometerValues;
    private float[] inR;
    private float[] outR;
    private float[] result;
    private final SensorEventListener sensorDataListener = new SensorEventListener() {
        @Override
        public void onSensorChanged(SensorEvent event) {
            if (event.sensor.getType() == Sensor.TYPE_ACCELEROMETER) {
                if (accelerometerValues == null) {
                    accelerometerValues = new float[3];
                }
                System.arraycopy(event.values, 0, accelerometerValues, 0, 3);
            }

            if (event.sensor.getType() == Sensor.TYPE_MAGNETIC_FIELD) {
                if (magneticValues == null) {
                    magneticValues = new float[3];
                }
                System.arraycopy(event.values, 0, magneticValues, 0, 3);
            }

            if (accelerometerValues != null && magneticValues != null) {
                float[] xyzA = accelerometerValues;
                float[] xyzM = magneticValues;
                float ax = (accelerometerValues[0] / 9.81f);
                float ay = (accelerometerValues[1] / 9.81f);
                float az = (accelerometerValues[2] / 9.81f);

                SensorManager.getRotationMatrix(inR, null, xyzA, xyzM);


                SensorManager.remapCoordinateSystem(inR, axis.first, axis.second, outR);
                SensorManager.getOrientation(outR, result);
                result[0] = (float) Math.toDegrees(result[0]);
                result[1] = (float) Math.toDegrees(result[1]);
                result[2] = (float) Math.toDegrees(result[2]);

                float azimut = result[0] * (-1);
                float pitch = result[1] * (-1);
                float roll = result[2];

                if (transfer != null) {
                    final MeasurementEvent measurementEvent = MeasurementEvent.createFromSensor(ax, ay, az, azimut, pitch, roll);
                    transfer.deliver(measurementEvent);

                }

            }
        }

        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {

        }
    };


    public SensorMeasurementProvider(Context context, MeasurementTransfer transfer) {
        super(transfer);
        this.context = context.getApplicationContext();
        this.sensorManager = (SensorManager) context.getSystemService(Context.SENSOR_SERVICE);
    }

    @Override
    public void start() {

        axis = getDeviceAxis();
        inR = new float[9];
        outR = new float[9];
        result = new float[3];
        Sensor sensorA = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        Sensor sensorM = sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
        sensorManager.registerListener(sensorDataListener, sensorA, SENSOR_RATE);
        sensorManager.registerListener(sensorDataListener, sensorM, SENSOR_RATE);
    }

    @Override
    public void stop() {
        sensorManager.unregisterListener(sensorDataListener);
        axis = null;
        inR = null;
        outR = null;
        result = null;
        magneticValues = null;
        accelerometerValues = null;
    }

    private Pair<Integer, Integer> getDeviceAxis() {
        int axis1 = SensorManager.AXIS_X;
        int axis2 = SensorManager.AXIS_Y;

        WindowManager windowManager = (WindowManager) context.getSystemService(Context.WINDOW_SERVICE);
        Display display = windowManager.getDefaultDisplay();
        int rotation = display.getRotation();

        switch (rotation) {
            case Surface.ROTATION_0:
                break;
            case Surface.ROTATION_90:
                axis1 = SensorManager.AXIS_Y;
                axis2 = SensorManager.AXIS_MINUS_X;
                break;
            case Surface.ROTATION_180:
                axis2 = SensorManager.AXIS_MINUS_Y;
                break;
            case Surface.ROTATION_270:
                axis1 = SensorManager.AXIS_MINUS_Y;
                axis2 = SensorManager.AXIS_X;
                break;
            default:
                break;
        }
        return new Pair<>(axis1, axis2);
    }
}
