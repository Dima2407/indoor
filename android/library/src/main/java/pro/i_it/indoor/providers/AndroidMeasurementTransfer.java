package pro.i_it.indoor.providers;

import android.os.Handler;
import android.os.Looper;

import pro.i_it.indoor.events.MeasurementEvent;


public final class AndroidMeasurementTransfer implements MeasurementTransfer {
    private final Handler handler;

    public AndroidMeasurementTransfer(Looper looper) {
        handler = new Handler(looper);
    }

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
