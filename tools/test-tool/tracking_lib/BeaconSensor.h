#ifndef BEACONSENSOR_H
#define BEACONSENSOR_H

#include "AbstractSensor.h"
#include "Beacon.h"
#include "common_defs.h"

#include <cstdio>
#include <map>

namespace Sensors {
/** \brief Beacons sensor. Contains a list of Hardware::Beacon.
 *
 *  Inherits things like addState() and updateState(), while overriding proceedMeasurements()
 *
 * Note: apparently BeaconSensor uses txPower from measurements
 * while txPower of beacon is ignored, while damp is taken from the beacon data
 */
    class BeaconSensor : public AbstractSensor {
    public:
        //-------------------------------
        // Constants
        //-------------------------------
        static constexpr double DEFAULT_DATA_ASSOCIATION_INTERVAL = 100;

        //-------------------------------
        // Types
        //-------------------------------

        /// Map of Hardware::Beacon with hash_t as the key
        typedef std::map<hash_t, Hardware::Beacon> BeaconContainer;

        // Needed by eigen
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW

        //-------------------------------
        // Constructor
        //-------------------------------

        /// Constructor, sets MeasureSigma=(3,3,3)
        BeaconSensor() : AbstractSensor() {
            Vector3 s;
            s.x = 3;
            s.y = 3;
            s.z = 3;
            setMeasureSigma(s);
        }

        // Destructor, if neeeded
        //virtual ~BeaconSensor() {}


        //-------------------------------
        // Public methods
        //-------------------------------

        /// Return SensorType::Beacon
        virtual int sensorType() const{
            return SensorType::Beacon;
        }

        /// Delete all beacons
        virtual void clear(){
            _beacons.clear();
        }

        /// Add new beacon
        void addBeacon(const Hardware::Beacon &b){
            _beacons[b.hash()] = b;
        }

        /// Calibrate one beacon
        bool calibrateBeacon(hash_t hash, const Hardware::Beacon::CalibrationDataContainer &data) {
            if (hasBeacon(hash)) {
                return _beacons[hash].calibrate(data);
            }
            return false;
        }

        /// Set dataAssociationInterval
        void setDataAssociationInterval(double dt){
            _dataAssociationInterval = dt;
        }

        /// Add one measurement. Invokes updateState().
        void addMeasurement(const BeaconMeasurement &m){
            addMeasurement(m.hash, m.txPower, m.rssi, m.timestamp);
        }


        /// Add one measurement. Invokes updateState().
        void addMeasurement(hash_t hash, double tx_power, double rssi, timestamp_t tm);

        /// Return number of beacons
        size_t beaconsCount(){
            return _beacons.size();
        }

        /// Set measureSigma
        void setMeasureSigma(double sx, double sy, double sz){
            _measureSigma.x = sx;
            _measureSigma.y = sy;
            _measureSigma.z = sz;
        }

        /// Set measureSigma
        void setMeasureSigma(const Vector3 &s){
            setMeasureSigma(s.x, s.y, s.z);
        }

        /// Get measureSigma
        Vector3 measureSigma() const{
            return _measureSigma;
        }

        /// true is beacon hash exists
        bool hasBeacon(hash_t hash){
            return (_beacons.count(hash) > 0);
        }

        /// Get beacon by hash
        Hardware::Beacon beacon(hash_t hash) {
            Hardware::Beacon b;
            if (_beacons.count(hash) > 0) {
                b = _beacons[hash];
            }
            return b;
        }

        /** \brief Calculate distance to beacon hash
         *
         * Uses BMath::get_distance. Apparently it averages rssi and txPower over several measurements.
         * 
         * \param[in]  hash           Hash code of the beacon
         * \param[in]  smooth_count   Max number of measurements to average over
         * \result                    Distance to the beacon
         */
        double beaconDistance(hash_t hash, size_t smooth_count = 1);

    protected:
        /** \brief Create a Types::ObjectState from measurements
         * 
         * Uses trilateration (BMath::TrilatLocation2d) 
         */
        virtual Types::ObjectState proceedMeasurements();

        /// Creates a constant 8-vector of (0.3, 2, 10, 10, 10, 10, 10, 10), don't ask me. USUSED?
        virtual Types::ObjectState::StateVec defaultMeasurementNoise() const;

        /// Returns a 8x8 identity matrix for now
        virtual Types::ObjectState::CovarMatrix
        measureCovarMatrix(const Types::ObjectState &measurement, const Types::ObjectState &prevState) const;

    private:
        /// Map with beacons
        BeaconContainer _beacons;
        double _dataAssociationInterval = DEFAULT_DATA_ASSOCIATION_INTERVAL;
        /// Timestamp of the last measurement
        timestamp_t _lastMeasureTime = -1;
        Vector3 _measureSigma;
    };
} // namespace Sensors

#endif // BEACONSENSOR_H
