#ifndef OBJECTSTATE_H
#define OBJECTSTATE_H

#include "Eigen/Dense"
#include "common_types.h"

namespace Types {
    
/** \brief Object (Smartphone) state as a vector + matrix.
 *
 * Contains a 8-vector of Object position, velocity, acceleration etc. in 2D only,
 * and a 8x8 matrix (why the matrix). Also contains timestamp.
 * This is a data class which basically has only data, getters and setters.
 *
 * Uses Eigen::Matrix from Eigen Library.
 *
 * Used by Sensors::AbstractSensor and other classes.
 *
 * WARNING !!! Do not confuse this with ObjectState in common_types.h !
 */
class ObjectState {
    public:
        /// Index names and number of indices
        enum {
            X   = 0,
            Y   = 1,
            Vx  = 2,
            Vy  = 3,
            Ax  = 4,
            Ay  = 5,
            dAx = 6,
            dAy = 7,
            NumStates = 8
        };
        /// The 8-vector
        typedef Eigen::Matrix<double, NumStates, 1> StateVec;
        /// The 8x8 matrix
        typedef Eigen::Matrix<double, NumStates, NumStates> CovarMatrix;
    public:
        /// Pretty basic constructor. Creates an invalid (timestamp<0) state.
        ObjectState();

        bool operator==(const ObjectState &rhs);


//        get
        /// Get position (X,Y,0)
        Point       position()     const;
        /// Get velocity (Vx,Vy,0)
        Vector3     velocity()     const;
        /// Get acceleration (Ax, Ay, 0)
        Vector3     acceleration() const;
        /// Get acceleration derivative (dAx, dAy, 0)
        Vector3     accelerationDerivative() const;
        /// Get timestamp
        timestamp_t timestamp() const;
        /// Get state as a 8-vector
        const StateVec&     stateVector() const;
        /// Get the 8x8 covar matrix
        const CovarMatrix&  covarMatrix() const;
        /// Check if timestamp is >0
        bool valid () const;

//        set
        /// Set position (X,Y,0)
        void setPosition(const Point& p);
        /// Set velocity (Vx,Vy,0)
        void setVelocity(const Vector3& v);
        /// Set acceleration (Ax, Ay, 0)
        void setAcceleration(const Vector3& a);
        /// Set acceleration derivative (dAx, dAy, 0)
        void setAccelerationDerivative(const Vector3& ad);
        /// Set timestamp
        void setTimestamp(timestamp_t t);
        /// Set state as a 8-vector
        void setStateVector(const StateVec& v);
        /// Set the 8x8 covar matrix
        void setCovarMatrix(const CovarMatrix& m);

    public:
        static const unsigned int __num_states = NumStates;

    private:
        StateVec    _state_vector;
        CovarMatrix _covar_matrix;
        timestamp_t _timestamp;
};

/** \brief list of Types::ObjectState */
typedef std::list<Types::ObjectState> ObjectStateContainer;

//utility classes for algorithms
/** \brief Functor which returns false, parent to  Types::ObjectState_TimeUnaryPredicator. */
class ObjectState_AbstractUnaryPredicator {
    protected:
        ObjectState_AbstractUnaryPredicator(const Types::ObjectState &s) : _internal_state(s) {}

    public:
        virtual ~ObjectState_AbstractUnaryPredicator() {}
        virtual bool operator() (const Types::ObjectState &s) = 0;
        const Types::ObjectState&  internalState() const {return _internal_state;}

    private:
        Types::ObjectState _internal_state;
};

/** \brief A functor which compares timestamps of two Types::ObjectState objects. 
 *
 * Used by Sensors::AbstractSensor.
 */
class ObjectState_TimeUnaryPredicator : public ObjectState_AbstractUnaryPredicator {
    public:
        ObjectState_TimeUnaryPredicator(const Types::ObjectState &s) : ObjectState_AbstractUnaryPredicator(s) {}

        virtual bool operator() (const Types::ObjectState &s) {
            return internalState().timestamp() == s.timestamp();
        }
};

} //  namespace Types

/// Write ObjectState to a stream
template <class Stream>
Stream &operator << (Stream &stream, const Types::ObjectState &state);

#endif // OBJECTSTATE_H
