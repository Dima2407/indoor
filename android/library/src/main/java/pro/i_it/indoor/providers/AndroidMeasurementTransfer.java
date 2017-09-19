package pro.i_it.indoor.providers;

import android.os.Handler;
import android.os.Looper;

import pro.i_it.indoor.events.MeasurementEvent;
import pro.i_it.indoor.logger.AndroidLoggableMeasurementTransfer;


public final class AndroidMeasurementTransfer implements MeasurementTransfer {
    private final Handler handler;
    private AndroidLoggableMeasurementTransfer transfer;

    public AndroidMeasurementTransfer(Looper looper) {
        this.handler = new Handler(looper);
    }

    public void setTransfer(AndroidLoggableMeasurementTransfer transfer) {
        this.transfer = transfer;
    }

    public void deliver(final MeasurementEvent event){
        handler.post(new Runnable() {
            @Override
            public void run() {
                double[] position = nativeDeliver(event);
                if(transfer != null){
                    transfer.log(event, position);
                }
            }
        });
    }

    private native double[] nativeDeliver(MeasurementEvent event);
}
