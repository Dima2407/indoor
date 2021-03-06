#include "beacon.h"
#include "imath.h"
#include "bmath.h"

#ifdef ASTUDIO
#   include <android/log.h>
#endif

namespace Sensors {
namespace Hardware {

const double Beacon::DEFAULT_DAMP = 4.0;
const int Beacon::DEFAULT_DATA_CAPACITY   = 2048;
const int Beacon::DEFAULT_FILTER_WIN_SIZE = 10;

Beacon::Beacon(hash_t hash, double damp, double tx_power) : _maxDataCapacity(DEFAULT_DATA_CAPACITY)
                                         , _filterWinSize(DEFAULT_FILTER_WIN_SIZE)
                                         , _hash(hash), _damp(damp), _txPower(tx_power)
                                         , _useTxPowerFromMeasurements(true) {
}

const Point&    Beacon::position() const {
    return _position;
}

hash_t  Beacon::hash() const {
    return _hash;
}

double Beacon::damp() const {
    return _damp;
}

double Beacon::txPower() const {
    return _txPower;
}

void Beacon::setDamp(double damp) {
    _damp = damp;
}

void Beacon::setTxPower(double tx_power) {
    _txPower = tx_power;
}

void Beacon::setUseTxPowerFromMeasurements(bool s, double txPower) {
    if (txPower < 0) {
        _txPower = txPower;
    }
    if (s && _txPower < 0) {
        _useTxPowerFromMeasurements = true;
    } else {
        _useTxPowerFromMeasurements = false;
    }
}

bool Beacon::useTxPowerFromMeasurements() const {
    return _useTxPowerFromMeasurements;
}

void Beacon::setPosition(const Point &position) {
    _position = position;
}

void Beacon::setHash(hash_t hash) {
    _hash = hash;
}

void Beacon::clear() {
    _measurements.clear();
}

void  Beacon::addMeasurement(const BeaconMeasurement &m) {
#ifdef DEBUG_MODE
#ifdef ASTUDIO
    __android_log_print(ANDROID_LOG_ERROR, "BridgeLOG", "Measurement (%f), time: %f", (double)m.hash, (double)m.timestamp);
#endif
#endif
    _measurements.push_back(m);
    if ((_maxDataCapacity > 0) && (_measurements.size() > _maxDataCapacity)) {
        _measurements.pop_front();
    }
    BeaconMeasurement mf = filter(_measurements); // needs to smooth (tx-rssi) to supress noise
#ifdef DEBUG_MODE
#ifdef ASTUDIO
    __android_log_print(ANDROID_LOG_ERROR, "BridgeLOG", "Smooth (%f), time: %f", (double)mf.hash, (double)mf.timestamp);
#endif
#endif
    if (mf.timestamp >= 0) {
        _filtered_measurements.push_back(mf);
        if ((_maxDataCapacity > 0) && (_filtered_measurements.size() > _maxDataCapacity)) {
            _filtered_measurements.pop_front();
        }
    }
}

void  Beacon::addMeasurement(double tx_power, double rssi, timestamp_t timestamp) {
    BeaconMeasurement m;
    m.hash = hash();
    m.txPower = tx_power;
    m.rssi = rssi;
    m.timestamp = timestamp;
    addMeasurement(m);
}

BeaconMeasurementsContainer Beacon::history(size_t count) const {
    if (count == 0) {
        return _measurements;
    }
    return last_elements(_measurements, count);
}

BeaconMeasurement Beacon::measurement(size_t i) const {
    BeaconMeasurement m;
    m.timestamp = -1;
    if (i < _measurements.size()) {
        BeaconMeasurementsContainer::const_iterator it = _measurements.begin();
        std::advance(it, i);
        m = *it;
    }
    return m;
}

BeaconMeasurement Beacon::rmeasurement(size_t i) const {
    BeaconMeasurement m;
    m.timestamp = -1;
    if (i < _measurements.size()) {
        BeaconMeasurementsContainer::const_reverse_iterator it = _measurements.rbegin();
        std::advance(it, i);
        m = *it;
    }
#ifdef DEBUG_MODE
#ifdef ASTUDIO
    __android_log_print(ANDROID_LOG_ERROR, "BridgeLOG", "Returning Measurement %ld (%f), time: %f", i, (double)m.hash, (double)m.timestamp);
#endif
#endif
    return m;
}

BeaconMeasurement Beacon::measurement_filtered(size_t i) const {
    BeaconMeasurement m;
    m.timestamp = -1;
    if (i < _filtered_measurements.size()) {
        BeaconMeasurementsContainer::const_iterator it = _filtered_measurements.begin();
        std::advance(it, i);
        m = *it;
    }
    return m;
}

BeaconMeasurement Beacon::rmeasurement_filtered(size_t i) const {
    BeaconMeasurement m;
    m.timestamp = -1;
    if (i < _filtered_measurements.size()) {
        BeaconMeasurementsContainer::const_reverse_iterator it = _filtered_measurements.rbegin();
        std::advance(it, i);
        m = *it;
    }
    return m;
}

BeaconMeasurement Beacon::estimation(timestamp_t time) const {
    /**
      * 1) find nearest rssi measurements (at least two) that satisfy abs(rssi.timestamp - time) < interpolation_window
      * 2) computes linear interpolation to time 'time' if
      *
      **/
    BeaconMeasurement b = BMath::inxtrapolate(_filtered_measurements, time);
    return b;
}

bool Beacon::calibrate(const Beacon::CalibrationDataContainer &c) {
    if (c.size() < 2) {
        return false;
    }
    std::vector<double> x(c.size(), 0);
    std::vector<double> y(c.size(), 0);
    std::vector<double>::iterator xit = x.begin();
    std::vector<double>::iterator yit = y.begin();
    for (CalibrationDataContainer::const_iterator cit = c.begin(); cit != c.end(); ++cit) {
        *xit++ = -10 * std::log10(cit->distance);
        *yit++ = cit->rssi;
    }
    /*
     * damp     = cov(x,y) / cov(x,x);
     * tx_power = mean(y) - damp * mean(x)
     * Maybe, do to nonlinearity of x, there is need to use weighted samples?
    */
    double damp = this->damp();
    double tx_power = this->txPower();
    if (useTxPowerFromMeasurements()) {
        double s = x.size();
        double c_xx = Math::cov(x, x);
        if (c_xx <=  0) { // prevent division by zero and negative standard deviation (which means some error is presented)
            return false;
        }
        damp     = Math::cov(x, y) / c_xx;
        tx_power = (Math::sum(y) - damp * Math::sum(x)) / s;
    } else { // use predefined txPower
        std::vector<double> xy(x.size());
        std::vector<double> xx(x.size());
        std::transform(x.begin(), x.end(), y.begin(), xy.begin(), Math::Multiplicator());
        std::transform(x.begin(), x.end(), x.begin(), xx.begin(), Math::Multiplicator());
        double c_xx = Math::sum(xx);
        if (c_xx == 0) {  // prevent division by zero and negative standard deviation (which means some error is presented)
            return false;
        }
        damp = (Math::sum(xy) - tx_power * Math::sum(x)) / c_xx;
    }
    this->setDamp(damp);
    this->setTxPower(tx_power);
    return true;
}

size_t Beacon::dataCapacity() const {
    return _maxDataCapacity;
}

void Beacon::setDataCapacity(size_t c) {
    _maxDataCapacity = c;
    long int ds = _maxDataCapacity - _measurements.size();
    if (_maxDataCapacity > 0 && ds < 0) {
        BeaconMeasurementsContainer tmp(_maxDataCapacity);
        std::copy_n(_measurements.rbegin(), _maxDataCapacity, tmp.rbegin());
        _measurements = tmp;
    }
}

size_t Beacon::dataCount() const {
    return _measurements.size();
}

size_t Beacon::dataCountF() const {
    return _filtered_measurements.size();
}

size_t Beacon::filterWinSize() {
    return _filterWinSize;
}

void Beacon::setFilterWinSize(size_t ws) {
    _filterWinSize = ws;
}

bool Beacon::valid() const {
    return (_hash >= 0);
}

BeaconMeasurement Beacon::filter(const BeaconMeasurementsContainer &mc) {
    BeaconMeasurement m;
    m.timestamp = -1;
    if (!mc.empty()) {
        size_t win_size = std::min(_filterWinSize, mc.size());
        if (win_size == 0) {
            win_size = mc.size();
        }
        BeaconMeasurementsContainer win_data = last_elements(mc, win_size);
        std::vector<double> d_power(win_data.size(), 0.0);
        std::vector<double> d_time(win_data.size(), 0.0);
        BeaconMeasurementsContainer::const_iterator dit = win_data.begin();
        std::vector<double>::iterator pit = d_power.begin();
        std::vector<double>::iterator tit = d_time.begin();
        for (; dit != win_data.end(); ++dit, ++pit, ++tit) {
            *pit = dit->txPower-dit->rssi;
            *tit = dit->timestamp;
        }
        m.hash    = mc.rbegin()->hash;
        m.txPower = mc.rbegin()->txPower;
        m.rssi    = m.txPower - Math::mean(d_power);
        m.timestamp = (timestamp_t)(Math::mean(d_time));
    }
    return m;
}

} // namespace Hardware
} // namespace Sensors
