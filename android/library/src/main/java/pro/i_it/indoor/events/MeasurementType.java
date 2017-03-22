package pro.i_it.indoor.events;

public enum MeasurementType {
    GEO_VALUE(0),
    SENSOR_VALUE(1),
    BLUETOOTH_VALUE(2),
    WIFI_VALUE(3);

    private final int id;

    MeasurementType(int code) {
        this.id = code;
    }

    public int getCode(){
        return id;
    }

}
