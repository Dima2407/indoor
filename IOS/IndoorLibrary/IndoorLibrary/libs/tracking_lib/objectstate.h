#ifndef OBJECTSTATE_H
#define OBJECTSTATE_H

#include "external/Eigen/Dense"
#include "common_types.h"

namespace Types {
class ObjectState {
    public:
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
        typedef Eigen::Matrix<double, NumStates, 1> StateVec;
        typedef Eigen::Matrix<double, NumStates, NumStates> CovarMatrix;
    public:
        ObjectState();

        bool operator==(const ObjectState &rhs);


//        get
        Point       position()     const;
        Vector3     velocity()     const;
        Vector3     acceleration() const;
        Vector3     accelerationDerivative() const;
        timestamp_t timestamp() const;
        const StateVec&     stateVector() const;
        const CovarMatrix&  covarMatrix() const;
        bool valid () const;

//        set
        void setPosition(const Point& p);
        void setVelocity(const Vector3& v);
        void setAcceleration(const Vector3& a);
        void setAccelerationDerivative(const Vector3& ad);
        void setTimestamp(timestamp_t t);
        void setStateVector(const StateVec& v);
        void setCovarMatrix(const CovarMatrix& m);

    public:
        static const unsigned int __num_states = NumStates;

    private:
        StateVec    _state_vector;
        CovarMatrix _covar_matrix;
        timestamp_t _timestamp;
};

typedef std::list<Types::ObjectState> ObjectStateContainer;

//utility classes for algorithms
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

class ObjectState_TimeUnaryPredicator : public ObjectState_AbstractUnaryPredicator {
    public:
        ObjectState_TimeUnaryPredicator(const Types::ObjectState &s) : ObjectState_AbstractUnaryPredicator(s) {}

        virtual bool operator() (const Types::ObjectState &s) {
            return internalState().timestamp() == s.timestamp();
        }
};

} //  namespace Types

template <class Stream>
Stream &operator << (Stream &stream, const Types::ObjectState &state);

#endif // OBJECTSTATE_H
