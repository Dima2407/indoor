package kaa_solutions.com.indoorsdk;

import android.app.Activity;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;

public class SensorActivity extends Activity implements SensorEventListener {
    public static final String TAG_ACCELEROMETER = "Accelerometer";
    public static final String TAG_MAGNETIC_FIELD = "Magnetic field";
    public static final String TAG_GYROSCOPE = "Gyroscope";
    public static final String TAG_LINEAR_ACCELERATION = "Linear acceleration";

    private SensorManager sensorManager;
    private boolean showValueOfTheSensor = false;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.sensor_activity);

        findViewById(R.id.btn_show_value).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showValueOfTheSensor = true;
            }
        });

        findViewById(R.id.btn_not_show_value).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showValueOfTheSensor = false;
            }
        });

        sensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        if (showValueOfTheSensor) {
            getSensorValues(event);
        }
    }

    private void getSensorValues(SensorEvent event) {
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

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }

    @Override
    protected void onResume() {
        super.onResume();
        sensorManager.registerListener(this, sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER), SensorManager.SENSOR_DELAY_NORMAL);
        sensorManager.registerListener(this, sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD), SensorManager.SENSOR_DELAY_FASTEST);
        sensorManager.registerListener(this, sensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE), SensorManager.SENSOR_DELAY_FASTEST);
        sensorManager.registerListener(this, sensorManager.getDefaultSensor(Sensor.TYPE_LINEAR_ACCELERATION), SensorManager.SENSOR_DELAY_FASTEST);
    }

    @Override
    protected void onPause() {
        super.onPause();
        sensorManager.unregisterListener(this, sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER));
        sensorManager.unregisterListener(this, sensorManager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD));
        sensorManager.unregisterListener(this, sensorManager.getDefaultSensor(Sensor.TYPE_GYROSCOPE));
        sensorManager.unregisterListener(this, sensorManager.getDefaultSensor(Sensor.TYPE_LINEAR_ACCELERATION));
    }
}
