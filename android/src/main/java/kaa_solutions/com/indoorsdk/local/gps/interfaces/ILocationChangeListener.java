package kaa_solutions.com.indoorsdk.local.gps.interfaces;

import kaa_solutions.com.indoorsdk.local.gps.model.Position;

/**
 * Created by syn on 12.02.17.
 */

public interface ILocationChangeListener {
    void locationUpdate(Position position);
}
