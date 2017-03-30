#ifndef NAVIGATOR_H
#define NAVIGATOR_H

#include "smartptr.h"
#include "beaconsensor.h"
#include "accelerometersensor.h"

class Navigator {
    typedef std::list<SmartPtr<Sensors::AbstractSensor> > SensorsContainer;

    public: // constants
        static const size_t DEFAULT_CAPACITY = 2048;

    private:
        Navigator();

    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        ~Navigator();

        const Sensors::BeaconSensor& beacon() const;
              Sensors::BeaconSensor& beacon();
        const Sensors::AccelerometerSensor& accelerometer() const;
              Sensors::AccelerometerSensor& accelerometer();

              void  addBeaconMeasurement(const BeaconMeasurement &m);
              void  addBeaconMeasurement(hash_t hash, double tx_power, double rssi, timestamp_t timestamp);
              void  addAccelerometerMeasurement(const AccMeasurement &m);
              void  addAccelerometerMeasurement(double ax, double ay, double az, timestamp_t timestamp);

        Types::ObjectState   lastState() const;
        Types::ObjectState   state(size_t i) const;
        Types::ObjectState  rstate(size_t i) const;

        size_t dataCapacity() const;
        void   setDataCapacity(size_t c);
        size_t dataCount() const;

    protected:
        void updateState(const Types::ObjectState &measurement);
        void addState(const Types::ObjectState &state);
        Types::ObjectState::StateVec defaultMeasurementNoise() const;

    public:
        static SmartPtr<Navigator> instance();
        //static SmartPtr<Navigator> clear(); /*WARNING! caused crash*/
        static void clear();
        static double smoothedDistanceToBeacon(hash_t hash, size_t smooth_lwngth = 1);

    protected:
        static SmartPtr<Navigator> __instance;

    protected:
        Sensors::BeaconSensor _beacon;
        Sensors::AccelerometerSensor _accelerometer;

        Types::ObjectStateContainer  _stateHistory;
        size_t                       _maxDataCapacity;
};

#endif // NAVIGATOR_H
