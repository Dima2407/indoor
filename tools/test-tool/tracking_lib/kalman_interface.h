#pragma once
#ifndef KALMAN_TYPES_H
#define KALMAN_TYPES_H

#include "objectstate.h"

#include "KalmanFilter.h"

/** \brief Kalman filter operations
 *
 * Used by imath.h
 */
class KalmanInterface {
    public: // types
        /// A 8-vector
        typedef Types::ObjectState::StateVec    KalmanVec;
        /// A 8x8 matrix
        typedef Types::ObjectState::CovarMatrix KalmanMat;
        typedef eigenkf::SimpleState<Types::ObjectState::NumStates> SimpleState;
        class ProcessModel : public eigenkf::ConstantProcess<SimpleState::DIM, SimpleState> {
            public:
                typedef SimpleState StateType;

                ProcessModel();
                void updateState(ProcessModel::StateType &state, const double dt);

                KalmanMat getJacobian(const SimpleState &, const double);
        };
    public: // static methods
        static KalmanVec kalman_state(const Types::ObjectState &state);
        static KalmanMat kalman_covar(const Types::ObjectState &state);
        static SimpleState kalman_object_state(const Types::ObjectState &state);
        static KalmanVec kalman_process_noise();
};

#endif // KALMAN_TYPES_H
