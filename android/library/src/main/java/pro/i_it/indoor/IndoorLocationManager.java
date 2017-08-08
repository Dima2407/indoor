package pro.i_it.indoor;

import android.content.Context;
import android.os.Handler;
import android.os.Message;

import pro.i_it.indoor.config.NativeConfigMap;
import pro.i_it.indoor.events.MeasurementType;
import pro.i_it.indoor.logger.LoggableLocationUpdateListener;
import pro.i_it.indoor.providers.*;
import pro.i_it.indoor.routing.IndoorRouter;
import pro.i_it.indoor.routing.Route;

import java.util.HashSet;
import java.util.Set;

public class IndoorLocationManager {


    private static final String TAG = IndoorLocationManager.class.getSimpleName();
    public static final int POSITION_REQUEST = 101;
    public static final int POSITION_REQUEST_DELAY = 700;
    private volatile boolean active  = false;
    private boolean initialized = false;
    private OnInitializationCompletedListener onInitializationCompletedListener;

    public void setOnInitializationCompletedListener(OnInitializationCompletedListener onInitializationCompletedListener) {
        this.onInitializationCompletedListener = onInitializationCompletedListener;
    }

    static {
        System.loadLibrary("native-lib");
    }

    private OnLocationUpdateListener onLocationUpdateListener;

    private OnErrorListener onErrorListener;
    private Handler positionRequester;

    private Set<MeasurementProvider> providers;
    private NativeConfigMap configuration;
    private final IndoorRouter router = new IndoorRouter();

    public IndoorLocationManager() {
        this.providers = new HashSet<>();
        this.positionRequester = new Handler(){
            @Override
            public void handleMessage(Message msg) {
                if(active) {
                    nativeTakeLastPositionWithDestination(router);
                    if(router.positionDetected()){
                        if (onInitializationCompletedListener != null && !initialized) {
                            onInitializationCompletedListener.onInitializationCompleted();
                            initialized = true;
                        }
                        if (onLocationUpdateListener != null) {
                            onLocationUpdateListener.onLocationChanged(router.getStartPosition(), router.getRoute());
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

    public void start() {
        active = true;
        initialized = false;
        for (MeasurementProvider provider : providers) {
            provider.start();
        }
        nativeInit(configuration);
        router.clear();
        positionRequester.sendEmptyMessageDelayed(POSITION_REQUEST, POSITION_REQUEST_DELAY);
    }

    public void stop() {
        initialized = false;
        configuration = null;
        active = false;
        for (MeasurementProvider provider : providers) {
            provider.stop();
        }
        onLocationUpdateListener = null;
        positionRequester.removeCallbacksAndMessages(null);
        nativeRelease();
        router.clear();
    }

    public void setDestination(float destinationX, float destinationY, double pixelSize){
        router.setDestination(destinationX,destinationY, pixelSize);
    }

    private native void nativeInit(NativeConfigMap configuration);

    private native void nativeRelease();

    private native void nativeTakeLastPositionWithDestination(IndoorRouter router);


    public void setConfiguration(NativeConfigMap configuration) {
        this.configuration = configuration;
    }

    public void clearDestination() {
        router.clearDestination();
    }

    public Route buildRoute(){
        return router.buildRoute();
    }
}
