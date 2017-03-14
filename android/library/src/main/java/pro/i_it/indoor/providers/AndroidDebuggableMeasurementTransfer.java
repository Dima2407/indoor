package pro.i_it.indoor.providers;

import android.util.Log;
import pro.i_it.indoor.DebugConfig;
import pro.i_it.indoor.events.MeasurementEvent;

public class AndroidDebuggableMeasurementTransfer implements MeasurementTransfer {

    private final MeasurementTransfer transfer;

    public AndroidDebuggableMeasurementTransfer() {
        this.transfer = new AndroidMeasurementTransfer();
    }

    @Override
    public void deliver(MeasurementEvent event) {
        Log.d(DebugConfig.TAG, "deliver: " + event);
        Log.d(DebugConfig.TAG, "deliver: " + stringFromJNI());
        transfer.deliver(event);
    }

    public native String stringFromJNI();
}
