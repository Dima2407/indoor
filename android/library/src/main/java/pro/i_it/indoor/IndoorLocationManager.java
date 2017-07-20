package pro.i_it.indoor;

import android.content.Context;
import android.os.Handler;
import android.os.Message;

import pro.i_it.indoor.config.NativeConfigMap;
import pro.i_it.indoor.events.MeasurementType;
import pro.i_it.indoor.logger.LoggableLocationUpdateListener;
import pro.i_it.indoor.masks.MaskTableFetcher;
import pro.i_it.indoor.providers.*;
import pro.i_it.indoor.region.BeaconsInRegionLoader;
import pro.i_it.indoor.region.SpaceBeacon;
import pro.i_it.indoor.region.SpaceRegion;

import java.util.HashSet;
import java.util.Set;

public class IndoorLocationManager {


    private static final String TAG = IndoorLocationManager.class.getSimpleName();
    public static final int POSITION_REQUEST = 101;
    public static final int POSITION_REQUEST_DELAY = 700;
    private volatile boolean active  = false;

    static {
        System.loadLibrary("native-lib");
    }

    private OnLocationUpdateListener onLocationUpdateListener;

    private OnErrorListener onErrorListener;
    private Handler positionRequester;

    private Set<MeasurementProvider> providers;
    private final float[] lastPosition = new float[]{-1.0f,-1.0f,-1.0f};
    private NativeConfigMap configuration;

    public IndoorLocationManager() {
        this.providers = new HashSet<>();
        this.positionRequester = new Handler(){
            @Override
            public void handleMessage(Message msg) {
                if(active) {
                    nativeTakeLastPosition(lastPosition);
                    if(lastPosition[0] >= 0.0f || lastPosition[1] >= 0.0f){
                        if (onLocationUpdateListener != null) {
                            onLocationUpdateListener.onLocationChanged(lastPosition);
                        }
                    }
                    sendEmptyMessageDelayed(POSITION_REQUEST, POSITION_REQUEST_DELAY);
                }
            }
        };
    }

    public void setOnLocationUpdateListener(OnLocationUpdateListener listener) {
        this.onLocationUpdateListener = new LoggableLocationUpdateListener(listener);
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
        this.addProvider(context, type, AndroidMeasurementTransfer.TRANSFER);
        //this.addProvider(context, type, new AndroidLoggableMeasurementTransfer(new AndroidDebuggableMeasurementTransfer()));
    }

    public void setMapAngle(float angle){
        for(MeasurementProvider p : providers){
            if( p instanceof SensorMeasurementProvider){
                ((SensorMeasurementProvider)p).setMapAngle(angle);
            }
        }
    }

    public double[] getRoute(double x1, double y1, double x2, double y2) {

        return getNativeRoute(x1, y1, x2, y2);
    }

    public void start() {
        active = true;
        for (MeasurementProvider provider : providers) {
            provider.start();
        }
        nativeInit(configuration);
        lastPosition[0] = -1.0f;
        lastPosition[1] = -1.0f;
        lastPosition[2] = -1.0f;
        positionRequester.sendEmptyMessageDelayed(POSITION_REQUEST, POSITION_REQUEST_DELAY);
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

    private native void setGraphArraysFromFile(String fileContent, double scale);

    public void setGraph(String fileContent, double scale){
        if(!active){
            return;
        }
        setGraphArraysFromFile(fileContent, scale);

    }
    //route



    private native void nativeInit(NativeConfigMap configuration);

    private native void nativeRelease();

    private native void nativeTakeLastPosition(float [] position);

    public void setConfiguration(NativeConfigMap configuration) {
        this.configuration = configuration;
    }
}
