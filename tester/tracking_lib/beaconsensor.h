#ifndef BEACONSENSOR_H
#define BEACONSENSOR_H

#include "abstractsensor.h"
#include "beacon.h"
#include "common_types.h"

#include <cstdio>
#include <map>

namespace Sensors {
/** \brief Beacons sensor. Contains a list of Hardware::Beacon.
 *
 *  Inherits things like addState() and updateState(), while overriding proceedMeasurements()
 */
class BeaconSensor : public AbstractSensor {
    public:
        static const double DEFAULT_DATA_ASSOCIATION_INTERVAL;
        /// Map of Hardware::Beacon with hash_t as the key
        typedef std::map<hash_t, Hardware::Beacon>    BeaconContainer;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        /// Constructor, sets MeasureSigma=(3,3,3)
        BeaconSensor();
        virtual ~BeaconSensor();
        /// Return SensorType::Beacon
        virtual int sensorType() const;
        
        /// Delete all beacons
        virtual void clear();
        /// Add new beacon
        void    addBeacon(const Hardware::Beacon &b);
        /// Calibrate one beacon
        bool    calibrateBeacon(hash_t hash, const Hardware::Beacon::CalibrationDataContainer &data);
        /// Set dataAssociationInterval
        void    setDataAssociationInterval(double dt);
        /// Add one measurement. Invokes updateState().
        void    addMeasurement(const BeaconMeasurement &m);
        /// Add one measurement. Invokes updateState().
        void    addMeasurement(hash_t hash, double tx_power, double rssi, timestamp_t tm);

        /// Return number of beacons
        size_t  beaconsCount();

        /// Set measureSigma
        void    setMeasureSigma(double sx, double sy, double sz);
        /// Set measureSigma
        void    setMeasureSigma(const Vector3 &s);
        /// Get measureSigma
        Vector3 measureSigma() const;
        /// true is beacon hash exists
        bool    hasBeacon(hash_t hash);
        /// Get beacon by hash
        Hardware::Beacon beacon(hash_t hash);

        /** \brief Calculate distance to beacon hash
         *
         * Uses BMath::get_distance. Apparently it averages rssi and txPower over several measurements.
         * 
         * \param[in]  hash           Hash code of the beacon
         * \param[in]  smooth_count   Max number of measurements to average over
         * \result                    Distance to the beacon
         */
        double  beaconDistance(hash_t hash, size_t smooth_count = 1);

    protected:
        /** \brief Create a Types::ObjectState from measurements
         * 
         * Uses trilateration (BMath::TrilatLocation2d) 
         */
        virtual Types::ObjectState    proceedMeasurements();
        /// Creates a constant 8-vector of (0.3, 2, 10, 10, 10, 10, 10, 10), don't ask me. USUSED?
        virtual Types::ObjectState::StateVec defaultMeasurementNoise() const;
        /// Returns a 8x8 identity matrix for now
        virtual Types::ObjectState::CovarMatrix   measureCovarMatrix( const Types::ObjectState &measurement
                                                                    , const Types::ObjectState &prevState) const;

    private:
        /// Map with beacons
        BeaconContainer    _beacons;
        double  _dataAssociationInterval;
        /// Timestamp of the last measurement
        timestamp_t _lastMeasureTime;
        Vector3 _measureSigma;
};
} // namespace Sensors

#endif // BEACONSENSOR_H
