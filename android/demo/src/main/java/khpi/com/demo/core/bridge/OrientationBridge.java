package khpi.com.demo.core.bridge;

public interface OrientationBridge {
    void startOrientationTracking(DeviceOrientationListener listener);

    void stopOrientationTracking(final DeviceOrientationListener deviceOrientationListener);

    interface DeviceOrientationListener {
        void onOrientationUpdated(float azimuth, float pitch, float roll);
    }
}
