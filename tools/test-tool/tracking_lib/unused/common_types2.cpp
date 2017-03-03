//
// Created by  Oleksiy Grechnyev on 3/1/2017.
//

std::vector<double> getRssiVectorFromMeasurements(const BeaconMeasurementsContainer &mc) {
    std::vector<double> rssi(mc.size());
    std::vector<double>::iterator rit = rssi.begin();
    for (BeaconMeasurementsContainer::const_iterator it = mc.begin(); it !=mc.end(); ++it, ++rit) {
        *rit = it->rssi;
    }
    return rssi;
}

std::vector<double> getTxVectorFromMeasurements  (const BeaconMeasurementsContainer &mc) {
    std::vector<double> tx(mc.size());
    std::vector<double>::iterator tit = tx.begin();
    for (BeaconMeasurementsContainer::const_iterator it = mc.begin(); it !=mc.end(); ++it, ++tit) {
        *tit = it->txPower;
    }
    return tx;
}

std::vector<time_t> getTimestampVectorFromMeasurements  (const BeaconMeasurementsContainer &mc) {
    std::vector<time_t> tm(mc.size());
    std::vector<time_t>::iterator tit = tm.begin();
    for (BeaconMeasurementsContainer::const_iterator it = mc.begin(); it !=mc.end(); ++it, ++tit) {
        *tit = it->timestamp;
    }
    return tm;
}
