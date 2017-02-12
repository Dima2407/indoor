package kaa_solutions.com.indoorsdk.local.gps.interfaces;

import kaa_solutions.com.indoorsdk.local.interfaces.IBaseSetting;

/**
 * Created by syn on 12.02.17.
 */

public interface IGPSManager extends IBaseSetting{
      void setPositionListener(ILocationChangeListener listener);

}
