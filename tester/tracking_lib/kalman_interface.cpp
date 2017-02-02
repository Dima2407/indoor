#include "kalman_interface.h"

KalmanInterface::ProcessModel::ProcessModel() {
    jacobian = KalmanInterface::SimpleState::MatStateState::Zero();
}

void KalmanInterface::ProcessModel::updateState(ProcessModel::StateType &state, const double dt) {
    KalmanInterface::SimpleState::VecState m = getJacobian(state, dt) * state.x;// + getNoiseCovariance(dt) * (sigma * dt);
    state.x = m;
}

KalmanInterface::KalmanMat KalmanInterface::ProcessModel::getJacobian(const KalmanInterface::SimpleState &state, const double dt) {
    jacobian = MatStateState::Identity();
    jacobian(Types::ObjectState::X, Types::ObjectState::X)  = 1.0;
    jacobian(Types::ObjectState::X, Types::ObjectState::Vx) = dt;
    jacobian(Types::ObjectState::X, Types::ObjectState::Ax) = dt*dt / 2.0;
    jacobian(Types::ObjectState::Y, Types::ObjectState::Y)  = 1.0;
    jacobian(Types::ObjectState::Y, Types::ObjectState::Vy) = dt;
    jacobian(Types::ObjectState::Y, Types::ObjectState::Ay) = dt*dt / 2.0;
    jacobian(Types::ObjectState::Vx, Types::ObjectState::Vx) = 1.0;
    jacobian(Types::ObjectState::Vx, Types::ObjectState::Ax) = dt;
    jacobian(Types::ObjectState::Vy, Types::ObjectState::Vy) = 1.0;
    jacobian(Types::ObjectState::Vy, Types::ObjectState::Ay) = dt;
    jacobian(Types::ObjectState::Ax, Types::ObjectState::Ax) = 1.0;
    jacobian(Types::ObjectState::Ay, Types::ObjectState::Ay) = 1.0;
    return jacobian;
}

KalmanInterface::KalmanVec KalmanInterface::kalman_state(const Types::ObjectState &state) {
    return state.stateVector();
}

KalmanInterface::KalmanMat KalmanInterface::kalman_covar(const Types::ObjectState &state) {
    return state.covarMatrix();
}

KalmanInterface::SimpleState KalmanInterface::kalman_object_state(const Types::ObjectState &state) {
    SimpleState ks;
    ks.x = state.stateVector();
    ks.covariance = state.covarMatrix();
    return ks;
}

KalmanInterface::KalmanVec KalmanInterface::kalman_process_noise() {
    KalmanVec n;
    n(Types::ObjectState::dAx) =  0.001;
    n(Types::ObjectState::dAy) =  0.001;
    n(Types::ObjectState::Ax)  =  1.0;
    n(Types::ObjectState::Ay)  =  1.0;
    n(Types::ObjectState::Vx)  =  1.0;
    n(Types::ObjectState::Vy)  =  1.0;
    n(Types::ObjectState::X)   =  0.5;
    n(Types::ObjectState::Y)   =  0.5;
    return n;
}

