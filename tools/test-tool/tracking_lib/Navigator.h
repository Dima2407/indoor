#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "SmartPtr.h"
#include "BeaconSensor.h"
#include "AccelerometerSensor.h"

/** \brief A singleton class which manages Sensors::BeaconSensor and Sensors::AccelerometerSensor
 *
 * Sensors::AccelerometerSensor seems to be disabled at present.
 *
 * Note: apparently BeaconSensor uses txPower from measurements
 * while txPower of beacon is ignored, while damp is taken from the beacon data
 */
class Navigator {
    typedef std::list<SmartPtr<Sensors::AbstractSensor> > SensorsContainer;

public: // constants
    static const size_t DEFAULT_CAPACITY = 2048;

private:
    /// Private constructor. Sets DEFAULT_CAPACITY.
    Navigator() : _maxDataCapacity(DEFAULT_CAPACITY) {}

public: // Methods
    // What is that ?
    // Unit doesn't work without it, Tester does, WHY ???
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    /// Get beacon sensor (const)
    const Sensors::BeaconSensor &beacon() const {
        return _beacon;
    }

    /// Get beacon sensor
    Sensors::BeaconSensor &beacon() {
        return _beacon;
    }

    /// Get accelerometer sensor (const)
    const Sensors::AccelerometerSensor &accelerometer() const {
        return _accelerometer;
    }

    /// Get accelerometer sensor
    Sensors::AccelerometerSensor &accelerometer() {
        return _accelerometer;
    }

    /// Add one Sensors::BeaconSensor measurement and call updateState if _beacon.updated()
    void addBeaconMeasurement(const BeaconMeasurement &m){
        addBeaconMeasurement(m.hash, m.txPower, m.rssi, m.timestamp);
    }

    /// Add one Sensors::BeaconSensor measurement and call updateState if _beacon.updated()
    void addBeaconMeasurement(hash_t hash, double tx_power, double rssi, timestamp_t timestamp);

    /// Add one Sensors::AccelerometerSensor measurement. Does nothing for now!
    void addAccelerometerMeasurement(const AccMeasurement &m);

    /// Add one Sensors::AccelerometerSensor measurement. Does nothing for now!
    void addAccelerometerMeasurement(double ax, double ay, double az, timestamp_t timestamp);

    /// Get last state from _stateHistory
    Types::ObjectState lastState() const {
        return rstate(0);
    }

    /// Get state i from _stateHistory (0 = oldest)
    Types::ObjectState state(size_t i) const;

    /// Get state i from _stateHistory (0 = newest)
    Types::ObjectState rstate(size_t i) const;

    /// Get _maxDataCapacity
    size_t dataCapacity() const{
        return _maxDataCapacity;
    }

    /// Set _maxDataCapacity
    void setDataCapacity(size_t c);

    /// Return _stateHistory.size()
    size_t dataCount() const {
        return _stateHistory.size();
    }

protected:

    /// Add/update measurement and set it as reference state???
    void updateState(const Types::ObjectState &measurement);

    /// Add state to history if valid (timestamp>0)
    void addState(const Types::ObjectState &state);

    /// Return the 8-vector with elements 100.0, why ?
    Types::ObjectState::StateVec defaultMeasurementNoise() const;

public:
    /// Return Navigator singleton instance
    static SmartPtr<Navigator> instance();

    /// What was that crash about?
    static SmartPtr<Navigator> clear(); /*WARNING! caused crash*/

    /** \brief Smoothed distance to beacons
     *
     * Simply returns _beacon.beaconDistance(hash, smooth_length) at present.
     *
     * \param[in]  hash           Hash code of the beacon
     * \param[in]  smooth_length  Max number of measurements to average over?
     * \result                    Distance to the beacon
     *
     */
    static double smoothedDistanceToBeacon(hash_t hash, size_t smooth_lwngth = 1);

protected:
    /// The instance of singleton Navigator
    static SmartPtr<Navigator> __instance;

protected:
    /// The Beacon sensor
    Sensors::BeaconSensor _beacon;
    /// The accelerometer sensor
    Sensors::AccelerometerSensor _accelerometer;
    /// History: container of Types::ObjectState
    Types::ObjectStateContainer _stateHistory;
    /// Max size of _stateHistory apparently
    size_t _maxDataCapacity;
};

#endif // NAVIGATOR_H
