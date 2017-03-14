package pro.i_it.indoor.providers;


import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.RemoteException;
import android.util.Log;
import org.altbeacon.beacon.*;
import pro.i_it.indoor.events.MeasurementEvent;
import pro.i_it.indoor.local.beacon.model.AltBeaconConfigModel;
import pro.i_it.indoor.local.beacon.model.BeaconManagerConfig;
import pro.i_it.indoor.model.SettingModel;

import java.util.Collection;

public class BluetoothMeasurementProvider extends MeasurementProvider {

    private static final String TAG = BluetoothMeasurementProvider.class.getSimpleName();
    private final RangeNotifier rangeNotifier = new RangeNotifier() {
        @Override
        public void didRangeBeaconsInRegion(Collection<Beacon> collection, Region region) {
            if (transfer != null) {
                for (Beacon beacon : collection) {
                    final MeasurementEvent event = MeasurementEvent.createBluetooth(beacon);
                    transfer.deliver(event);
                }

            }
        }
    };
    private org.altbeacon.beacon.BeaconManager beaconManager;
    private Context context;
    private AltBeaconConfigModel configModel;
    private final BeaconConsumer beaconConsumer = new BeaconConsumer() {
        @Override
        public void onBeaconServiceConnect() {
            try {
                beaconManager.startRangingBeaconsInRegion(new Region(configModel.getBeaconRangingId(), null, null, null));
            } catch (RemoteException e) {
                e.printStackTrace();
            }
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
        public boolean bindService(Intent intent, ServiceConnection serviceConnection, int flags) {
            return context.bindService(intent, serviceConnection, flags);
        }
    };


    public BluetoothMeasurementProvider(Context context, MeasurementTransfer transfer) {
        super(transfer);
        this.context = context;
        beaconManager = org.altbeacon.beacon.BeaconManager.getInstanceForApplication(context);
        configModel = new AltBeaconConfigModel();
        updateSettings(null);
    }


    public void updateSettings(SettingModel settings) {
        beaconManager = org.altbeacon.beacon.BeaconManager.getInstanceForApplication(context);
        beaconManager.setForegroundScanPeriod(configModel.getBeaconsScanningPeriodForeground());
        beaconManager.setForegroundBetweenScanPeriod(configModel.getBeaconsScanningForegroundBeatwen());
        beaconManager.setBackgroundScanPeriod(configModel.getBeaconsScanningPeriodBackground());
        beaconManager.setBackgroundBetweenScanPeriod(configModel.getBeaconsScanningBackgroundBeatwen());
        BeaconParser parser = new BeaconParser().setBeaconLayout(configModel.getRangingBeaconsFormat());
        beaconManager.getBeaconParsers().add(parser);
    }

    @Override
    public void start() {
        beaconManager.addRangeNotifier(rangeNotifier);
        beaconManager.bind(beaconConsumer);


    }

    @Override
    public void stop() {
        beaconManager.removeRangeNotifier(rangeNotifier);
        beaconManager.unbind(beaconConsumer);
    }
}
