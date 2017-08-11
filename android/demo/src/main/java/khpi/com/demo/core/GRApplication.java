package khpi.com.demo.core;

import android.app.ActivityManager;
import android.app.Application;
import android.content.Context;
import android.os.SystemClock;
import android.util.Log;

import java.io.File;
import java.util.Arrays;

import khpi.com.demo.BuildConfig;
import khpi.com.demo.core.bridge.DbBridge;
import khpi.com.demo.core.bridge.NetBridge;
import khpi.com.demo.core.bridge.OrientationBridge;
import khpi.com.demo.db.DbFacade;
import khpi.com.demo.net.MapCacheHelper;
import khpi.com.demo.net.NetFacade;
import khpi.com.demo.orientation.OrientationFacade;
import khpi.com.demo.routing.RouteHelper;

import khpi.com.demo.utils.FileUtil;
import pro.i_it.indoor.IndoorLocationManager;
import pro.i_it.indoor.events.MeasurementType;

public final class GRApplication extends Application {

    private static final String TAG = GRApplication.class.getSimpleName();
    private DbBridge dbBridge;
    private NetBridge netBridge;
    private OrientationBridge orientationBridge;
    private SharedHelper sharedHelper;
    private RouteHelper routeHelper;
    private MapCacheHelper mapCacheHelper;
    private IndoorLocationManager localManager;

    @Override
    public void onCreate() {
        super.onCreate();

        clearApplicationData();



        routeHelper = new RouteHelper();
        sharedHelper = new SharedHelper(this);

        dbBridge = new DbFacade(this);

        if (!sharedHelper.containsProductionFlag()) {
            sharedHelper.setUseProduction(false);
        }

        netBridge = new NetFacade(dbBridge, sharedHelper.useProduction() ? BuildConfig.PRODUCTION_SERVER_URL : BuildConfig.DEVELOPER_SERVER_URL);
        orientationBridge = new OrientationFacade(this);
        getNetBridge().logIn(BuildConfig.USERNAME, BuildConfig.PASSWORD);
        mapCacheHelper = new MapCacheHelper(this,sharedHelper.useProduction() ? BuildConfig.PRODUCTION_SERVER_URL : BuildConfig.DEVELOPER_SERVER_URL);
        localManager = new IndoorLocationManager();
    }
    private void clearApplicationData() {
        File cacheDirectory = getCacheDir();
        File applicationDirectory = new File(cacheDirectory.getParent());
        if (applicationDirectory.exists()) {
            String[] fileNames = applicationDirectory.list();
            for (String fileName : fileNames) {
                if (!fileName.equals("lib")) {
                    if (fileName.contains("shared_prefs"))
                        continue;
                    Log.i("AppliocGRA", "filename = " + fileName);
                    FileUtil.deleteFile(new File(applicationDirectory, fileName));
                }
            }
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

    public MapCacheHelper getMapCacheHelper() {
        return mapCacheHelper;
    }
}
