#include "beaconsensor.h"

#include "bmath.h"
#include "imath.h"

#include "defines.h"

namespace Sensors {

const double BeaconSensor::DEFAULT_DATA_ASSOCIATION_INTERVAL = 100; // msec

BeaconSensor::BeaconSensor() : AbstractSensor()
                             , _dataAssociationInterval(DEFAULT_DATA_ASSOCIATION_INTERVAL)
                             , _lastMeasureTime(-1)
{
    Vector3 s;
    s.x = 3;
    s.y = 3;
    s.z = 3;
    setMeasureSigma(s);
}

BeaconSensor::~BeaconSensor() {

}

int BeaconSensor::sensorType() const {
    return SensorType::Beacon;
}

void BeaconSensor::clear() {
    _beacons.clear();
}

void    BeaconSensor::addBeacon(const Hardware::Beacon &b) {
    _beacons[b.hash()] = b;
}

bool BeaconSensor::calibrateBeacon(hash_t hash, const Hardware::Beacon::CalibrationDataContainer &data) {
    if (hasBeacon(hash)) {
        return _beacons[hash].calibrate(data);
    }
    return false;
}

void    BeaconSensor::setDataAssociationInterval(double dt) {
    _dataAssociationInterval = dt;
}

void BeaconSensor::addMeasurement(const BeaconMeasurement &m) {
    addMeasurement(m.hash, m.txPower, m.rssi, m.timestamp);
}

void BeaconSensor::addMeasurement(hash_t hash, double tx_power, double rssi, timestamp_t tm) {
    AbstractSensor::dropUpdated();
    if (_beacons.count(hash)) {
        _beacons[hash].addMeasurement(tx_power, rssi, tm);
    }
    if (_lastMeasureTime < tm) {
        _lastMeasureTime = tm;
    }
    updateState();
}

size_t  BeaconSensor::beaconsCount() {
    return _beacons.size();
}

bool BeaconSensor::hasBeacon(hash_t hash) {
    return (_beacons.count(hash) > 0);
}

Hardware::Beacon BeaconSensor::beacon(hash_t hash) {
    Hardware::Beacon b;
    if (_beacons.count(hash) > 0) {
        b = _beacons[hash];
    }
    return b;
}

void BeaconSensor::setMeasureSigma(double sx, double sy, double sz) {
    _measureSigma.x = sx;
    _measureSigma.y = sy;
    _measureSigma.z = sz;
}

void BeaconSensor::setMeasureSigma(const Vector3 &s) {
    setMeasureSigma(s.x, s.y, s.z);
}

Vector3 BeaconSensor::measureSigma() const {
    return _measureSigma;
}

double BeaconSensor::beaconDistance(hash_t hash, size_t smooth_count) {
    double dist = -1;
    if (_beacons.count(hash) > 0) {
        Sensors::Hardware::Beacon b = _beacons[hash];
        size_t count = b.dataCountF();
        if (smooth_count > 0) {
            count = std::min(smooth_count, count);
        }
        if (count > 0) {
            std::vector<double> rssi(count, 0);
            std::vector<double> tx_power(count, 0);

            size_t real_count = 0;
            for (int i = 0; i < count; ++i) {
                BeaconMeasurement m = b.rmeasurement_filtered(i);
                if (m.timestamp >= 0) {
                    tx_power[real_count] = m.txPower;
                    rssi[real_count] = m.rssi;
                    real_count++;
                }
            }
            tx_power.resize(real_count);
            rssi.resize(real_count);

            double rssi_m = Math::mean(rssi);
            double tx_power_m = Math::mean(tx_power);

            dist = BMath::get_distance(rssi_m, tx_power_m, b.damp());
        }
    } else {
#ifdef DEBUG_MODE
#ifdef ASTUDIO
      __android_log_print(ANDROID_LOG_ERROR, "BridgeLOG", "No hash %d", hash);
#endif
#endif
    }
    return dist;
}

Types::ObjectState BeaconSensor::proceedMeasurements() {
    Types::ObjectState state;
    state.setTimestamp(-1);
    if (_beacons.size() > 2) {
        PointContainer beacons_pos;
        DistancesContainer distances_to_beacons;
        double mean_time = 0;
        double tm_count  = 0;
        double last_time = 0;

        // find last added measurement timestamp
        timestamp_t max_time = std::numeric_limits<timestamp_t>::min();
        for (BeaconContainer::const_reverse_iterator rit = _beacons.rbegin(); rit != _beacons.rend(); ++rit) {
            BeaconMeasurement m = rit->second.rmeasurement_filtered(0);
            if (m.timestamp >= 0) {
                max_time = m.timestamp > max_time ? m.timestamp : max_time;
            }
        }

        for (BeaconContainer::const_reverse_iterator rit = _beacons.rbegin(); rit != _beacons.rend(); ++rit) {
//            BeaconMeasurement m = rit->second.rmeasurement_filtered(0);
            BeaconMeasurement m = rit->second.estimation(max_time);
            if (    (m.timestamp >= 0)
                 && ((m.timestamp - _lastMeasureTime) <= _dataAssociationInterval)
                 //&& (m.rssi <= m.txPower) // Cannot be nearest then 1 meter from beacon
                ) {
                beacons_pos.push_back(rit->second.position());
                double tx_power = rit->second.useTxPowerFromMeasurements() ? m.txPower : rit->second.txPower();
                distances_to_beacons.push_back(BMath::get_distance(m.rssi, tx_power, rit->second.damp()));
                mean_time += m.timestamp;
                last_time = last_time < m.timestamp ? m.timestamp : last_time;
                tm_count+=1;
            }
        }
        if (beacons_pos.size() > 2) {
            Point location;
            if (BMath::TrilatLocation2d(beacons_pos, distances_to_beacons, location)) {
                state.setPosition(location);
//                state.setTimestamp(mean_time / tm_count); // Time is set as a mean of timestamps of all beacon measurements was used
                state.setTimestamp(last_time);
                state.setCovarMatrix(measureCovarMatrix(state, Types::ObjectState()));

                Types::ObjectState lstate = rstate(0);
                if (state.timestamp() == lstate.timestamp()) {
                    lstate = rstate(1);
                }

                if (lstate.valid()) { // If we already have at least ONE valid measurement
                    double dt = (state.timestamp() - lstate.timestamp()) * CommonConstants::time_multiplicator;
                    if (dt != 0) {
                        state.setVelocity((state.position() - lstate.position()) / dt); // we can estimate velocity
                        if (dataCount() > 1) { // If we already have at least TWO valid measurement
                            state.setAcceleration((state.velocity() - lstate.velocity()) / dt);  // we can estimate acceleration also
                        }
                    }
                    state.setCovarMatrix(measureCovarMatrix(state, lstate));
                }
            }
        }
    }
    return state;
}

Types::ObjectState::StateVec BeaconSensor::defaultMeasurementNoise() const {
    Types::ObjectState::StateVec vec;
    vec(0) =  0.3; vec(1) =  2.0;
    vec(2) = 10.0; vec(3) = 10.0;
    vec(4) = 10.0; vec(5) = 10.0;
    vec(6) = 10.0; vec(7) = 10.0;
    return vec;
}

Types::ObjectState::CovarMatrix BeaconSensor::measureCovarMatrix( const Types::ObjectState &measurement
                                                                , const Types::ObjectState &prevState) const {
    Types::ObjectState::CovarMatrix m = Types::ObjectState::CovarMatrix::Identity() * CommonConstants::big_value<double>();
    return m; // NO UPDATES FOR NOW
    if (!measurement.valid()) {
        return m;
    }

    Types::ObjectState  currState = measurement;
    if (prevState.valid()) {
        Types::ObjectState::CovarMatrix pcovar = prevState.covarMatrix();
        double sX  = pcovar(Types::ObjectState::X,  Types::ObjectState::X);
        double sY  = pcovar(Types::ObjectState::Y,  Types::ObjectState::Y);
        double sVx = pcovar(Types::ObjectState::Vx, Types::ObjectState::Vx);
        double sVy = pcovar(Types::ObjectState::Vy, Types::ObjectState::Vy);
        double sAx = pcovar(Types::ObjectState::Ax, Types::ObjectState::Ax);
        double sAy = pcovar(Types::ObjectState::Ay, Types::ObjectState::Ay);

        double dt = (currState.timestamp() - prevState.timestamp()) * CommonConstants::time_multiplicator;
        double dt2 = dt*dt;

        m = prevState.covarMatrix();

        if (dt > 0) {
//            m(Types::ObjectState::X,  Types::ObjectState::Vx) = std::min(std::pow(_measureSigma.x, 2.0) / dt, CommonConstants::big_value<double>());
//            m(Types::ObjectState::Y,  Types::ObjectState::Vy) = std::min(std::pow(_measureSigma.y, 2.0) / dt, CommonConstants::big_value<double>());
//            m(Types::ObjectState::X,  Types::ObjectState::Ax) = std::min(std::pow(_measureSigma.x / dt, 2.0), CommonConstants::big_value<double>());
//            m(Types::ObjectState::Y,  Types::ObjectState::Ay) = std::min(std::pow(_measureSigma.y / dt, 2.0), CommonConstants::big_value<double>());
//            m(Types::ObjectState::Vx, Types::ObjectState::X)  = std::min(m(Types::ObjectState::X,  Types::ObjectState::Vx), CommonConstants::big_value<double>());
//            m(Types::ObjectState::Vy, Types::ObjectState::Y)  = std::min(m(Types::ObjectState::Y,  Types::ObjectState::Vy), CommonConstants::big_value<double>());
            double sVxc = std::pow((_measureSigma.x + sX) / dt, 2.0);
            double sVyc = std::pow((_measureSigma.y + sY) / dt, 2.0);
            m(Types::ObjectState::Vx, Types::ObjectState::Vx) = std::min(sVxc, CommonConstants::big_value<double>());
            m(Types::ObjectState::Vy, Types::ObjectState::Vy) = std::min(sVyc, CommonConstants::big_value<double>());
//            m(Types::ObjectState::Vx, Types::ObjectState::Ax) = std::min(std::pow(sVxc, 2.0) / dt, CommonConstants::big_value<double>());
//            m(Types::ObjectState::Vy, Types::ObjectState::Ay) = std::min(std::pow(sVyc, 2.0) / dt, CommonConstants::big_value<double>());
//            m(Types::ObjectState::Ax, Types::ObjectState::X) = std::min(m(Types::ObjectState::X, Types::ObjectState::Ax), CommonConstants::big_value<double>());
//            m(Types::ObjectState::Ay, Types::ObjectState::Y) = std::min(m(Types::ObjectState::Y, Types::ObjectState::Ay), CommonConstants::big_value<double>());
//            m(Types::ObjectState::Ax, Types::ObjectState::Vx) = std::min(m(Types::ObjectState::Vx, Types::ObjectState::Ax), CommonConstants::big_value<double>());
//            m(Types::ObjectState::Ay, Types::ObjectState::Vy) = std::min(m(Types::ObjectState::Vy, Types::ObjectState::Ay), CommonConstants::big_value<double>());
            m(Types::ObjectState::Ax, Types::ObjectState::Ax) = std::min(std::pow((sVxc - sVx) / dt, 2.0), CommonConstants::big_value<double>());
            m(Types::ObjectState::Ay, Types::ObjectState::Ay) = std::min(std::pow((sVyc - sVy) / dt, 2.0), CommonConstants::big_value<double>());
        }
    }
    m(Types::ObjectState::X, Types::ObjectState::X) = std::pow(_measureSigma.x, 2.0);
    m(Types::ObjectState::Y, Types::ObjectState::Y) = std::pow(_measureSigma.y, 2.0);
    return m;
}

} // namespace Sensors
