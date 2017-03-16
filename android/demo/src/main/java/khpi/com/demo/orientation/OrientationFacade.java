package khpi.com.demo.orientation;

import android.content.Context;

import khpi.com.demo.core.bridge.OrientationBridge;

public final class OrientationFacade implements OrientationBridge {

    private final OrientationManager orientationManager;

    public OrientationFacade(Context context) {
        orientationManager = new OrientationManager(context);
    }

    @Override
    public void startOrientationTracking(DeviceOrientationListener listener) {
        orientationManager.startTracking(listener);
    }

    @Override
    public void stopOrientationTracking(final DeviceOrientationListener deviceOrientationListener) {
        orientationManager.stopTracking(deviceOrientationListener);
    }
}
