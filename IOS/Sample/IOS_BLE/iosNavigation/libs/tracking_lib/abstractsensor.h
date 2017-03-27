#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include "objectstate.h"

#include <list>

namespace Sensors {

typedef void* SensorDataPtr;

class AbstractSensor;

typedef void (*CallBackFunc) (AbstractSensor*, SensorDataPtr);

class AbstractSensor {
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        static const size_t DEFAULT_CAPACITY = 2048;
    public:
        AbstractSensor();
        virtual ~AbstractSensor();

        virtual int sensorType() const = 0;

        Types::ObjectState          referenceState() const;
        Types::ObjectState          lastState()      const;
        Types::ObjectState          state(size_t pos)  const;
        Types::ObjectState          rstate(size_t pos) const;

        const Types::ObjectStateContainer& history(size_t length = 0) const;

        size_t dataCapacity() const;
        void   setDataCapacity(size_t c);
        size_t dataCount() const;

        virtual void clear();

        virtual void    setReferenceState(const Types::ObjectState &state);

        virtual bool    updated() const; // return true is after last measurement internal state was udated
        virtual void    dropUpdated();   // set 'updated' flag to false

    protected:
        void addState(const Types::ObjectState &state);
        void updateState(const Types::ObjectState &state = Types::ObjectState());
        virtual Types::ObjectState proceedMeasurements() = 0;

        virtual Types::ObjectState::CovarMatrix   measureCovarMatrix( const Types::ObjectState &measurement
                                                                    , const Types::ObjectState &prevState) const = 0;

    private:
        Types::ObjectStateContainer    _history;
        size_t                         _maxDataCapacity;
        Types::ObjectState             _referenceState;
        bool                           _updated;
};

} // namespace Sensors

#endif // ABSTRACTSENSOR_H
