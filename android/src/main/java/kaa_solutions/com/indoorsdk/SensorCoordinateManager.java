package kaa_solutions.com.indoorsdk;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.util.Log;

import java.util.ArrayList;
import java.util.List;

public class SensorCoordinateManager implements SensorEventListener {

    public static final String TAG_ACCELEROMETER = "Accelerometer";
    public static final String TAG_MAGNETIC_FIELD = "Magnetic field";
    public static final String TAG_GYROSCOPE = "Gyroscope";
    public static final String TAG_LINEAR_ACCELERATION = "Linear acceleration";

    SensorManager sensorManager;
    List<IOnSensorChangedListener> listeners = new ArrayList<IOnSensorChangedListener>();

    public SensorCoordinateManager(Context context) {
        sensorManager = (SensorManager) context.getSystemService(Context.SENSOR_SERVICE);
    }


    public void getSensorValues(SensorEvent event) {
        switch (event.sensor.getType()) {
            case Sensor.TYPE_ACCELEROMETER:
                mappingSensorValues(event, TAG_ACCELEROMETER);
                break;
            case Sensor.TYPE_MAGNETIC_FIELD:
                mappingSensorValues(event, TAG_MAGNETIC_FIELD);
                break;
            case Sensor.TYPE_GYROSCOPE:
                mappingSensorValues(event, TAG_GYROSCOPE);
                break;
            case Sensor.TYPE_LINEAR_ACCELERATION:
                mappingSensorValues(event, TAG_LINEAR_ACCELERATION);
                break;
        }
    }

    private void mappingSensorValues(SensorEvent event, String tag) {
        float[] values = event.values;
        float x = values[0];
        float y = values[1];
        float z = values[2];
        Log.d(tag, tag + ": " + "x: " + x + ", y: " + y + ", z: " + z);
    }

    public void addListener(IOnSensorChangedListener listener) {
        tryRegisterListener();
        listeners.add(listener);
    }

    public void removeListener(IOnSensorChangedListener listener) {
        listeners.remove(listener);
        tryUnregisterListener();
    }

    private void tryRegisterListener() {
        if (!listeners.isEmpty()) {
            return;
        }
        sensorManager.registerListener(this, sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_NORMAL);
        sensorManager.registerListener(this, sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD), SensorManager.SENSOR_DELAY_FASTEST);
        sensorManager.registerListener(this, sensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE), SensorManager.SENSOR_DELAY_FASTEST);
        sensorManager.registerListener(this, sensorManager.getDefaultSensor(Sensor.TYPE_LINEAR_ACCELERATION), SensorManager.SENSOR_DELAY_FASTEST);
    }

    private void tryUnregisterListener() {
        if (!listeners.isEmpty()) {
            return;
        }
        sensorManager.unregisterListener(this, sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER));
        sensorManager.unregisterListener(this, sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD));
        sensorManager.unregisterListener(this, sensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE));
        sensorManager.unregisterListener(this, sensorManager.getDefaultSensor(Sensor.TYPE_LINEAR_ACCELERATION));
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        for (int i = 0; i < listeners.size(); i++) {
            listeners.get(i).sensorChanged(event);
        }

    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }


}
