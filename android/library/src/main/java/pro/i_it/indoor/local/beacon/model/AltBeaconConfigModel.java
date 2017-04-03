package pro.i_it.indoor.local.beacon.model;

import org.altbeacon.beacon.Identifier;
import org.altbeacon.beacon.Region;

import java.util.UUID;

/**
 * Created by syn on 19.12.16.
 */

public class AltBeaconConfigModel {
    private String rangingBeaconsFormat = "m:2-3=0215,i:4-19,i:20-21,i:22-23,p:24-24,d:25-25";
    private String beaconRangingId ="rangingId";
    private String beaconIdentifierId = "23a01af0-232a-4518-9c0e-323fb773f5ef";
    private long beaconsScanningPeriodForeground = 1000;
    private long beaconsScanningForegroundBeatwen = 10000;
    private long beaconsScanningForegroundBeatenConcurrency = 2000;
    private long beaconsScanningPeriodBackground = 2000;
    private long beaconsScanningBackgroundBeatwen = 30000;

    public AltBeaconConfigModel() {
    }

    public AltBeaconConfigModel(String rangingBeaconsFormat, long beaconsScanningPeriodForeground, long beaconsScanningForegroundBeatwen, long beaconsScanningForegroundBeatenConcurrency, long beaconsScanningPeriodBackground, long beaconsScanningBackgroundBeatwen) {
        this.rangingBeaconsFormat = rangingBeaconsFormat;
        this.beaconsScanningPeriodForeground = beaconsScanningPeriodForeground;
        this.beaconsScanningForegroundBeatwen = beaconsScanningForegroundBeatwen;
        this.beaconsScanningForegroundBeatenConcurrency = beaconsScanningForegroundBeatenConcurrency;
        this.beaconsScanningPeriodBackground = beaconsScanningPeriodBackground;
        this.beaconsScanningBackgroundBeatwen = beaconsScanningBackgroundBeatwen;
    }

    public String getRangingBeaconsFormat() {
        return rangingBeaconsFormat;
    }

    public void setRangingBeaconsFormat(String rangingBeaconsFormat) {
        this.rangingBeaconsFormat = rangingBeaconsFormat;
    }

    public long getBeaconsScanningPeriodForeground() {
        return beaconsScanningPeriodForeground;
    }

    public void setBeaconsScanningPeriodForeground(long beaconsScanningPeriodForeground) {
        this.beaconsScanningPeriodForeground = beaconsScanningPeriodForeground;
    }

    public long getBeaconsScanningForegroundBeatwen() {
        return beaconsScanningForegroundBeatwen;
    }

    public void setBeaconsScanningForegroundBeatwen(long beaconsScanningForegroundBeatwen) {
        this.beaconsScanningForegroundBeatwen = beaconsScanningForegroundBeatwen;
    }

    public long getBeaconsScanningForegroundBeatenConcurrency() {
        return beaconsScanningForegroundBeatenConcurrency;
    }

    public void setBeaconsScanningForegroundBeatenConcurrency(long beaconsScanningForegroundBeatenConcurrency) {
        this.beaconsScanningForegroundBeatenConcurrency = beaconsScanningForegroundBeatenConcurrency;
    }

    public long getBeaconsScanningPeriodBackground() {
        return beaconsScanningPeriodBackground;
    }

    public void setBeaconsScanningPeriodBackground(long beaconsScanningPeriodBackground) {
        this.beaconsScanningPeriodBackground = beaconsScanningPeriodBackground;
    }

    public long getBeaconsScanningBackgroundBeatwen() {
        return beaconsScanningBackgroundBeatwen;
    }

    public void setBeaconsScanningBackgroundBeatwen(long beaconsScanningBackgroundBeatwen) {
        this.beaconsScanningBackgroundBeatwen = beaconsScanningBackgroundBeatwen;
    }

    public String getBeaconRangingId() {
        return beaconRangingId;
    }

    public void setBeaconRangingId(String beaconRangingId) {
        this.beaconRangingId = beaconRangingId;
    }

    public Identifier getBeaconIdentifierId() {
        return Identifier.parse(beaconIdentifierId);
    }

    public void setBeaconIdentifierId(String beaconIdentifierId) {
        this.beaconIdentifierId = beaconIdentifierId;
    }

    public Region getRegion(){
       return new Region(getBeaconRangingId(), getBeaconIdentifierId(), null, null);
    }

    public long getForegroundScanPeriod() {
        return 420;
    }

    public long getForegroundBetweenScanPeriod() {
        return 0;
    }

    public long getBackgroundScanPeriod() {
        return 1000;
    }

    public long getBackgroundBetweenScanPeriod() {
        return 0;
    }
}
