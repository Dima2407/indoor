#include "accelerometersensor.h"
#include "amath.h"

#include <cmath>

namespace Sensors {

AccelerometerSensor::AccelerometerSensor() : _dataAssociationInterval(DEFAULT_DATA_ASSOCIATION_INTERVAL)
                                           , _lastMeasureTime(-1)
                                           , _filterWinSize(DEFAULT_FILTER_WIN_SIZE)
{
    Vector3 s;
    s.x = 0.05;
    s.y = 0.05;
    s.z = 0.05;
    setMeasureSigma(s);
}

AccelerometerSensor::~AccelerometerSensor() {

}

int AccelerometerSensor::sensorType() const {
    return SensorType::AccelerometerLinear;
}

void AccelerometerSensor::clear() {
    _measurements.clear();
    _measurements_filtered.clear();
}

void    AccelerometerSensor::setDataAssociationInterval(double dt) {
    _dataAssociationInterval = dt;
}

void AccelerometerSensor::addMeasurement(const AccMeasurement &m) {
    dropUpdated();
    _measurements.push_back(m);
    if (_measurements.size() > dataCapacity()) {
        _measurements.pop_front();
    }
    if (_lastMeasureTime < m.timestamp) {
        _lastMeasureTime = m.timestamp;
    }
    AccMeasurement fm = filter(_measurements);
    if (fm.timestamp >= 0) {
        _measurements_filtered.push_back(fm);
        if (_measurements_filtered.size() > dataCapacity()) {
            _measurements_filtered.pop_front();
        }
    }
    updateState();
}

void AccelerometerSensor::addMeasurement(double ax, double ay, double az, timestamp_t tm) {
    AccMeasurement m;
    m.values.x = ax;
    m.values.y = ay;
    m.values.z = az;
    m.timestamp = tm;
    addMeasurement(m);
}

void AccelerometerSensor::setMeasureSigma(double sx, double sy, double sz) {
    _measureSigma.x = sx;
    _measureSigma.y = sy;
    _measureSigma.z = sz;
}

void AccelerometerSensor::setMeasureSigma(const Vector3 &s) {
    setMeasureSigma(s.x, s.y, s.z);
}

Vector3 AccelerometerSensor::measureSigma() const {
    return _measureSigma;
}

Types::ObjectState AccelerometerSensor::proceedMeasurements() {
    Types::ObjectState state;
    state.setTimestamp(-1);
    AccMeasurement m;
    if (_measurements_filtered.empty()) {
        if (_measurements.empty()) {
            return state;
        } else {
            m = *_measurements.rbegin();
        }
    } else {
        m = *_measurements_filtered.rbegin();
    }
    state.setAcceleration(m.values);
    state.setTimestamp(m.timestamp);
    state.setCovarMatrix(measureCovarMatrix(state, Types::ObjectState()));
    Types::ObjectState lstate = referenceState();
    if (lstate.valid()) {
        double dt = double(m.timestamp - lstate.timestamp()) * CommonConstants::time_multiplicator;
        state.setVelocity(lstate.velocity() + dt * lstate.acceleration());
        state.setPosition(lstate.position() + dt * lstate.velocity() + (dt*dt / 2.0) * lstate.acceleration());
        state.setCovarMatrix(measureCovarMatrix(state, lstate));
    }
    return state;
}

AccMeasurement AccelerometerSensor::filter(const AccelerationMeasurementsContainer &mc) {
    AccMeasurement m;
    m.timestamp = -1;
    if (!mc.empty()) {
        m = *mc.rbegin();
    }
    return m;
}

Types::ObjectState::StateVec AccelerometerSensor::defaultMeasurementNoise() const {
    Types::ObjectState::StateVec vec;
    vec(0) = 100.0; vec(1) = 100.0;
    vec(2) = 30.0; vec(3) = 30.0;
    vec(4) = 0.02; vec(5) = 0.02;
    vec(6) = 10.0; vec(7) = 10.0;
    return vec;
}

Types::ObjectState::CovarMatrix AccelerometerSensor::measureCovarMatrix( const Types::ObjectState &measurement
                                                                       , const Types::ObjectState &prevState) const {
    Types::ObjectState::CovarMatrix m = Types::ObjectState::CovarMatrix::Identity() * CommonConstants::big_value<double>();
    if (!measurement.valid()) {
        return m;
    }

    Types::ObjectState  currState = measurement;
    if (currState.valid()) {
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

            if (dt > 0) {
                m(Types::ObjectState::X,  Types::ObjectState::X)  = std::min(std::pow(sX + sVx*dt + sAx * dt2 / 2.0, 2.0), CommonConstants::big_value<double>());
//                m(Types::ObjectState::X,  Types::ObjectState::Vx) = std::min(dt * std::pow(sVx + sAx*dt, 2.0), CommonConstants::big_value<double>());
//                m(Types::ObjectState::Vx, Types::ObjectState::X)  = std::min(dt * std::pow(sVx + sAx*dt, 2.0), CommonConstants::big_value<double>());
                m(Types::ObjectState::Vx, Types::ObjectState::Vx) = std::min(std::pow(sVx + sAx*dt, 2.0), CommonConstants::big_value<double>());
//                m(Types::ObjectState::Vx, Types::ObjectState::Ax) = std::min(dt * std::pow(sAx, 2.0), CommonConstants::big_value<double>());
//                m(Types::ObjectState::Ax, Types::ObjectState::Vx) = std::min(dt * std::pow(sAx, 2.0), CommonConstants::big_value<double>());

                m(Types::ObjectState::Y,  Types::ObjectState::Y)  = std::min(std::pow(sY + sVy*dt + sAy * dt2 / 2.0, 2.0), CommonConstants::big_value<double>());
//                m(Types::ObjectState::Y,  Types::ObjectState::Vy) = std::min(dt * std::pow(sVy + sAy*dt, 2.0), CommonConstants::big_value<double>());
//                m(Types::ObjectState::Vy, Types::ObjectState::Y)  = std::min(dt * std::pow(sVy + sAy*dt, 2.0), CommonConstants::big_value<double>());
                m(Types::ObjectState::Vy, Types::ObjectState::Vy) = std::min(std::pow(sVy + sAy*dt, 2.0), CommonConstants::big_value<double>());
//                m(Types::ObjectState::Vy, Types::ObjectState::Ay) = std::min(dt * std::pow(sAy, 2.0), CommonConstants::big_value<double>());
//                m(Types::ObjectState::Ay, Types::ObjectState::Vy) = std::min(dt * std::pow(sAy, 2.0), CommonConstants::big_value<double>());
            } else {
                m = prevState.covarMatrix();
            }
        }
        m(Types::ObjectState::Ax, Types::ObjectState::Ax) = std::pow(_measureSigma.x, 2.0);
        m(Types::ObjectState::Ay, Types::ObjectState::Ay) = std::pow(_measureSigma.x, 2.0);
    }
    return m;
}

} // namespace Sensors

