#ifndef ABSTRACTSENSOR_H
#define ABSTRACTSENSOR_H

#include "Objectstate.h"
#include "Point.h"

#include <list>

namespace Sensors {

// A new name for void*, enjoy! UNUSED
//typedef void* SensorDataPtr;

    class AbstractSensor;

// Pointer to a function void callback(Sensors::AbstractSensor *, void *){}, UNUSED
//typedef void (*CallBackFunc) (AbstractSensor*, SensorDataPtr);

/** \brief The abstract parent of Sensors::BeaconSensor and Sensors::AccelerometerSensor.
 *
 * Keeps one Types::ObjectState object called referenceState, and a container of 
 * Types::ObjectState objects called history. dataCapacity is the maximum size of history.
 *
 * Apart from keeping the history, this class doesn't do much. Apparently this changes in its chidren.
 *
 * Note: _referenceState is definitely UNUSED in BeaconSensor
 * AccelerometerSensor reads it, but doesn't write (WTF ???)
 */
    class AbstractSensor {
    public:
        // Stupid eigen stuff
        EIGEN_MAKE_ALIGNED_OPERATOR_NEW

        // Const
        static constexpr size_t DEFAULT_CAPACITY = 2048;

        //--------------------------
        // Public abstract methods
        //--------------------------

        /// Virtual destructor just in case
        virtual ~AbstractSensor() {}

        /// Get sensor type. Overridden by subclasses.
        virtual int sensorType() const = 0;

        //--------------------------
        // Public methods
        //--------------------------



        /// Get reference state.
        Types::ObjectState referenceState() const{
            return _referenceState;
        }


        /** \brief Return the last state in history.
         * 
         * Note: used in e.g. bridge.h to get the device position
         */
        Types::ObjectState lastState() const{
            return rstate(0);
        }

        /// Return a history state with index pos (0=oldest).
        Types::ObjectState state(size_t pos) const;

        /// Return a history state with index pos (0=newest).
        Types::ObjectState rstate(size_t pos) const;

        /// Get the entire history
        Types::ObjectStateContainer history(size_t length = 0) const;

        /// Get data capacity
        size_t dataCapacity() const{
            return _maxDataCapacity;
        }

        /// Set data capacity
        void setDataCapacity(size_t c);

        /// Get history size
        size_t dataCount() const{
            return _history.size();
        }

        /// Clear history
        virtual void clear() {
            _history.clear();
        }

        /// Set reference state
        virtual void setReferenceState(const Types::ObjectState &state) {
            _referenceState = state;
        }

        /// Get updated
        virtual bool updated() const{
            // return true is after last measurement internal state was udated
            return _updated;
        }


        /// Set updated to false
        virtual void dropUpdated() {
            _updated = false; // set 'updated' flag to false
        }

    protected:
        //--------------------------
        // Protected methods
        //--------------------------

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

        //--------------------------
        // Protected abstract methods
        //--------------------------

        /** \brief Perform the measurements. 
         *
         * Create the Types::ObjectState position data from sensor data.
         * Abstract for Sensors::AbstractSensor, for subclasses
         * it involves funny things like trilateration.
         */
        virtual Types::ObjectState proceedMeasurements() = 0;

        /** \brief Get the 8x8 CovarMatrix 
         *
         * Abstract for Sensors::AbstractSensor, and even subclasses
         * didn't implement it properly
         */
        virtual Types::ObjectState::CovarMatrix
        measureCovarMatrix(const Types::ObjectState &measurement, const Types::ObjectState &prevState) const = 0;

    private:
        //--------------------------
        // Private fields
        //--------------------------


        /// History container
        Types::ObjectStateContainer _history;
        /// Max size of history
        size_t _maxDataCapacity = DEFAULT_CAPACITY;
        /// The reference state, UNUSED in BeaconSensor
        Types::ObjectState _referenceState;
        /// The updated flag
        bool _updated = false;
    };

} // namespace Sensors

#endif // ABSTRACTSENSOR_H
