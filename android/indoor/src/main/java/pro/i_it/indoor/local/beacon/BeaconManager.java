package pro.i_it.indoor.local.beacon;

import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.RemoteException;
import android.util.Log;

import org.altbeacon.beacon.Beacon;
import org.altbeacon.beacon.BeaconConsumer;
import org.altbeacon.beacon.BeaconParser;
import org.altbeacon.beacon.RangeNotifier;
import org.altbeacon.beacon.Region;

import java.util.Collection;

import pro.i_it.indoor.local.beacon.interfaces.OnBeaconListener;
import pro.i_it.indoor.local.beacon.model.AltBeaconConfigModel;
import pro.i_it.indoor.local.beacon.model.BeaconManagerConfig;
import pro.i_it.indoor.local.interfaces.BaseSetting;
import pro.i_it.indoor.model.SettingModel;

import static pro.i_it.indoor.config.DebugConfig.BEACON_IS_DEBUG;
import static pro.i_it.indoor.config.DebugConfig.IS_DEBUG;
import static pro.i_it.indoor.model.SettingsType.BEACON;

/**
 * Created by syn on 09.02.17.
 */

public class BeaconManager implements BaseSetting, BeaconConsumer, RangeNotifier {
    private static final String TAG = BeaconManager.class.getSimpleName();
    private BeaconManagerConfig settings;
    private org.altbeacon.beacon.BeaconManager beaconManager;
    private Context context;
    private AltBeaconConfigModel configModel;
    private OnBeaconListener listener;


    public BeaconManager(Context context) {
        this.context = context;
        beaconManager = org.altbeacon.beacon.BeaconManager.getInstanceForApplication(context);
        configModel = new AltBeaconConfigModel();
    }

    @Override
    public void updateSettings(SettingModel settings) {
        if (!(settings instanceof BeaconManagerConfig)) {
            return;
        }
        this.settings = (BeaconManagerConfig) settings;
        beaconManager = org.altbeacon.beacon.BeaconManager.getInstanceForApplication(context);
        beaconManager.setForegroundScanPeriod(configModel.getBeaconsScanningPeriodForeground());
        beaconManager.setForegroundBetweenScanPeriod(configModel.getBeaconsScanningForegroundBeatwen());
        beaconManager.setBackgroundScanPeriod(configModel.getBeaconsScanningPeriodBackground());
        beaconManager.setBackgroundBetweenScanPeriod(configModel.getBeaconsScanningBackgroundBeatwen());
        BeaconParser parser = new BeaconParser().setBeaconLayout(configModel.getRangingBeaconsFormat());
        beaconManager.getBeaconParsers().add(parser);
    }

    @Override
    public void setEnable(boolean isEnable) {
        if (isEnable) {

            Log.i(TAG, "initAltBeaconManager: ");
            beaconManager.addRangeNotifier(this);
            beaconManager.bind(this);

        } else {
            beaconManager.unbind(this);
        }
    }

    @Override
    public int getSettingType() {
        return BEACON;
    }

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

    @Override
    public void didRangeBeaconsInRegion(Collection<Beacon> collection, Region region) {
        if (listener != null) {
            listener.beaconUpdate(collection);
        }

        if (IS_DEBUG && BEACON_IS_DEBUG) {
            for (Beacon beacon : collection) {
                Log.d(TAG, "didRangeBeaconsInRegion: " + beacon.toString());
            }
        }
    }

    public void setOnBeaconListener(OnBeaconListener onBeaconListener) {
        this.listener = onBeaconListener;
    }
}
