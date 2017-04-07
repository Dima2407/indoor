package khpi.com.demo.core;

import android.app.Application;
import android.content.Context;
import android.os.SystemClock;
import android.util.Log;

import java.util.Arrays;

import khpi.com.demo.BuildConfig;
import khpi.com.demo.core.bridge.DbBridge;
import khpi.com.demo.core.bridge.NetBridge;
import khpi.com.demo.core.bridge.OrientationBridge;
import khpi.com.demo.db.DbFacade;
import khpi.com.demo.net.NetFacade;
import khpi.com.demo.orientation.OrientationFacade;
import khpi.com.demo.routing.RouteHelper;

import pro.i_it.indoor.IndoorLocationManager;
import pro.i_it.indoor.OnLocationUpdateListener;
import pro.i_it.indoor.dependency.LocaleManager;
import pro.i_it.indoor.events.MeasurementType;
import pro.i_it.indoor.local.data.DataManager;

import static pro.i_it.indoor.config.DebugConfig.IS_DEBUG;

public final class GRApplication extends Application {

    private static final String TAG = GRApplication.class.getSimpleName();
    private DbBridge dbBridge;
    private NetBridge netBridge;
    private OrientationBridge orientationBridge;
    private SharedHelper sharedHelper;
    private RouteHelper routeHelper;
    private IndoorLocationManager localManager;

    @Override
    public void onCreate() {
        super.onCreate();

        routeHelper = new RouteHelper();
        sharedHelper = new SharedHelper(this);

        dbBridge = new DbFacade(this);

        if (!sharedHelper.containsProductionFlag()) {
            sharedHelper.setUseProduction(false);
        }

        netBridge = new NetFacade(dbBridge, sharedHelper.useProduction() ? BuildConfig.PRODUCTION_SERVER_URL : BuildConfig.DEVELOPER_SERVER_URL);
        orientationBridge = new OrientationFacade(this);
        getNetBridge().logIn(BuildConfig.USERNAME, BuildConfig.PASSWORD);
    }

    public void init(Context context){
        if(localManager == null) {
            localManager = new IndoorLocationManager();
            localManager.addProvider(context, MeasurementType.BLUETOOTH_VALUE);
        }
    }

    public IndoorLocationManager getLocalManager(){
        return this.localManager;
    }

    public DbBridge getDbBridge() {
        return dbBridge;
    }

    public NetBridge getNetBridge() {
        return netBridge;
    }

    public OrientationBridge getOrientationBridge() {
        return orientationBridge;
    }

    public SharedHelper getSharedHelper() {
        return sharedHelper;
    }

    public RouteHelper getRouteHelper() {
        return routeHelper;
    }
}
