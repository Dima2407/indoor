#include "Navigator.h"

#ifdef DEBUG_MODE
#   ifdef ASTUDIO
#       include <android/log.h>
#   endif
#endif

SmartPtr<Navigator> Navigator::__instance = 0;

void Navigator::addBeaconMeasurement(hash_t hash, double tx_power, double rssi, timestamp_t timestamp) {
    _beacon.addMeasurement(hash, tx_power, rssi, timestamp);
    if (_beacon.updated()) {
        updateState(_beacon.lastState());
    }
}

void Navigator::addAccelerometerMeasurement(const AccMeasurement &m) {
    addAccelerometerMeasurement(m.values.x, m.values.y, m.values.z, m.timestamp);
}

void Navigator::addAccelerometerMeasurement(double ax, double ay, double az, timestamp_t timestamp) {
//    _accelerometer.addMeasurement(ax, ay, az, timestamp);
//    if (_accelerometer.updated()) { // always true
//        updateState(_accelerometer.lastState());
//    }
}

Types::ObjectState Navigator::state(size_t i) const {
    Types::ObjectState state;
    if (i < _stateHistory.size()) {
        Types::ObjectStateContainer::const_iterator it = _stateHistory.begin();
        std::advance(it, i);
        state = *it;
    }
    return state;
}

Types::ObjectState Navigator::rstate(size_t i) const {
    Types::ObjectState state;
    if (i < _stateHistory.size()) {
        Types::ObjectStateContainer::const_reverse_iterator it = _stateHistory.rbegin();
        std::advance(it, i);
        state = *it;
    }
    return state;
}

void Navigator::setDataCapacity(size_t c) {
    _maxDataCapacity = c;
    long int ds = _maxDataCapacity - _stateHistory.size();
    if (ds < 0) {
        Types::ObjectStateContainer tmp(_maxDataCapacity);
        std::copy_n(_stateHistory.rbegin(), _maxDataCapacity, tmp.rbegin());
        _stateHistory = tmp;
    }
}

void Navigator::updateState(const Types::ObjectState &measurement) {
    if (measurement.valid()) {
        Types::ObjectState lstate = lastState();
        if (!lstate.valid()) {
            addState(measurement);
        } else {
            if (measurement.timestamp() == lstate.timestamp()) {
                lstate = rstate(1);
                _stateHistory.pop_back();
            }
//            if (lstate.valid()) {
//                lstate = Math::kalman(lstate, measurement);
//            } else {
//                lstate = measurement;
//            }
            lstate = measurement;
            if (lstate.valid()) {
                addState(lstate);
                _accelerometer.setReferenceState(lstate);
                _beacon.setReferenceState(lstate);
            }
        }
    }

//    if (measurement.valid()) {
//        Types::ObjectState lstate = lastState();
//        if (!lstate.valid()) {
//            lstate = measurement;
//        } else {
//            lstate = Math::kalman(lstate, measurement);
//        }
//        if (lstate.valid()) {
//            addState(lstate);
//            _accelerometer.setReferenceState(lstate);
//            _beacon.setReferenceState(lstate);
//        }
//    }
}

void Navigator::addState(const Types::ObjectState &state) {
    if (state.valid()) {
        if (!_stateHistory.empty()) {
            if (*_stateHistory.rbegin() == state) { // new state must be different from last at least in one parameter (including timestamp)
                return;
            }
        }
        _stateHistory.push_back(state);
    }
    if (_stateHistory.size() > dataCapacity()) {
        _stateHistory.pop_front();
    }
#ifdef ASTUDIO
    double x = 0;
    double y = 0;
    x = rstate(0).position().x;
    y = rstate(0).position().y;
      __android_log_print(ANDROID_LOG_ERROR, "BridgeLOG", "states count: %d; last (x: %f, y: %f)", _stateHistory.size(), x, y);
#endif
}

Types::ObjectState::StateVec Navigator::defaultMeasurementNoise() const {
    Types::ObjectState::StateVec vec;
    vec(0) = 100.0; vec(1) = 100.0;
    vec(2) = 100.0; vec(3) = 100.0;
    vec(4) = 100.0; vec(5) = 100.0;
    vec(6) = 100.0; vec(7) = 100.0;
    return vec;
}

SmartPtr<Navigator> Navigator::instance() {
    if (__instance.isNull()) {
        __instance = new Navigator();
    }
    return __instance;
}

SmartPtr<Navigator> Navigator::clear() {
    /*WARNING! caused crash*/
    __instance.clear();
}

double Navigator::smoothedDistanceToBeacon(hash_t hash, size_t smooth_length) {
    return Navigator::instance()->beacon().beaconDistance(hash, smooth_length);
}
