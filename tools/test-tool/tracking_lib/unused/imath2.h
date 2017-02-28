//
// Created by  Oleksiy Grechnyev on 2/28/2017.
//

#ifndef TESTTOOL_IMATH2_H
#define TESTTOOL_IMATH2_H

#include "common_types.h"
#include "Objectstate.h"
#include "imath1.h"

/// \file imath2.h : Unused things that were originally in imath.h

namespace Math {


    /// Despite name, doesn't seem to use Kalman filters.
    ObjectState kalman(const ObjectState &currState, const ObjectState &beaconState, const ObjectState &accState);

    /** \brief Use kalman filter
     *
     *        Model:
     * acceleration is constant and zero
     * velocity is constant
     * position is lineary changed
     *
     * Note: this is supposed to be used by Navigator, but currrently disabled
     *
     **/
    Types::ObjectState kalman(const Types::ObjectState &currState, const Types::ObjectState &measure);


    /// Used by smooth()
    std::vector<double>  mean_filter(int n, const std::vector<double> &data, const std::vector<double> &weights = std::vector<double>());

    /** \brief General smoothing function (UNUSED)
     *
     * preparing data, weigths and calling appropriate subroutine
     */
    std::vector<double> smooth(const std::vector<double> &measurements, const std::vector<time_t> &times = std::vector<time_t>(), time_t max_time = 0);

}

Types::ObjectState kalman(const Types::ObjectState &currentState, const Types::ObjectState &measurement);

#endif //TESTTOOL_IMATH2_H
