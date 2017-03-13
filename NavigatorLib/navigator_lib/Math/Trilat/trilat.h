//
// Created by  Oleksiy Grechnyev on 3/13/2017.
// Trilateration routines stolen from the old tracking_lib
//

#pragma once

#include <vector>

#include "../Position3D.h"

// TODO finish this !

namespace Navi {
    namespace Math {
        namespace Trilat {
            /** \brief Trilateration in 2D.
             *
             * Trilateration in 2D with a minimum of reference 3 points (beacons).
             * As the 3 or more distances cannot be satisfied exctly in general,
             * the result is the least squares fit.
             *
             * Used in Sensors::BeaconSensor.
             *
             * Based on https://github.com/Wayne82/Trilateration
             *
             * \param[in]  beaconsPos   List of beacon positions (list<Point>).
             * \param[in]  beaconsDist  List of distances to beacons (list<double>).
             * \param[out] location     The result of trilateration.
             * \result                  true if success, false otherwise.
             * \sa TrilatLocation3d()
             */
            bool TrilatLocation2d(const std::vector<Position3D> &beaconsPos,
                                  const std::vector<double> &beaconsDist,
                                  Position3D &location);
        }
    }
}