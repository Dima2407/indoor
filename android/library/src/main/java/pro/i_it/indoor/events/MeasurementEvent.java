package pro.i_it.indoor.events;

import android.net.wifi.ScanResult;
import org.altbeacon.beacon.Beacon;

import java.util.Arrays;

public class MeasurementEvent {

    private final MeasurementType type;
    private final long timestamp;
    private final double[] data;

    private MeasurementEvent(MeasurementType type, double... data) {
        this.type = type;
        this.timestamp = System.currentTimeMillis();
        this.data = data;
    }

    public static MeasurementEvent createGPS(double latitude, double longitude) {
        return new MeasurementEvent(MeasurementType.GEO_VALUE, latitude, longitude);
    }

    public static MeasurementEvent createBluetooth(Beacon beacon) {
        return new MeasurementEvent(MeasurementType.BLUETOOTH_VALUE,
                beacon.getId1().toUuid().hashCode(),
                beacon.getId2().toInt(),
                beacon.getId3().toInt(),
                beacon.getTxPower(),
                beacon.getRssi());
    }

    public static MeasurementEvent createWiFi(ScanResult wifi) {
        return new MeasurementEvent(MeasurementType.WIFI_VALUE,
                wifi.SSID.hashCode(),
                wifi.level);
    }

    @Override
    public String toString() {
        return type + " event at " + timestamp + " - " + Arrays.toString(data);
    }
}
