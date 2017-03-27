#ifndef BEACONSENSOR_H
#define BEACONSENSOR_H

#include "abstractsensor.h"
#include "beacon.h"
#include "common_types.h"

#include <cstdio>
#include <map>

namespace Sensors {
class BeaconSensor : public AbstractSensor {
    public:
        static const double DEFAULT_DATA_ASSOCIATION_INTERVAL;
        typedef std::map<hash_t, Hardware::Beacon>    BeaconContainer;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        BeaconSensor();
        virtual ~BeaconSensor();

        virtual int sensorType() const;

        virtual void clear();
        void    addBeacon(const Hardware::Beacon &b);
        bool    calibrateBeacon(hash_t hash, const Hardware::Beacon::CalibrationDataContainer &data);
        void    setDataAssociationInterval(double dt);
        void    addMeasurement(const BeaconMeasurement &m);
        void    addMeasurement(hash_t hash, double tx_power, double rssi, timestamp_t tm);

        size_t  beaconsCount();

        void    setMeasureSigma(double sx, double sy, double sz);
        void    setMeasureSigma(const Vector3 &s);
        Vector3 measureSigma() const;
        bool    hasBeacon(hash_t hash);
        Hardware::Beacon beacon(hash_t hash);

        double  beaconDistance(hash_t hash, size_t smooth_count = 1);

    protected:
        virtual Types::ObjectState    proceedMeasurements();
        virtual Types::ObjectState::StateVec defaultMeasurementNoise() const;

        virtual Types::ObjectState::CovarMatrix   measureCovarMatrix( const Types::ObjectState &measurement
                                                                    , const Types::ObjectState &prevState) const;

    private:
        BeaconContainer    _beacons;
        double  _dataAssociationInterval;
        timestamp_t _lastMeasureTime;
        Vector3 _measureSigma;
};
} // namespace Sensors

#endif // BEACONSENSOR_H
