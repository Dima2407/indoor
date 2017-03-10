package pro.i_it.indoor.local.beacon.model;

/**
 * Created by syn on 19.12.16.
 */

public class AltBeaconConfigModel {
    private String rangingBeaconsFormat = "m:2-3=0215,i:4-19,i:20-21,i:22-23,p:24-24,d:25-25";
    private String beaconRangingId = "rangingId";
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
}
