package pro.i_it.indoor.events;

public enum MeasurementType {
    GEO_VALUE("gps"),
    SENSOR_VALUE("sensor"),
    BLUETOOTH_VALUE("beacon"),
    WIFI_VALUE("wifi");

    private final String description;

    MeasurementType(String description) {

        this.description = description;
    }

    @Override
    public String toString() {
        return description;
    }
}
