#ifndef ACCELEROMETERSENSOR_H
#define ACCELEROMETERSENSOR_H

#include "abstractsensor.h"
#include "common_types.h"


namespace Sensors {
class AccelerometerSensor : public AbstractSensor {
    public:
        const double DEFAULT_DATA_ASSOCIATION_INTERVAL = 1000; // msec
        static const int DEFAULT_FILTER_WIN_SIZE = 10;
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        AccelerometerSensor();
        virtual ~AccelerometerSensor();

        virtual int sensorType() const;

        virtual void clear();
        void    setDataAssociationInterval(double dt);
        void    addMeasurement(const AccMeasurement &m);
        void    addMeasurement(double ax, double ay, double az, timestamp_t tm);

        void    setMeasureSigma(double sx, double sy, double sz);
        void    setMeasureSigma(const Vector3 &s);
        Vector3 measureSigma() const;

    protected:
        virtual Types::ObjectState    proceedMeasurements();
        AccMeasurement    filter(const AccelerationMeasurementsContainer &mc);
        Types::ObjectState::StateVec defaultMeasurementNoise() const;

        virtual Types::ObjectState::CovarMatrix   measureCovarMatrix( const Types::ObjectState &measurement
                                                                    , const Types::ObjectState &prevState) const;

    private:
        int     _measurementsCapacity;
        int     _filterWinSize;
        double  _dataAssociationInterval;
        timestamp_t _lastMeasureTime;
        AccelerationMeasurementsContainer   _measurements;
        AccelerationMeasurementsContainer   _measurements_filtered;
        Vector3 _measureSigma;
};
} // namespace Sensors

#endif // ACCELEROMETERSENSOR_H
