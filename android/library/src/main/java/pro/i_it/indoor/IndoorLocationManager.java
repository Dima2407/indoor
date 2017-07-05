package pro.i_it.indoor;

import android.content.Context;
import android.util.Log;
import pro.i_it.indoor.events.MeasurementType;
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

    static {
        System.loadLibrary("native-lib");
    }

    private OnLocationUpdateListener internalLocationUpdateListener;
    private OnLocationUpdateListener onLocationUpdateListener;
    private BeaconsInRegionLoader beaconsInRegionLoader;
    private Mode mode = Mode.TRILATERATION_BEACON_NAVIGATOR;
    private CurrentMap currentMap = CurrentMap.KAA_OFFICE;
    private int[] maskArray;
    private Context context;

    private OnErrorListener onErrorListener;

    private Set<MeasurementProvider> providers;

    public IndoorLocationManager() {
        this.providers = new HashSet<>();
    }

    public void setOnLocationUpdateListener(OnLocationUpdateListener listener) {
        this.onLocationUpdateListener = listener;
    }

    public void setBeaconsInRegionLoader(BeaconsInRegionLoader beaconsInRegionLoader) {
        this.beaconsInRegionLoader = beaconsInRegionLoader;
    }

    public void setOnErrorListener(OnErrorListener onErrorListener) {
        this.onErrorListener = onErrorListener;
    }

    public Mode getMode() {
        return mode;
    }

    public void setMode(boolean useBinaryMask) {
        this.mode = useBinaryMask ? Mode.STANDARD_BEACON_NAVIGATOR : Mode.TRILATERATION_BEACON_NAVIGATOR;
    }

    public void setCurrentMap(Context context, CurrentMap map) {
        this.currentMap = map;
        this.context = context;
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
        this.addProvider(context, type, new AndroidDebuggableMeasurementTransfer());
    }

    private void readFileWithMask() {
        List<Integer> maskList = new ArrayList<>();
        int[] maskArray;

        switch (currentMap) {

            case KAA_OFFICE:
                try (BufferedReader br = new BufferedReader(new InputStreamReader(context.getResources()
                        .openRawResource(R.raw.masktable2)))) {
                    String str;
                    while ((str = br.readLine()) != null) {
                        maskList.add(Integer.valueOf(str.trim()));
                    }
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                maskArray = new int[maskList.size()];
                for (int i = 0; i < maskArray.length; i++)
                    maskArray[i] = maskList.get(i);
                this.maskArray = maskArray;
                break;

            case IT_JIM:
                try (BufferedReader br = new BufferedReader(new InputStreamReader(context.getResources()
                        .openRawResource(R.raw.masktable1)))) {
                    String str;
                    while ((str = br.readLine()) != null) {
                        maskList.add(Integer.valueOf(str.trim()));
                    }
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                maskArray = new int[maskList.size()];
                for (int i = 0; i < maskArray.length; i++)
                    maskArray[i] = maskList.get(i);
                this.maskArray = maskArray;
                break;
        }
    }

    public double[] getRoute(double x1, double y1, double x2, double y2) {

        return getNativeRoute(x1, y1, x2, y2);
    }

    public void start() {
        setNativeCurrentMap(currentMap.code);
        readFileWithMask();
        setNativeMaskArray(maskArray);
        internalLocationUpdateListener = new OnLocationUpdateListener() {
            @Override
            public void onLocationChanged(float[] position) {
                if (onLocationUpdateListener != null) {
                  //  position = new float[]{1f, 1.0f, 0, 0};
                    onLocationUpdateListener.onLocationChanged(position);
                }
                if (beaconsInRegionLoader != null) {
                    SpaceRegion region = beaconsInRegionLoader.onLocationChanged(position[0], position[1], position[2]);
                    if (region.isChanged()) {
                        Set<SpaceBeacon> beacons = region.getBeacons();
                        SpaceBeacon[] data = new SpaceBeacon[beacons.size()];
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
        nativeInit(mode.getCode(), internalLocationUpdateListener);
    }

    public void stop() {
       /* for (MeasurementProvider provider : providers) {
            provider.stop();
        }*/
        onLocationUpdateListener = null;
        internalLocationUpdateListener = null;
        nativeRelease();
    }

    private native double[] getNativeRoute(double x1, double y1, double x2, double y2);

    public native void setGraphArraysFromFile(String fileContent, double scale);

    private native void setNativeMaskArray(int[] mask);

    private native void setNativeCurrentMap(int map);

    private native void nativeInit(int modeType, OnLocationUpdateListener onUpdateListener);

    private native void nativeRelease();

    private native void nativeSetBeacons(SpaceBeacon[] beacons);

    public native void callEvent();

    public enum Mode {
        @Deprecated
        TRILATERATION_BEACON_NAVIGATOR(0),
        STANDARD_BEACON_NAVIGATOR(1);

        private int code;

        Mode(int code) {
            this.code = code;
        }

        public int getCode() {
            return code;
        }
    }

    public enum CurrentMap {
        KAA_OFFICE(0),
        IT_JIM(1);

        private int code;

        CurrentMap(int code) {
            this.code = code;
        }
    }
}
