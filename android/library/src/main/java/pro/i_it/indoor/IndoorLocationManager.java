package pro.i_it.indoor;

import android.content.Context;
import android.os.Handler;
import android.util.Log;
import pro.i_it.indoor.events.MeasurementType;
import pro.i_it.indoor.masks.MaskTableFetcher;
import pro.i_it.indoor.mesh.MeshConfig;
import pro.i_it.indoor.providers.*;
import pro.i_it.indoor.region.BeaconsInRegionLoader;
import pro.i_it.indoor.region.SpaceBeacon;
import pro.i_it.indoor.region.SpaceRegion;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class IndoorLocationManager {


    private static final String TAG = IndoorLocationManager.class.getSimpleName();
    private volatile boolean active  = false;

    static {
        System.loadLibrary("native-lib");
    }

    private OnLocationUpdateListener onLocationUpdateListener;
    private BeaconsInRegionLoader beaconsInRegionLoader;
    private Mode mode = Mode.TRILATERATION_BEACON_NAVIGATOR;

    private OnErrorListener onErrorListener;
    private Handler positionRequester;

    private Set<MeasurementProvider> providers;
    private MaskTableFetcher maskTableFetcher;
    private MeshConfig meshConfig;

    public IndoorLocationManager() {
        this.providers = new HashSet<>();
        this.positionRequester = new Handler();
    }

    public void setOnLocationUpdateListener(OnLocationUpdateListener listener) {
        this.onLocationUpdateListener = new LoggableLocationUpdateListener(listener);
    }

    public void setBeaconsInRegionLoader(BeaconsInRegionLoader beaconsInRegionLoader) {
        this.beaconsInRegionLoader = beaconsInRegionLoader;
    }

    public void setOnErrorListener(OnErrorListener onErrorListener) {
        this.onErrorListener = onErrorListener;
    }

    public void setMode(Mode mode) {
        this.mode = mode;
    }

    public void addProvider(Context context, MeasurementType type, MeasurementTransfer transfer) {
        switch (type) {
            case GEO_VALUE:
                providers.add(new GPSMeasurementProvider(context, transfer));
                break;
            case SENSOR_VALUE:
                providers.add(new SensorMeasurementProvider(context,transfer));
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
        this.addProvider(context, type, new AndroidLoggableMeasurementTransfer(new AndroidDebuggableMeasurementTransfer()));
    }

    public void useMask(MeshConfig meshConfig, MaskTableFetcher fetcher){
        this.meshConfig  = meshConfig;
        this.maskTableFetcher = fetcher;
    }

    public void setMapAngle(float angle){
        for(MeasurementProvider p : providers){
            if( p instanceof SensorMeasurementProvider){
                ((SensorMeasurementProvider)p).setMapAngle(angle);
            }
        }
    }

    public double[] getRoute(double x1, double y1, double x2, double y2) {

        return getRoute(x1, y1, x2, y2);
    }

    public void start() {
        active = true;
        for (MeasurementProvider provider : providers) {
            provider.start();
        }
        nativeInit(mode.getCode(), maskTableFetcher.fetchMaskTable(), meshConfig);
        final float[] lastPosition = new float[]{-1.0f,-1.0f,-1.0f};
        positionRequester.postDelayed(new Runnable() {
            @Override
            public void run() {
                if(active) {
                    nativeTakeLastPosition(lastPosition);
                    if(lastPosition[0] >= 0.0f || lastPosition[1] >= 0.0f){
                        if (onLocationUpdateListener != null) {
                            onLocationUpdateListener.onLocationChanged(lastPosition);
                        }
                        if (beaconsInRegionLoader != null) {
                            SpaceRegion region = beaconsInRegionLoader.onLocationChanged(lastPosition[0], lastPosition[1], lastPosition[2]);
                            if (region.isChanged()) {
                                Set<SpaceBeacon> beacons = region.getBeacons();
                                SpaceBeacon[] data = new SpaceBeacon[beacons.size()];
                                beacons.toArray(data);
                                Log.d("TAGBEACON", "setBeacons, region.getBeacons.SIZE + " + region.getBeacons().size());
                                nativeSetBeacons(data);
                            }
                        }
                    }
                    positionRequester.postDelayed(this, 100);
                }
            }
        }, 100);

    }

    public void stop() {
        active = false;
        for (MeasurementProvider provider : providers) {
            provider.stop();
        }
        onLocationUpdateListener = null;
        positionRequester.removeCallbacksAndMessages(null);
        nativeRelease();
    }
    //route

    private native double[] getNativeRoute(double x1, double y1, double x2, double y2);

    //route
    public native void setGraphArraysFromFile(String fileContent, double scale);

    private native void nativeInit(int modeType, int[] mask, MeshConfig config);

    private native void nativeRelease();

    private native void nativeSetBeacons(SpaceBeacon[] beacons);

    private native void nativeTakeLastPosition(float [] position);

    public enum Mode {
        @Deprecated
        TRILATERATION_BEACON_NAVIGATOR(0),
        @Deprecated
        STANDARD_BEACON_NAVIGATOR(1),
        SENSOR_BEACON_NAVIGATOR(2);

        private int code;

        Mode(int code) {
            this.code = code;
        }

        public int getCode() {
            return code;
        }
    }
}
