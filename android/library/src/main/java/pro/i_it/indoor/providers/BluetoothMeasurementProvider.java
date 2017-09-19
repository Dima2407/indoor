package pro.i_it.indoor.providers;


import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.RemoteException;
import android.util.Log;
import org.altbeacon.beacon.*;
import pro.i_it.indoor.events.MeasurementEvent;

import java.util.Collection;
import java.util.UUID;

public class BluetoothMeasurementProvider extends MeasurementProvider {

    private OnBeaconsChangeListener onBeaconsChangeListener;
    private static final String TAG = BluetoothMeasurementProvider.class.getSimpleName();
    private final RangeNotifier rangeNotifier = new RangeNotifier() {
        @Override
        public void didRangeBeaconsInRegion(Collection<Beacon> collection, Region region) {
            if (transfer != null) {
                transfer.deliver(MeasurementEvent.createBluetooth(collection));
            }
            if (onBeaconsChangeListener != null) {
                onBeaconsChangeListener.onBeaconsChanged(collection.size());
            }
        }
    };
    private org.altbeacon.beacon.BeaconManager beaconManager;
    private Context context;
    private final BeaconConsumer beaconConsumer = new BeaconConsumer() {
        @Override
        public void onBeaconServiceConnect() {
            Log.d(TAG, "onBeaconServiceConnect: ");
            final Region region = new Region(UUID.randomUUID().toString(), null, null, null);

            beaconManager.addRangeNotifier(rangeNotifier);

            try {
                beaconManager.startRangingBeaconsInRegion(region);
            } catch (RemoteException e) {
                Log.w(TAG, "onBeaconServiceConnect: ", e);
            }
        }

        @Override
        public Context getApplicationContext() {
            return context.getApplicationContext();
        }

        @Override
        public void unbindService(ServiceConnection serviceConnection) {
            context.unbindService(serviceConnection);
        }

        @Override
        public boolean bindService(Intent intent, ServiceConnection serviceConnection, int flags) {
            return context.bindService(intent, serviceConnection, flags);
        }
    };

    public void setOnBeaconsChangeListener(OnBeaconsChangeListener onBeaconsChangeListener) {
        this.onBeaconsChangeListener = onBeaconsChangeListener;
    }

    public BluetoothMeasurementProvider(Context context, MeasurementTransfer transfer) {
        super(transfer);
        this.context = context;
        beaconManager = BeaconManager.getInstanceForApplication(context);
        beaconManager.setForegroundScanPeriod(420);
        beaconManager.setForegroundBetweenScanPeriod(0);
        beaconManager.setBackgroundScanPeriod(1000);
        beaconManager.setBackgroundBetweenScanPeriod(0);

        beaconManager.getBeaconParsers().add(new BeaconParser().setBeaconLayout("m:2-3=0215,i:4-19,i:20-21,i:22-23,p:24-24"));
    }

    @Override
    public void start() {
        beaconManager.removeAllRangeNotifiers();
        beaconManager.removeAllMonitorNotifiers();
        beaconManager.bind(beaconConsumer);
    }

    @Override
    public void stop() {
        beaconManager.removeAllRangeNotifiers();
        beaconManager.removeAllMonitorNotifiers();
        beaconManager.unbind(beaconConsumer);
    }
}
