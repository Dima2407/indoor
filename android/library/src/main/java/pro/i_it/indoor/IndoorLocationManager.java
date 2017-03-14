package pro.i_it.indoor;

import android.content.Context;
import pro.i_it.indoor.events.MeasurementType;
import pro.i_it.indoor.providers.*;

import java.util.HashSet;
import java.util.Set;

public class IndoorLocationManager {

    static {
        System.loadLibrary("native-lib");
    }

    private OnLocationUpdateListener onLocationUpdateListener;

    private OnErrorListener onErrorListener;

    private Set<MeasurementProvider> providers;

    public IndoorLocationManager() {
        this.providers = new HashSet<>();
    }

    public void setOnLocationUpdateListener(OnLocationUpdateListener listener) {
        this.onLocationUpdateListener = listener;
    }

    public void setOnErrorListener(OnErrorListener onErrorListener) {
        this.onErrorListener = onErrorListener;
    }

    public void addProvider(Context context, MeasurementType type, MeasurementTransfer transfer) {
        switch (type) {
            case GEO_VALUE:
                providers.add(new GPSMeasurementProvider(context, transfer));
                break;
            case SENSOR_VALUE:
                break;
            case BLUETOOTH_VALUE:
                providers.add(new BluetoothMeasurementProvider(context, transfer));
                break;
            case WIFI_VALUE:
                providers.add(new WiFiMeasurementProvider(context, transfer));
                break;
        }
    }

    public void addProvider(Context context, MeasurementType type){
        this.addProvider(context, type, new AndroidDebuggableMeasurementTransfer());
    }

    public void start() {
        for (MeasurementProvider provider : providers) {
            provider.start();
        }
    }

    public void stop() {
        for (MeasurementProvider provider : providers) {
            provider.stop();
        }
    }

}
