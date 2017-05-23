package pro.i_it.indoor;

import android.app.Activity;
import android.content.Context;
import android.util.Log;

import pro.i_it.indoor.events.MeasurementType;
import pro.i_it.indoor.providers.*;
import pro.i_it.indoor.region.BeaconsInRegionLoader;
import pro.i_it.indoor.region.InMemoryBeaconsLoader;
import pro.i_it.indoor.region.SpaceBeacon;
import pro.i_it.indoor.region.SpaceRegion;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import static pro.i_it.indoor.DebugConfig.TAG;

public class IndoorLocationManager {


    private static final String TAG = IndoorLocationManager.class.getSimpleName();

    static {
        System.loadLibrary("native-lib");
    }

    private OnLocationUpdateListener internalLocationUpdateListener;
    private OnLocationUpdateListener onLocationUpdateListener;
    private BeaconsInRegionLoader beaconsInRegionLoader;
    private Mode mode;
    private CurrentMap currentMap;
    private int[] maskArray;
    private Context context;
    private int[] graphArray;
    private double[] edgesArray;

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


    public void setMode(boolean useBinaryMask) {
        this.mode = useBinaryMask ? Mode.STANDARD_BEACON_NAVIGATOR : Mode.TRILAT_BEACON_NAVIGATOR;
    }

    public Mode getMode() {
        return mode;
    }

    public void setCurrentMap(Context context, CurrentMap map) {
        currentMap = map;
        this.context = context;
    }

  /*  public void setMaskArray(int[] maskArray){
        this.maskArray = maskArray;
    }*/

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

    private void readFileWithMask() {
        List<Integer> maskList = new ArrayList<>();
        int[] maskArray;

        switch (currentMap){

            case KAA_OFFICE:
                try (BufferedReader br = new BufferedReader(new InputStreamReader(context.getResources()
                        .openRawResource(R.raw.masktable2)))) {
                    String str;
                    while ((str = br.readLine()) != null) {
                        //Log.i(TAG, "read file : " + str);
                        maskList.add(Integer.valueOf(str.trim()));
                        //Log.i(TAG, "read maskList : " + str);
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
                       // Log.i(TAG, "read file : " + str);
                        maskList.add(Integer.valueOf(str.trim()));
                       // Log.i(TAG, "read maskList : " + str);
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

    public void setNodes(List<Integer> graphList){
        Log.i("locationManager", "setNodes started");
        graphArray = new int[graphList.size()];
        for (int i = 0; i < graphList.size(); i++){
            graphArray[i] = graphList.get(i);
            //  Log.i(TAG, "graphArray = " + graphArray[i]);
        }
        setNativeGraphArray(graphArray);
    }

    public void setEdges(List<Double> edgesList){
        Log.i("locationManager", "setEdges started");
        edgesArray = new double[edgesList.size()];
        for (int i = 0; i < edgesList.size(); i++){
            edgesArray[i] = edgesList.get(i);
            //  Log.i(TAG, "edgesArray = " + edgesArray[i]);
        }
        setNativeEdgesArray(edgesArray);
    }

    /*private void readFileWithGraph() {
        List<Integer> graphList = new ArrayList<>();
        List<Double> edgesList = new ArrayList<>();
        try (BufferedReader br = new BufferedReader(new InputStreamReader(context.getResources()
                .openRawResource(R.raw.graph1)))) {
            String str = br.readLine(); // пропускаем первую строку
            while (!(str = br.readLine()).equals("->EDGES")) {
                String[] s = str.trim().split(" ");
                graphList.add(Integer.valueOf(s[0]));
                graphList.add(Integer.valueOf(s[1]));

            }
            while ((str = br.readLine()) != null){
                String[] s = str.trim().split(" ");
                edgesList.add(Double.valueOf(s[0]));
                edgesList.add(Double.valueOf(s[1]));
                edgesList.add(Double.valueOf(s[2]));
            }
            graphArray = new int[graphList.size()];
            edgesArray = new double[edgesList.size()];
            for (int i = 0; i < graphList.size(); i++){
                graphArray[i] = graphList.get(i);
              //  Log.i(TAG, "graphArray = " + graphArray[i]);
            }
            for (int i = 0; i < edgesList.size(); i++){
                edgesArray[i] = edgesList.get(i);
              //  Log.i(TAG, "edgesArray = " + edgesArray[i]);
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }*/

    public double[] getRoute(double x1, double y1, double x2, double y2){
       // Log.i("locationManager", "instance.getRoute started");
        Log.i("locationManager", "x1 = " + x1 + ", y1 = " + y1 + ", x2 = " + x2 + ", y2 = " + y2);
        return getNativeRoute(x1, y1, x2, y2);
    }

    public void start() {
        setNativeMode(mode.code);
        setNativeCurrentMap(currentMap.code);
        readFileWithMask();
        setNativeMaskArray(maskArray);
      //  readFileWithGraph();
       /* for (int b:graphArray) {
            Log.i("locationManager", "graphArray = " + b);
        }*/
    /*    Log.i("locationManager", "setNativeGraphArray started");
        setNativeGraphArray(graphArray);
        Log.i("locationManager", "setNativeEdgesArray started");
        setNativeEdgesArray(edgesArray);
        Log.i("locationManager", "setNativeEdgesArray end");*/
        internalLocationUpdateListener = new OnLocationUpdateListener() {
            @Override
            public void onLocationChanged(float[] position) {
                if (onLocationUpdateListener != null) {
                      position = new float[]{1f, 1.0f, 0, 0};
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
        Log.i("locationManager", "nativeInit started");
        nativeInit(internalLocationUpdateListener);
        Log.i("locationManager", "nativeInit end");
    }

    public void stop() {
        for (MeasurementProvider provider : providers) {
            provider.stop();
        }
        onLocationUpdateListener = null;
        internalLocationUpdateListener = null;
        nativeRelease();
    }

    public enum Mode{
        TRILAT_BEACON_NAVIGATOR(0),
        STANDARD_BEACON_NAVIGATOR(1);

        private int code;

        Mode(int code) {

            this.code = code;
        }
    }

    public enum CurrentMap{
        KAA_OFFICE(0),
        IT_JIM(1);

        private int code;

        CurrentMap(int code) {
            this.code = code;
        }
    }

    private native double[] getNativeRoute(double x1, double y1, double x2, double y2);

    public native void setGraphArraysFromFile(String fileContent, double scale);

    private native void setNativeGraphArray(int[] graphs);

    private native void setNativeEdgesArray(double[] edges);

    private native void setNativeMaskArray(int[] mask);

    private native void setNativeCurrentMap(int map);

    private native void setNativeMode(int mode);

    private native void nativeInit(OnLocationUpdateListener onUpdateListener);

    private native void nativeRelease();

    private native void nativeSetBeacons(SpaceBeacon[] beacons);

    public native void callEvent();
}
