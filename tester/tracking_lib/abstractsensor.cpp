#include "abstractsensor.h"

#ifdef DEBUG_MODE
#ifdef ASTUDIO
#   include <android/log.h>
#endif
#endif

namespace Sensors {

AbstractSensor::AbstractSensor() : _maxDataCapacity(DEFAULT_CAPACITY)
                                 , _updated(false) {
}

AbstractSensor::~AbstractSensor() {
}

Types::ObjectState AbstractSensor::referenceState() const {
    return _referenceState;
}

Types::ObjectState AbstractSensor::lastState() const {
    return rstate(0);
}

Types::ObjectState AbstractSensor::state(size_t pos) const {
    if (pos < _history.size()) {
        Types::ObjectStateContainer::const_iterator it = _history.begin();
        std::advance(it, pos);
        return *it;
    }
    return Types::ObjectState();
}

Types::ObjectState AbstractSensor::rstate(size_t pos) const {
    if (pos < _history.size()) {
        Types::ObjectStateContainer::const_reverse_iterator it = _history.rbegin();
        std::advance(it, pos);
        return *it;
    }
    return Types::ObjectState();
}

const Types::ObjectStateContainer& AbstractSensor::history(size_t length) const {
    if (length == 0) {
        return _history;
    }
    return last_elements(_history, length);
}

size_t AbstractSensor::dataCapacity() const {
    return _maxDataCapacity;
}

void AbstractSensor::setDataCapacity(size_t c) {
    _maxDataCapacity = c;
    long int ds = _maxDataCapacity - _history.size();
    if (ds < 0) {
        Types::ObjectStateContainer tmp(_maxDataCapacity);
        std::copy_n(_history.rbegin(), _maxDataCapacity, tmp.rbegin());
        _history = tmp;
    }
}

size_t AbstractSensor::dataCount() const {
    return _history.size();
}

void AbstractSensor::clear() {
    _history.clear();
}

/// Set the reference state
void AbstractSensor::setReferenceState(const Types::ObjectState &state) {
    _referenceState = state;
}

bool AbstractSensor::updated() const {
    return _updated;
}

void AbstractSensor::dropUpdated() {
    _updated = false;
}

void AbstractSensor::addState(const Types::ObjectState &state) {
#ifdef DEBUG_MODE
#ifdef ASTUDIO
    __android_log_print(ANDROID_LOG_ERROR, "BridgeLOG", "Add new state (x: %f, y: %f), time: %d", state.position().x, state.position().y, state.timestamp());
#endif
#endif
    if (state.valid()) {
        if (!_history.empty()) {
            if (*_history.rbegin() == state) { // new state must be different from last at least in one parameter (including timestamp)
                return;
            }
        }
        Types::ObjectStateContainer::reverse_iterator it = std::find_if(_history.rbegin(), _history.rend(), Types::ObjectState_TimeUnaryPredicator(state));
        if (it != _history.rend()) {
            *it = state;
        } else {
            _history.push_back(state);
//            setReferenceState(state);
            if (_history.size() > dataCapacity()) {
                _history.pop_front();
            }
        }
        _updated = true;
    }
}

void AbstractSensor::updateState(const Types::ObjectState &state) {
    if (state.valid()) {
        addState(state);
    } else {
        Types::ObjectState newState = proceedMeasurements();
        addState(newState);
    }
}

} // namespace Sensors
