package pro.i_it.indoor.local.wifi.interfaces;

import android.net.wifi.ScanResult;

import java.util.List;

/**
 * Created by syn on 12.02.17.
 */

public interface WifiScanResultListener {
    void scanResult(List<ScanResult> results);
}
