package pro.i_it.indoor.providers;


import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.RemoteException;
import android.util.Log;
import org.altbeacon.beacon.*;
import pro.i_it.indoor.events.MeasurementEvent;
import pro.i_it.indoor.model.SettingModel;

import java.util.Collection;

public class BluetoothMeasurementProvider extends MeasurementProvider {

    private static final String TAG = BluetoothMeasurementProvider.class.getSimpleName();
    private final RangeNotifier rangeNotifier = new RangeNotifier() {
        @Override
        public void didRangeBeaconsInRegion(Collection<Beacon> collection, Region region) {
            if (transfer != null) {
                Log.d("onLocationChanged", "number of beacons " + collection.size());
                transfer.deliver(MeasurementEvent.createBluetooth(collection));

            }
        }
    };
    private org.altbeacon.beacon.BeaconManager beaconManager;
    private MonitorNotifier monitorNotifier = new MonitorNotifier() {
        @Override
        public void didEnterRegion(Region region) {
            try {
                beaconManager.startRangingBeaconsInRegion(region);
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }

        @Override
        public void didExitRegion(Region region) {
            try {
                beaconManager.stopRangingBeaconsInRegion(region);
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }

        @Override
        public void didDetermineStateForRegion(int i, Region region) {

        }
    };
    private Context context;
    private final BeaconConsumer beaconConsumer = new BeaconConsumer() {
        @Override
        public void onBeaconServiceConnect() {
            final Region region = new Region("rangingId", Identifier.parse("23a01af0-232a-4518-9c0e-323fb773f5ef"), null, null);

            beaconManager.addMonitorNotifier(monitorNotifier);
            beaconManager.addRangeNotifier(rangeNotifier);
            Log.d("MyDebugTag", "beaconManagerMonitor" + beaconManager);
            try {
                beaconManager.startMonitoringBeaconsInRegion(region);
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
    private AltBeaconConfigModel configModel;


    public BluetoothMeasurementProvider(Context context, MeasurementTransfer transfer) {
        super(transfer);
        this.context = context;
        beaconManager = org.altbeacon.beacon.BeaconManager.getInstanceForApplication(context);
        configModel = new AltBeaconConfigModel();
        updateSettings(null);
    }


    public void updateSettings(SettingModel settings) {
        beaconManager = org.altbeacon.beacon.BeaconManager.getInstanceForApplication(context);
        beaconManager.setForegroundScanPeriod(configModel.getForegroundScanPeriod());
        beaconManager.setForegroundBetweenScanPeriod(configModel.getForegroundBetweenScanPeriod());
        beaconManager.setBackgroundScanPeriod(configModel.getBackgroundScanPeriod());
        beaconManager.setBackgroundBetweenScanPeriod(configModel.getBackgroundBetweenScanPeriod());
        BeaconParser parser = new BeaconParser().setBeaconLayout(configModel.getRangingBeaconsFormat());
        beaconManager.getBeaconParsers().add(parser);
    }

    @Override
    public void start() {
        beaconManager.bind(beaconConsumer);
    }

    @Override
    public void stop() {
        beaconManager.removeRangeNotifier(rangeNotifier);
        beaconManager.removeMonitoreNotifier(monitorNotifier);
        beaconManager.unbind(beaconConsumer);
    }

    private static class AltBeaconConfigModel {
        private String rangingBeaconsFormat = "m:2-3=0215,i:4-19,i:20-21,i:22-23,p:24-24,d:25-25";
        private String beaconRangingId = "rangingId";
        private String beaconIdentifierId = "23a01af0-232a-4518-9c0e-323fb773f5ef";
        private long beaconsScanningPeriodForeground = 1000;
        private long beaconsScanningForegroundBeatwen = 10000;
        private long beaconsScanningForegroundBeatenConcurrency = 2000;
        private long beaconsScanningPeriodBackground = 2000;
        private long beaconsScanningBackgroundBeatwen = 30000;

        public AltBeaconConfigModel() {
        }

        public AltBeaconConfigModel(String rangingBeaconsFormat, long beaconsScanningPeriodForeground, long beaconsScanningForegroundBeatwen, long beaconsScanningForegroundBeatenConcurrency, long beaconsScanningPeriodBackground, long beaconsScanningBackgroundBeatwen) {
            this.rangingBeaconsFormat = rangingBeaconsFormat;
            this.beaconsScanningPeriodForeground = beaconsScanningPeriodForeground;
            this.beaconsScanningForegroundBeatwen = beaconsScanningForegroundBeatwen;
            this.beaconsScanningForegroundBeatenConcurrency = beaconsScanningForegroundBeatenConcurrency;
            this.beaconsScanningPeriodBackground = beaconsScanningPeriodBackground;
            this.beaconsScanningBackgroundBeatwen = beaconsScanningBackgroundBeatwen;
        }

        public String getRangingBeaconsFormat() {
            return rangingBeaconsFormat;
        }

        public void setRangingBeaconsFormat(String rangingBeaconsFormat) {
            this.rangingBeaconsFormat = rangingBeaconsFormat;
        }

        public long getBeaconsScanningPeriodForeground() {
            return beaconsScanningPeriodForeground;
        }

        public void setBeaconsScanningPeriodForeground(long beaconsScanningPeriodForeground) {
            this.beaconsScanningPeriodForeground = beaconsScanningPeriodForeground;
        }

        public long getBeaconsScanningForegroundBeatwen() {
            return beaconsScanningForegroundBeatwen;
        }

        public void setBeaconsScanningForegroundBeatwen(long beaconsScanningForegroundBeatwen) {
            this.beaconsScanningForegroundBeatwen = beaconsScanningForegroundBeatwen;
        }

        public long getBeaconsScanningForegroundBeatenConcurrency() {
            return beaconsScanningForegroundBeatenConcurrency;
        }

        public void setBeaconsScanningForegroundBeatenConcurrency(long beaconsScanningForegroundBeatenConcurrency) {
            this.beaconsScanningForegroundBeatenConcurrency = beaconsScanningForegroundBeatenConcurrency;
        }

        public long getBeaconsScanningPeriodBackground() {
            return beaconsScanningPeriodBackground;
        }

        public void setBeaconsScanningPeriodBackground(long beaconsScanningPeriodBackground) {
            this.beaconsScanningPeriodBackground = beaconsScanningPeriodBackground;
        }

        public long getBeaconsScanningBackgroundBeatwen() {
            return beaconsScanningBackgroundBeatwen;
        }

        public void setBeaconsScanningBackgroundBeatwen(long beaconsScanningBackgroundBeatwen) {
            this.beaconsScanningBackgroundBeatwen = beaconsScanningBackgroundBeatwen;
        }

        public String getBeaconRangingId() {
            return beaconRangingId;
        }

        public void setBeaconRangingId(String beaconRangingId) {
            this.beaconRangingId = beaconRangingId;
        }

        public Identifier getBeaconIdentifierId() {
            return Identifier.parse(beaconIdentifierId);
        }

        public void setBeaconIdentifierId(String beaconIdentifierId) {
            this.beaconIdentifierId = beaconIdentifierId;
        }

        public Region getRegion() {
            return new Region(getBeaconRangingId(), getBeaconIdentifierId(), null, null);
        }

        public long getForegroundScanPeriod() {
            return 420;
        }

        public long getForegroundBetweenScanPeriod() {
            return 0;
        }

        public long getBackgroundScanPeriod() {
            return 1000;
        }

        public long getBackgroundBetweenScanPeriod() {
            return 0;
        }
    }

}
