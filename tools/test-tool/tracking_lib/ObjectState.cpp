#include "ObjectState.h"

#include <fstream>

namespace Types {
ObjectState::ObjectState() :
    _state_vector(StateVec::Zero()),
    _covar_matrix(CovarMatrix::Identity())
{
//    for (int i = 0; i<_state_vector.rows(); ++i) {
//        for (int j = 0; j<_state_vector.cols(); ++j) {
//            _state_vector(i, j) = 0;
//        }
//    }

//    for (int i = 0; i<_covar_matrix.rows(); ++i) {
//        for (int j = 0; j<_covar_matrix.cols(); ++j) {
//            _covar_matrix(i, j) = 0;
//        }
//    }
}

bool ObjectState::operator==(const ObjectState &rhs) {
    return (
            _state_vector == rhs._state_vector
         && _covar_matrix == rhs._covar_matrix
         && _timestamp    == rhs._timestamp
           );
}

Point   ObjectState::position()     const {
    Point p;
    p.x = _state_vector(X);
    p.y = _state_vector(Y);
    p.z = 0;
    return p;
}

Vector3 ObjectState::velocity()     const {
    Vector3 v;
    v.x = _state_vector(Vx);
    v.y = _state_vector(Vy);
    v.z = 0;
    return v;
}

Vector3 ObjectState::acceleration() const {
    Vector3 v;
    v.x = _state_vector(Ax);
    v.y = _state_vector(Ay);
    v.z = 0;
    return v;
}

Vector3 ObjectState::accelerationDerivative() const {
    Vector3 v;
    v.x = _state_vector(dAx);
    v.y = _state_vector(dAy);
    v.z = 0;
    return v;
}


void ObjectState::setPosition(const Point& p) {
    _state_vector[X] = p.x;
    _state_vector[Y] = p.y;
}

void ObjectState::setVelocity(const Vector3& v) {
    _state_vector[Vx] = v.x;
    _state_vector[Vy] = v.y;
}

void ObjectState::setAcceleration(const Vector3& a) {
    _state_vector[Ax] = a.x;
    _state_vector[Ay] = a.y;
}

void ObjectState::setAccelerationDerivative(const Vector3& ad) {
    _state_vector[dAx] = ad.x;
    _state_vector[dAy] = ad.y;
}

} // namespace Types


template <class Stream>
Stream &operator << (Stream &stream, const Types::ObjectState &state) {
    Types::ObjectState::StateVec v = state.stateVector();
    Types::ObjectState::CovarMatrix m = state.covarMatrix();
    stream  << state.timestamp()
        << ", " << v(Types::ObjectState::X)  << ", " << v(Types::ObjectState::Y)
        << ", " << v(Types::ObjectState::Vx) << ", " << v(Types::ObjectState::Vy)
        << ", " << v(Types::ObjectState::Ax) << ", " << v(Types::ObjectState::Ay)
        << ", " << m(Types::ObjectState::X, Types::ObjectState::X)  << ", " << m(Types::ObjectState::Y, Types::ObjectState::Y)
        << ", " << m(Types::ObjectState::Vx, Types::ObjectState::Vx) << ", " << m(Types::ObjectState::Vy, Types::ObjectState::Vy)
        << ", " << m(Types::ObjectState::Ax, Types::ObjectState::Ax) << ", " << m(Types::ObjectState::Ay, Types::ObjectState::Ay)
        << std::endl;
    return stream;
}

void initTemplates () {
    typedef std::ofstream& (*OFStreamFuncPrt) (std::ofstream &stream, const Types::ObjectState &state);
    std::ofstream f;
    f << Types::ObjectState();
}
