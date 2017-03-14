package pro.i_it.indoor.providers;

import pro.i_it.indoor.events.MeasurementEvent;

public class AndroidMeasurementTransfer implements MeasurementTransfer {
    @Override
    public native void deliver(MeasurementEvent event);
}
