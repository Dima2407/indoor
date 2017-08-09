package kaa_solutions.com.indoorsdk.ui.main;

import android.graphics.PointF;
import android.os.SystemClock;
import android.util.Log;
import kaa_solutions.com.indoorsdk.ui.main.interfaces.IMainActivity;
import kaa_solutions.com.indoorsdk.ui.main.interfaces.IMainActivityPresenter;
import pro.i_it.indoor.IndoorLocationManager;
import pro.i_it.indoor.OnLocationUpdateListener;
import pro.i_it.indoor.events.MeasurementType;

import java.util.Arrays;

import static pro.i_it.indoor.config.DebugConfig.IS_DEBUG;

public class MainActivityPresenter implements IMainActivityPresenter {
    private static final String TAG = MainActivityPresenter.class.getSimpleName();
    private IMainActivity view;
    private IndoorLocationManager localManager;

    @Override
    public void init(IMainActivity view) {
        this.view = view;
        localManager = new IndoorLocationManager();
        localManager.addProvider(view.getActivity(), MeasurementType.BLUETOOTH_VALUE);
        localManager.addProvider(view.getActivity(), MeasurementType.GEO_VALUE);
        localManager.addProvider(view.getActivity(), MeasurementType.SENSOR_VALUE);
        localManager.addProvider(view.getActivity(), MeasurementType.WIFI_VALUE);
        localManager.setOnLocationUpdateListener(new OnLocationUpdateListener() {
            @Override
            public void onLocationChanged(PointF position, float[] route) {

            }
        });
        localManager.start();
    }
}
