//
// Created by  Oleksiy Grechnyev on 3/13/2017.
// Trilateration routines stolen from the old tracking_lib
//

#pragma once

#include <vector>

#include "../Position3D.h"


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
             * \param[in]  beaconsPos   Vector of beacon positions .
             * \param[in]  beaconsDist  Vector of distances to beacons .
             * \param[out] location     The result of trilateration.
             * \result                  true if success, false otherwise.
             */
            bool trilatLocation2d(const std::vector<Position3D> &beaconsPos,
                                  const std::vector<double> &beaconsDist,
                                  Position3D &location);
    
            // TODO include trilat 3d here also !
            bool trilatLocation3d(const std::vector<Position3D> &beaconsPos,
                                  const std::vector<double> &beaconsDist,
                                  Position3D &location);
        }
    }
}