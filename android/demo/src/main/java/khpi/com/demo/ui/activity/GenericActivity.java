package khpi.com.demo.ui.activity;

import android.os.Bundle;
import android.support.annotation.Nullable;
import android.support.v7.app.AppCompatActivity;

import khpi.com.demo.core.GRApplication;
import khpi.com.demo.core.bridge.ActivityBridge;
import khpi.com.demo.core.bridge.DbBridge;
import khpi.com.demo.core.bridge.NetBridge;
import khpi.com.demo.core.bridge.OrientationBridge;
import khpi.com.demo.routing.RouteHelper;
import khpi.com.demo.ui.BottomSheet;
import khpi.com.demo.ui.launcher.Launcher;

public abstract class GenericActivity extends AppCompatActivity implements ActivityBridge {

    private GRApplication application;
    private NetBridge netBridge;
    private DbBridge dbBridge;
    private OrientationBridge orientationBridge;
    private RouteHelper routeHelper;

    private Launcher launcher;

    @Override
    protected void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        application = (GRApplication) getApplication();
        netBridge = application.getNetBridge();
        dbBridge = application.getDbBridge();
        orientationBridge = application.getOrientationBridge();
        routeHelper = application.getRouteHelper();
        launcher = new Launcher(getSupportFragmentManager());
    }

    public Launcher getLauncher() {
        return launcher;
    }

    @Override
    public GRApplication getProjectApplication() {
        return application;
    }

    @Override
    public NetBridge getNetBridge() {
        return netBridge;
    }

    @Override
    public DbBridge getDbBridge() {
        return dbBridge;
    }

    @Override
    public OrientationBridge getOrientationBridge() {
        return orientationBridge;
    }

    @Override
    public BottomSheet getBottomSheet() {
        return null;
    }

    @Override
    public RouteHelper getRouteHelper() {
        return routeHelper;
    }
}
