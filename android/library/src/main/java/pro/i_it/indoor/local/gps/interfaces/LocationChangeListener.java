package pro.i_it.indoor.local.gps.interfaces;

import pro.i_it.indoor.local.gps.model.Position;

/**
 * Created by syn on 12.02.17.
 */

public interface LocationChangeListener {
    void locationUpdate(Position position);
}
