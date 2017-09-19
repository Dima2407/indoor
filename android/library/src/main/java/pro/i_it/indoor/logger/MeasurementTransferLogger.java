package pro.i_it.indoor.logger;


import pro.i_it.indoor.events.MeasurementEvent;

public interface MeasurementTransferLogger {
    void log(MeasurementEvent event, double[] position);
}
