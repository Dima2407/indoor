package pro.i_it.indoor.providers;

import android.os.Handler;
import pro.i_it.indoor.events.MeasurementEvent;


public final class AndroidMeasurementTransfer implements MeasurementTransfer {

    public static final MeasurementTransfer TRANSFER = new AndroidMeasurementTransfer();

    private AndroidMeasurementTransfer() {
    }

    private final Handler handler = new Handler();

    public void deliver(final MeasurementEvent event){
        handler.post(new Runnable() {
            @Override
            public void run() {
                nativeDeliver(event);
            }
        });
    }

    private native void nativeDeliver(MeasurementEvent event);
}
