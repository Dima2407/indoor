package pro.i_it.indoor.region;

import java.util.Arrays;

public class BluetoothBeacon implements SpaceBeacon {

    private final String uuid;
    private final int major;
    private final int minor;
    private final float txPower;
    private final float dump;
    private final float[] position;
    private float[] values;

    public BluetoothBeacon(String uuid, int major, int minor,
                           float txPower,
                           float dump,
                           float x, float y, float z) {
        this.uuid = uuid;
        this.major = major;
        this.minor = minor;
        this.txPower = txPower;
        this.dump = dump;
        this.position = new float[]{x, y, z};
    }

    @Override
    public float[] getPosition() {
        return position;
    }

    @Override
    public String getId() {
        return uuid;
    }

    @Override
    public float[] getValues() {
        if (values == null) {
            values = new float[]{major, minor, txPower, dump};
        } else {
            values[0] = major;
            values[1] = minor;
            values[2] = txPower;
            values[3] = dump;
        }
        return values;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        BluetoothBeacon that = (BluetoothBeacon) o;

        if (major != that.major) return false;
        if (minor != that.minor) return false;
        return uuid.equals(that.uuid);
    }

    @Override
    public int hashCode() {
        int result = uuid.hashCode();
        result = 31 * result + major;
        result = 31 * result + minor;
        return result;
    }
}
