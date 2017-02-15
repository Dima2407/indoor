package kaa_solutions.com.indoorsdk;

import android.app.Activity;
import android.hardware.SensorEvent;
import android.os.Bundle;
import android.view.View;

public class SensorActivity extends Activity {

    SensorCoordinateManager sensorCoordinateManager;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.sensor_activity);
        sensorCoordinateManager = new SensorCoordinateManager(this);

        final IOnSensorChangedListener listener = new IOnSensorChangedListener() {
            @Override
            public void OnSensorChanged(SensorEvent event) {
            }
        };

        findViewById(R.id.btn_show_value).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sensorCoordinateManager.addListener(listener);
            }
        });

        findViewById(R.id.btn_not_show_value).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                sensorCoordinateManager.removeListener(listener);
            }
        });
    }

}
