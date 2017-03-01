#ifndef ACCELEROMETERSENSOR_H
#define ACCELEROMETERSENSOR_H

#include "AbstractSensor.h"
#include "common_types.h"


namespace Sensors {

/** \brief Accelerometer sensor. Contains list of measurements.
 *
 * Similar to Sensors::BeaconSensor.
 *
 * Note: Accelerometer data is not used at present. Not fully documented.
 */
    class AccelerometerSensor : public AbstractSensor {
    public:
        // Constants
        const double DEFAULT_DATA_ASSOCIATION_INTERVAL = 1000; // msec
        static const int DEFAULT_FILTER_WIN_SIZE = 10;

        // Eigen stuff
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW

        //--------------------------
        // Public constructor & destructor
        //--------------------------

        /// Constructor
        AccelerometerSensor(){
            Vector3 s;
            s.x = 0.05;
            s.y = 0.05;
            s.z = 0.05;
            setMeasureSigma(s);
        }

        // Empty virtual destructor, just in case
        // virtual ~AccelerometerSensor() {}

        //--------------------------
        // Public methods
        //--------------------------

        /// Get sensor type
        virtual int sensorType() const{
            return SensorType::AccelerometerLinear;
        }

        /// Remove all measurements
        virtual void clear(){
            _measurements.clear();
            _measurements_filtered.clear();
        }

        /// Set _dataAssociationInterval
        void setDataAssociationInterval(double dt){
            _dataAssociationInterval = dt;
        }

        void addMeasurement(const AccMeasurement &m);

        void addMeasurement(double ax, double ay, double az, timestamp_t tm);

        /// Set _measureSigma
        void setMeasureSigma(double sx, double sy, double sz) {
            _measureSigma.x = sx;
            _measureSigma.y = sy;
            _measureSigma.z = sz;
        }

        /// Set _measureSigma
        void setMeasureSigma(const Vector3 &s){
            setMeasureSigma(s.x, s.y, s.z);
        }

        /// Get _measureSigma
        Vector3 measureSigma() const {
            return _measureSigma;
        }

    private:
        //--------------------------
        // Private methods
        //--------------------------
        virtual Types::ObjectState proceedMeasurements();

        AccMeasurement filter(const AccelerationMeasurementsContainer &mc);

        Types::ObjectState::StateVec defaultMeasurementNoise() const;

        virtual Types::ObjectState::CovarMatrix
        measureCovarMatrix(const Types::ObjectState &measurement, const Types::ObjectState &prevState) const;

        //--------------------------
        // Private fields
        //--------------------------

        int _filterWinSize = DEFAULT_FILTER_WIN_SIZE;
        double _dataAssociationInterval = DEFAULT_DATA_ASSOCIATION_INTERVAL;
        timestamp_t _lastMeasureTime = -1;

        int _measurementsCapacity;
        AccelerationMeasurementsContainer _measurements;
        AccelerationMeasurementsContainer _measurements_filtered;
        Vector3 _measureSigma;
    };
} // namespace Sensors

#endif // ACCELEROMETERSENSOR_H
