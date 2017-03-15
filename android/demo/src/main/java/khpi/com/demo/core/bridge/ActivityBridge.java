package khpi.com.demo.core.bridge;

import khpi.com.demo.core.GRApplication;
import khpi.com.demo.routing.RouteHelper;
import khpi.com.demo.ui.BottomSheet;
import khpi.com.demo.ui.launcher.Launcher;

public interface ActivityBridge {

    GRApplication getProjectApplication();

    NetBridge getNetBridge();

    DbBridge getDbBridge();

    OrientationBridge getOrientationBridge();

    Launcher getLauncher();

    BottomSheet getBottomSheet();

    RouteHelper getRouteHelper();
}
