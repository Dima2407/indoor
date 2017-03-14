package pro.i_it.indoor.providers;

public abstract class MeasurementProvider {

    protected final MeasurementTransfer transfer;

    protected MeasurementProvider(MeasurementTransfer transfer) {
        this.transfer = transfer;
    }

    public abstract void start();

    public abstract void stop();
}
