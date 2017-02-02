#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include "objectstate.h"

#include <list>

namespace Sensors {

/// A new name for void*, enjoy.
typedef void* SensorDataPtr;

class AbstractSensor;

/// Pointer to a function void callback(Snsors::AbstractSensor *, void *){}.
typedef void (*CallBackFunc) (AbstractSensor*, SensorDataPtr);

/** \brief The abstract parent of Sensors::BeaconSensor and Sensors::AccelerometerSensor.
 *
 * Keeps one Types::ObjectState object called referenceState, and a container of 
 * Types::ObjectState objects called history. dataCapacity is the maximum size of history.
 *
 * Apart from keeping the history, this class doesn't do much. Apparently this changes in its chidren.
 */
class AbstractSensor {
    public:
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW
        static const size_t DEFAULT_CAPACITY = 2048;
    public:
        /// A pretty simple constructor, sets default capacity and _updated == false
        AbstractSensor();
        virtual ~AbstractSensor();
        
        /// Get sensor type. Overridden by subclasses.
        virtual int sensorType() const = 0;

        /// Get reference state.
        Types::ObjectState          referenceState() const;
        /** \brief Return the last state in history.
         * 
         * Note: used in bridge.h to get the device position
         */
        Types::ObjectState          lastState()      const;
        
        /// Return a history state with index pos (0=oldest).
        Types::ObjectState          state(size_t pos)  const;
        /// Return a history state with index pos (0=newest).
        Types::ObjectState          rstate(size_t pos) const;
        
        /// Get the entire history
        const Types::ObjectStateContainer& history(size_t length = 0) const;

        /// Get data capacity
        size_t dataCapacity() const;
        /// Set data capacity
        void   setDataCapacity(size_t c);
        /// Get history size
        size_t dataCount() const;

        /// Clear history
        virtual void clear();
        
        /// Set reference state
        virtual void    setReferenceState(const Types::ObjectState &state);

        /// Get updated
        virtual bool    updated() const; // return true is after last measurement internal state was udated
        /// Set updated to false
        virtual void    dropUpdated();   // set 'updated' flag to false

    protected:
        /// Add a new state to history and set _updated=true
        void addState(const Types::ObjectState &state);
        /** \brief Add the new state if valid (timestamp >0), otherwise add proceedMeasurements()
        *
        * This is where proceedMeasurements() (i.e. trilateration) is called
        *
        * Note: If called as updateState(), it invokes proceedMeasurements(), as
        * the Types::ObjectState() constructor creates an invalid state.
        */
        void updateState(const Types::ObjectState &state = Types::ObjectState());
        
        /** \brief Perform the measurements. 
         *
         * Create the Types::ObjectState position data from sensor data.
         * For Sensors::AbstractSensor it does nothing, but for subclasses
         * it involves funny things like trilateration.
         */
        virtual Types::ObjectState proceedMeasurements() = 0;

        /** \brief Get the 8x8 CovarMatrix 
         *
         * This gives 0 for Sensors::AbstractSensor, and I think even subclasses 
         * didn't implement it properly
         */
        virtual Types::ObjectState::CovarMatrix   measureCovarMatrix( const Types::ObjectState &measurement
                                                                    , const Types::ObjectState &prevState) const = 0;

    private:
        /// History container
        Types::ObjectStateContainer    _history;
        /// Max size of history
        size_t                         _maxDataCapacity;
        /// The reference state
        Types::ObjectState             _referenceState;
        /// The updated flag
        bool                           _updated;
};

} // namespace Sensors

#endif // ABSTRACTSENSOR_H
