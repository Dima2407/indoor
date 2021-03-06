package pro.i_it.indoor;

import android.content.Context;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.os.Message;
import android.util.Log;

import pro.i_it.indoor.config.NativeConfigMap;
import pro.i_it.indoor.events.MeasurementType;
import pro.i_it.indoor.logger.AndroidLoggableMeasurementTransfer;
import pro.i_it.indoor.logger.LoggableLocationUpdateListener;
import pro.i_it.indoor.providers.*;
import pro.i_it.indoor.routing.IndoorRouter;
import pro.i_it.indoor.routing.Route;

import java.util.HashSet;
import java.util.Set;

public class IndoorLocationManager {


    private static final String TAG = IndoorLocationManager.class.getSimpleName();
    public static final int POSITION_REQUEST = 101;
    public static final int POSITION_REQUEST_DELAY = 1000;
    private volatile boolean active  = false;
    private boolean initialized = false;
    private boolean loggerEnable = false;
    private OnInitializationCompletedListener onInitializationCompletedListener;
    private OnBeaconsChangeListener onBeaconsChangeListener;

    private HandlerThread deliverThread;
    private HandlerThread obtainThread;

    public void enableLogger() {
        Log.d("LOGGER", "enableLogger: ");
        loggerEnable = true;
    }

    public void setOnBeaconsChangeListener(OnBeaconsChangeListener onBeaconsChangeListener) {
        this.onBeaconsChangeListener = onBeaconsChangeListener;
    }

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
    private final IndoorRouter router = new IndoorRouter();

    public IndoorLocationManager() {
        this.providers = new HashSet<>();
    }

    private void startLooping(Looper looper) {
        this.positionRequester = new Handler(looper){
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

        positionRequester.sendEmptyMessageDelayed(POSITION_REQUEST, POSITION_REQUEST_DELAY);
    }

    public void setOnLocationUpdateListener(OnLocationUpdateListener listener) {
        if (loggerEnable) {
            this.onLocationUpdateListener = new LoggableLocationUpdateListener(listener);
        } else {
            this.onLocationUpdateListener = listener;
        }
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

    public void start(Context context, NativeConfigMap configuration) {
        active = true;
        initialized = false;
        deliverThread = new HandlerThread(AndroidMeasurementTransfer.class.getSimpleName());
        deliverThread.start();

        obtainThread = new HandlerThread(IndoorLocationManager.class.getSimpleName());
        obtainThread.start();


        AndroidMeasurementTransfer measurementTransfer = new AndroidMeasurementTransfer(deliverThread.getLooper());
        if (loggerEnable) {
            measurementTransfer.setTransfer(new AndroidLoggableMeasurementTransfer());
        }

        if (configuration.getBoolean(NativeConfigMap.KEY_USE_BEACONS)) {
            this.addProvider(context, MeasurementType.BLUETOOTH_VALUE,
                    measurementTransfer);
        }
        if (configuration.getBoolean(NativeConfigMap.KEY_USE_SENSORS)) {
            this.addProvider(context, MeasurementType.SENSOR_VALUE,
                    measurementTransfer);
        }
        for (MeasurementProvider provider : providers) {
            if (provider instanceof BluetoothMeasurementProvider) {
                BluetoothMeasurementProvider blProvider = (BluetoothMeasurementProvider) provider;
                blProvider.setOnBeaconsChangeListener(onBeaconsChangeListener);
            }
            provider.start();
        }
        nativeInit(configuration);
        router.clear();
        startLooping(obtainThread.getLooper());
    }

    public void stop() {
        initialized = false;
        active = false;
        loggerEnable = false;
        deliverThread.quitSafely();
        deliverThread = null;
        obtainThread.quitSafely();
        obtainThread = null;
        for (MeasurementProvider provider : providers) {
            if (provider instanceof BluetoothMeasurementProvider) {
                BluetoothMeasurementProvider blProvider = (BluetoothMeasurementProvider) provider;
                blProvider.setOnBeaconsChangeListener(null);
            }
            provider.stop();
        }
        providers.clear();
        onLocationUpdateListener = null;
        onBeaconsChangeListener = null;
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

    public void clearDestination() {
        router.clearDestination();
    }

    public Route buildRoute(){
        return router.buildRoute();
    }
}
