package kaa_solutions.com.indoorsdk.ui.main;

import android.os.SystemClock;
import android.util.Log;
import kaa_solutions.com.indoorsdk.ui.main.interfaces.IMainActivity;
import kaa_solutions.com.indoorsdk.ui.main.interfaces.IMainActivityPresenter;
import pro.i_it.indoor.IndoorLocationManager;
import pro.i_it.indoor.OnLocationUpdateListener;
import pro.i_it.indoor.events.MeasurementType;
import pro.i_it.indoor.local.data.DataManager;

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
            public void onLocationChanged(float[] position) {
                if (IS_DEBUG) {
                    Log.d(TAG, "onLocationChanged: " + SystemClock.elapsedRealtime() / 1000 + "  " + Arrays.toString(position));
                }
            }
        });
        localManager.start();
        view.updateData(DataManager.getSettingList());
    }
}
