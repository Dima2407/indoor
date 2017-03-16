package pro.i_it.indoor;

import android.content.Context;
import pro.i_it.indoor.events.MeasurementType;
import pro.i_it.indoor.providers.*;
import pro.i_it.indoor.region.SpaceBeacon;
import pro.i_it.indoor.region.SpaceRegion;

import java.util.HashSet;
import java.util.Set;

public class IndoorLocationManager {

    static {
        System.loadLibrary("native-lib");
    }

    private OnLocationUpdateListener internalLocationUpdateListener;
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
        internalLocationUpdateListener = new OnLocationUpdateListener() {
            @Override
            public void onLocationChanged(float[] position) {
                if(onLocationUpdateListener!= null){
                    onLocationUpdateListener.onLocationChanged(position);
                }
            }
        };
        for (MeasurementProvider provider : providers) {
            provider.start();
        }
        nativeInit(internalLocationUpdateListener);
    }

    public void stop() {
        for (MeasurementProvider provider : providers) {
            provider.stop();
        }
        onLocationUpdateListener = null;
        internalLocationUpdateListener = null;
        nativeRelease();
    }

    public void updateSpaceRegion(SpaceRegion region){
        region.updateRegion();
    }

    //TODO надо реализовать нативный метод, в нем создать обьект навигатора
    //TODO обьект навигатора сохранить глобально
    //TODO также сохранить глобально слушатель переданый как аргумент
    private native void nativeInit(OnLocationUpdateListener onUpdateListener);

    //TODO надо реализовать нативный метод, в нем удалить все что хранилось глобально в нативе
    private native void nativeRelease();

}
