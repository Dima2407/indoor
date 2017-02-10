package kaa_solutions.com.indoorsdk.local.beacon;

import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.RemoteException;
import android.util.Log;

import org.altbeacon.beacon.Beacon;
import org.altbeacon.beacon.BeaconConsumer;
import org.altbeacon.beacon.BeaconManager;
import org.altbeacon.beacon.BeaconParser;
import org.altbeacon.beacon.RangeNotifier;
import org.altbeacon.beacon.Region;

import java.util.Collection;

import kaa_solutions.com.indoorsdk.local.beacon.interfaces.IBeaconManager;
import kaa_solutions.com.indoorsdk.local.beacon.interfaces.IOnBeaconListener;
import kaa_solutions.com.indoorsdk.local.beacon.model.AltBeaconConfigModel;
import kaa_solutions.com.indoorsdk.local.beacon.model.BeaconManagerConfig;
import kaa_solutions.com.indoorsdk.ui.main.model.SettingModel;

import static kaa_solutions.com.indoorsdk.config.DebugConfig.BEACON_IS_DEBUG;
import static kaa_solutions.com.indoorsdk.config.DebugConfig.IS_DEBUG;
import static kaa_solutions.com.indoorsdk.ui.main.model.SettingsType.BEACON;

/**
 * Created by syn on 09.02.17.
 */

public class BeaconManage implements IBeaconManager, BeaconConsumer, RangeNotifier {
    private static final String TAG = BeaconManage.class.getSimpleName();
    private BeaconManagerConfig settings;
    private BeaconManager beaconManager;
    private Context context;
    private AltBeaconConfigModel configModel;
    private IOnBeaconListener listener;


    public BeaconManage(Context context) {
        this.context = context;
        beaconManager = BeaconManager.getInstanceForApplication(context);
        configModel = new AltBeaconConfigModel();
    }

    @Override
    public void updateSettings(SettingModel settings) {
        if (!(settings instanceof BeaconManagerConfig)) {
            return;
        }
        this.settings = (BeaconManagerConfig) settings;
        beaconManager = BeaconManager.getInstanceForApplication(context);
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

    @Override
    public void setOnBeaconListener(IOnBeaconListener onBeaconListener) {
        this.listener = onBeaconListener;
    }
}
