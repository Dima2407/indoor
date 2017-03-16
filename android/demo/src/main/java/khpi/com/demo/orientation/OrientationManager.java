package khpi.com.demo.orientation;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorManager;
import android.view.Display;
import android.view.Surface;
import android.view.WindowManager;

import khpi.com.demo.core.bridge.OrientationBridge;
import khpi.com.demo.utils.SensorEventListenerWrapper;

import java.util.ArrayList;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

final class OrientationManager {

    private static final long UPDATE_TIME = 800;
    private static final int BUFFER_SIZE_A = 15;
    private static final int BUFFER_SIZE_M = 20;
    private static final int WINDOW_SIZE_D = 10;
    private static final int ANGLES_Q_STEP = 12;

    private final Sensor accelerometerSensor;
    private final Sensor magneticSensor;
    private final SensorManager sensorManager;

    private final Display display;

    private Timer timer;

    private SensorEventListenerWrapper listenerWrapper;

    private float[] valuesAccel;
    private float[] valuesMagnet;

    private List<OrientationBridge.DeviceOrientationListener> listeners;

    OrientationManager(Context context) {
        WindowManager windowManager = (WindowManager) context.getSystemService(Context.WINDOW_SERVICE);

        display = windowManager.getDefaultDisplay();

        sensorManager = (SensorManager) context.getSystemService(Context.SENSOR_SERVICE);
        accelerometerSensor = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        magneticSensor = sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);

        listenerWrapper = new EventListenerWrapper();

        valuesAccel = new float[3];
        valuesMagnet = new float[3];

        listeners = new ArrayList<>();
    }

    void startTracking(OrientationBridge.DeviceOrientationListener listener) {
        boolean needInitSensors = listeners.isEmpty();

        listeners.add(listener);

        if (!needInitSensors) {
            return;
        }

        sensorManager.registerListener(listenerWrapper, accelerometerSensor, SensorManager.SENSOR_DELAY_GAME);
        sensorManager.registerListener(listenerWrapper, magneticSensor, SensorManager.SENSOR_DELAY_GAME);

        timer = new Timer(true);
        timer.schedule(new TimerTask() {
            @Override
            public void run() {
                calculateDeviceOrientation();
            }
        }, 0, UPDATE_TIME);
    }

    private void calculateDeviceOrientation() {
        float[] inR = new float[9];
        float[] outR = new float[9];
        float[] result = new float[3];

        SensorManager.getRotationMatrix(inR, null, valuesAccel, valuesMagnet);

        int axis1 = SensorManager.AXIS_X;
        int axis2 = SensorManager.AXIS_Y;

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

        SensorManager.remapCoordinateSystem(inR, axis1, axis2, outR);
        SensorManager.getOrientation(outR, result);

        result[0] = (int) (Math.toDegrees(result[0]));
        result[1] = (int) (Math.toDegrees(result[1]));
        result[2] = (int) (Math.toDegrees(result[2]));

        result = anglesQuantization(result, ANGLES_Q_STEP);

        for (OrientationBridge.DeviceOrientationListener listener : listeners) {
            listener.onOrientationUpdated(result[0], result[1], result[2]);
        }
    }

    void stopTracking(final OrientationBridge.DeviceOrientationListener deviceOrientationListener) {
        listeners.remove(deviceOrientationListener);

        if (!listeners.isEmpty()) {
            return;
        }

        sensorManager.unregisterListener(listenerWrapper);

        if (timer != null) {
            timer.cancel();
        }
    }

    private class EventListenerWrapper extends SensorEventListenerWrapper {

        EventListenerWrapper() {
            super(BUFFER_SIZE_A, BUFFER_SIZE_M);
        }

        @Override
        public void onSensorChanged(final Sensor sensor, final float[] data, final long timestamp) {
            switch (sensor.getType()) {
                case Sensor.TYPE_ACCELEROMETER:
                    System.arraycopy(data, 0, valuesAccel, 0, 3);
                    break;
                case Sensor.TYPE_MAGNETIC_FIELD:
                    System.arraycopy(data, 0, valuesMagnet, 0, 3);
                    break;
            }
        }

        @Override
        public void onAccuracyChanged(final Sensor sensor, final int i) {
        }
    }

    private float[] anglesQuantization(float[] inputAngles, int qStep) {
        float[] result = new float[inputAngles.length];
        int tempVar;

        for (int i = 0; i < inputAngles.length; i++) {

            float inputAngle = inputAngles[i];
            float dividedAngle = inputAngle / qStep;

            if (inputAngle >= 0) {
                tempVar = (int) Math.floor(dividedAngle);
            } else {
                tempVar = (int) Math.ceil(dividedAngle);
            }

            result[i] = tempVar * qStep;
        }

        return result;
    }
}
