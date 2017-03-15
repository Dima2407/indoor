package khpi.com.demo.utils;


import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.util.SparseArray;

public abstract class SensorEventListenerWrapper implements SensorEventListener {

    private int frameSizeA, frameSizeM;
    private SparseArray<Value> values;

    public SensorEventListenerWrapper(int frameSizeA, int frameSizeM) {
        this.frameSizeA = frameSizeA;
        this.frameSizeM = frameSizeM;

        values = new SparseArray<>();
    }

    @Override
    public void onSensorChanged(SensorEvent event) {
        if (values.indexOfKey(event.sensor.getType()) < 0) {
            initializeValuesByEventType(event);
        }

        float[] data = values.get(event.sensor.getType()).onEvent(event);
        onSensorChanged(event.sensor, data, event.timestamp);
    }

    private void initializeValuesByEventType(SensorEvent event) {
        switch (event.sensor.getType()) {
            case Sensor.TYPE_ACCELEROMETER:
                values.put(Sensor.TYPE_ACCELEROMETER, new Value(frameSizeA));
                break;
            case Sensor.TYPE_MAGNETIC_FIELD:
                values.put(Sensor.TYPE_MAGNETIC_FIELD, new Value(frameSizeM));
                break;
        }
    }

    public abstract void onSensorChanged(Sensor sensor, float[] data, long timestamp);

    private class Value {
        private int frameSize;

        private float[][] data;
        private boolean initialized;
        private int position;
        private int size;

        Value(int frameSize) {
            this.frameSize = frameSize;
        }

        float[] onEvent(SensorEvent event) {
            if (!initialized) {
                size = event.values.length;
                data = new float[frameSize][size];
                position = 0;
                initialized = true;
            }

            System.arraycopy(event.values, 0, data[position % frameSize], 0, event.values.length);
            position++;
            if (isReady()) {
                return getValues();
            }
            return event.values;
        }

        boolean isReady() {
            return position >= frameSize;
        }

        float[] getValues() {
            float[] result = new float[size];
            for (float[] f : data) {
                for (int i = 0; i < f.length; i++) {
                    result[i] += f[i];
                }
            }
            for (int i = 0; i < result.length; i++) {
                result[i] = result[i] / frameSize;
            }
            return result;
        }

    }
}
