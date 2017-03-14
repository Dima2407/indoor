package pro.i_it.indoor.providers;

import pro.i_it.indoor.events.MeasurementEvent;

public interface MeasurementTransfer {

    void deliver(MeasurementEvent event);
}
