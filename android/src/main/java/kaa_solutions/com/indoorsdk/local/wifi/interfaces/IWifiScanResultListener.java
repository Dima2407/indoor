package kaa_solutions.com.indoorsdk.local.wifi.interfaces;

import android.net.wifi.ScanResult;

import java.util.List;

/**
 * Created by syn on 12.02.17.
 */

public interface IWifiScanResultListener {
    void scanResult(List<ScanResult> results);
}
