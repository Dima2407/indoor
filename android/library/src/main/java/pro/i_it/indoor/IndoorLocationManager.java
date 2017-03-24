package pro.i_it.indoor;

import android.content.Context;
import android.util.Log;

import pro.i_it.indoor.events.MeasurementType;
import pro.i_it.indoor.providers.*;
import pro.i_it.indoor.region.BeaconsInRegionLoader;
import pro.i_it.indoor.region.InMemoryBeaconsLoader;
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
    private BeaconsInRegionLoader beaconsInRegionLoader;

    private OnErrorListener onErrorListener;

    private Set<MeasurementProvider> providers;

    public IndoorLocationManager() {
        this.providers = new HashSet<>();
    }

    public void setOnLocationUpdateListener(OnLocationUpdateListener listener) {
        this.onLocationUpdateListener = listener;
    }

    public void setBeaconsInRegionLoader(BeaconsInRegionLoader beaconsInRegionLoader){
        this.beaconsInRegionLoader = beaconsInRegionLoader;
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

    public void addProvider(Context context, MeasurementType type) {
        this.addProvider(context, type, new AndroidDebuggableMeasurementTransfer());
    }

    public void start() {
        internalLocationUpdateListener = new OnLocationUpdateListener() {
            @Override
            public void onLocationChanged(float[] position) {
                if (onLocationUpdateListener != null) {
                    onLocationUpdateListener.onLocationChanged(position);
                }
                if (beaconsInRegionLoader != null) {
                    SpaceRegion region = beaconsInRegionLoader.onLocationChanged(position[0], position[1], position[2]);
                    if(region.isChanged()){
                        Set<SpaceBeacon> beacons = region.getBeacons();
                        SpaceBeacon [] data = new SpaceBeacon[beacons.size()];
                        beacons.toArray(data);
                        Log.d("TAGBEACON", "setBeacons, region.getBeacons.SIZE + " + region.getBeacons().size());
                        nativeSetBeacons(data);
                    }
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

    private native void nativeInit(OnLocationUpdateListener onUpdateListener);

    private native void nativeRelease();

    private native void nativeSetBeacons(SpaceBeacon[] beacons);

}
