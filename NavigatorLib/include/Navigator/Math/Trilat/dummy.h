//
// Created by  Oleksiy Grechnyev on 3/13/2017.
// Trilateration routines stolen from the old tracking_lib
//

#pragma once

#include <vector>
#include <cmath>

#include "Navigator/Math/Position3D.h"


namespace Navigator {
    namespace Math {
        namespace Trilat {

            /** @brief  Calculate a fake RSSI signal for 2 points
             *
             * This is for the example only, of course you don't need this for the real code
             */
            double inline fakeRSSI(const Position3D &p1, const Position3D &p2, double txPower, double damp) {
                /*double dist = p1.distance(p2);
                double temp = log10(dist);
                return txPower - 10 * damp * temp;*/
                return txPower - 10 * damp * log10(p1.distance(p2));
            }


            /** @brief  Calculate a fake RSSI signal for a distance
             *
             * This is for the example only, of course you don't need this for the real code
             */
            double inline fakeRSSI(double dist, double txPower, double damp) {
                /*double dist = p1.distance(p2);
                double temp = log10(dist);
                return txPower - 10 * damp * temp;*/
                return txPower - 10 * damp * log10(dist);
            }


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

            /// This version throws exception if failure
            Position3D trilatLocation2d(const std::vector<Position3D> &beaconsPos,
                                        const std::vector<double> &beaconsDist);

            /** \brief Trilateration in 3D.
            *
            * Trilateration in 3D with a minimum of reference 4 points (beacons) (UNUSED).
            * As the 4 or more distances cannot be satisfied exctly in general,
            * the result is the least squares fit.
            *
            * UNUSED
            *
            * Based on https://github.com/Wayne82/Trilateration
            *
            * \param[in]  beaconsPos   List of beacon positions (list<Point>).
            * \param[in]  beaconsDist  List of distances to beacons (list<double>).
            * \param[out] location     The result of trilateration.
            * \result                  true if success, false otherwise.
            * \sa TrilatLocation2d()
            */
            bool trilatLocation3d(const std::vector<Position3D> &beaconsPos,
                                  const std::vector<double> &beaconsDist,
                                  Position3D &location);


            /// This version throws exception if failure
            Position3D trilatLocation3d(const std::vector<Position3D> &beaconsPos,
                                        const std::vector<double> &beaconsDist);


        }
    }
}