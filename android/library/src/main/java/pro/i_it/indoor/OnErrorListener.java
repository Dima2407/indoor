package pro.i_it.indoor;

import pro.i_it.indoor.errors.AvailabilityException;

public interface OnErrorListener {
    void onError(AvailabilityException e);
}
