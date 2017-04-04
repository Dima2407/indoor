package com.kit.indornavigation.core;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.RemoteException;

import com.github.alwayswannasleep.models.BeaconModel;

import org.altbeacon.beacon.Beacon;
import org.altbeacon.beacon.BeaconConsumer;
import org.altbeacon.beacon.BeaconManager;
import org.altbeacon.beacon.BeaconParser;
import org.altbeacon.beacon.RangeNotifier;
import org.altbeacon.beacon.Region;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by ivan.k on 21.06.2016.
 */
public class BeaconSearcher implements BeaconConsumer, RangeNotifier {

    public static String FRAME_EDDISTONE_UID = "s:0-1=feaa,m:2-2=00,p:3-3:-41,i:4-13,i:14-19";

    private final BeaconManager beaconManager;
    private Context context;

    private HashMap<String, Long> updates = new HashMap<>();
    private HashMap<String, Beacon> beacons = new HashMap<>();

    private List<BeaconListener> listeners = new ArrayList<>();

    public BeaconSearcher(Context context) {
        this.context = context;
        beaconManager = BeaconManager.getInstanceForApplication(context.getApplicationContext());
        beaconManager.setBackgroundScanPeriod(500);
        beaconManager.setForegroundScanPeriod(420);
        beaconManager.setBackgroundBetweenScanPeriod(0);
        beaconManager.getBeaconParsers().add(new BeaconParser().setBeaconLayout(FRAME_EDDISTONE_UID));
        beaconManager.getBeaconParsers().add(new BeaconParser().setBeaconLayout("m:2-3=0215,i:4-19,i:20-21,i:22-23," +
                "p:24-24"));
        beaconManager.bind(this);
    }

    @Override
    public void onBeaconServiceConnect() {
        try {
            beaconManager.startRangingBeaconsInRegion(new Region("all-beacons-region", null, null, null));
        } catch (RemoteException e) {
            e.printStackTrace();
        }
        beaconManager.setRangeNotifier(this);


    }

    @Override
    public Context getApplicationContext() {
        return context;
    }

    @Override
    public void unbindService(ServiceConnection serviceConnection) {
        context.unbindService(serviceConnection);
    }

    @Override
    public boolean bindService(Intent intent, ServiceConnection serviceConnection, int i) {
        return context.bindService(intent, serviceConnection, i);
    }

    @Override
    public void didRangeBeaconsInRegion(Collection<Beacon> collection, Region region) {
        addToCollection(collection);
    }

    private void addToCollection(Collection<Beacon> collection) {

        for (Map.Entry<String, Long> entry : updates.entrySet()) {
            String key = entry.getKey();
            Long value = entry.getValue();
            if (System.currentTimeMillis() - value > 5000) {
                beacons.remove(key);
            }
        }

        for (Beacon beacon : collection) {
            beacons.put(beacon.getBluetoothAddress(), beacon);
            updates.put(beacon.getBluetoothAddress(), System.currentTimeMillis());
        }


        Collection<Beacon> values = beacons.values();
        for (BeaconListener listener : listeners) {
            listener.onBeaconsDetected(values, collection);
        }
    }

    public void addListener(BeaconListener beaconListener) {
        listeners.add(beaconListener);
    }

    public void removeListener(BeaconListener beaconListener) {
        listeners.remove(beaconListener);
    }

    public boolean isBluetoothEnabled(Activity context) {
        BluetoothAdapter mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (mBluetoothAdapter == null) {
            return false;
        } else {
            if (!mBluetoothAdapter.isEnabled()) {
                return false;
            }
        }
        return true;
    }

    public boolean checkAvailability() {
        try {
            beaconManager.checkAvailability();
        } catch (Exception e) {
            return false;
        }
        return true;
    }

    public List<BeaconModel> getBeacons() {
        List<BeaconModel> result = new ArrayList<>();

        for (Beacon beacon : beacons.values()) {
            BeaconModel beaconModel = new BeaconModel();
            beaconModel.setMacAddress(beacon.getBluetoothAddress());
            beaconModel.setMajor(beacon.getId2().toInt());
            beaconModel.setMinor(beacon.getId3().toInt());

            result.add(beaconModel);
        }

        return result;
    }

    public interface BeaconListener {
        void onBeaconsDetected(Collection<Beacon> stableBeacons, Collection<Beacon> currentBeacons);
    }
}
