#ifndef BMATH_H
#define BMATH_H

#include "common_types.h"
#include "inxtrapolate.h"
#include <vector>

/** \brief %Math operations: distance, trilateration and extrapolation.
 *
 *  Contains static methods get_distance() to get distance to a beacon, and methods
 *  TrilatLocation2d() and TrilatLocation3d() 
 *  for the 2D and 3D trilateration respectively.
 *  Also inxtrapolate() for extrapolation.
 */
class BMath {
    public:
	
	    /** \brief Calculate distance to a beacon.
		 *
		 * The formula is  distance = 10^( (txPower-rssi) / (10*damp) ). 
		 * Don't ask me! Judging by the formula, rssi and txPower must
         * be logarithmic quantities (in dBm or something like this)
         *
         * Used in Sensors::BeaconSensor and bridge.cpp.
		 *
		 * \param[in] rssi      Received signal strength (in dBm ???).
		 * \param[in] txPower   Emitted signal strength.
		 * \param[in] damp      The empirical dampening parameter.
		 * \result              Distance to the beacon (in meters ?).
		 */
        static double get_distance (double rssi, double txPower, double damp);

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
        static bool TrilatLocation2d(const PointContainer &beaconsPos,
                          const DistancesContainer   &beaconsDist,
                          Point &location);
						  
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
        static bool TrilatLocation3d(const PointContainer &beacons,
                          const DistancesContainer   &beaconsDist,
                          Point &location);
                          
        /** \brief Clone prevState setting new PointMeasurement (position+timestamp) (UNUSED).
         *
         * Clone the ObjectState structure prevState and set the  PointMeasurement data (point+timestamp)
         * to beaconMeasurement in the new structure.
         * Note: this is about structure ObjectState from common_types.h . 
         * Has nothing to do with the class Types::ObjectState from objectstate.h !
         *
         * UNUSED
         *
         * \param[in]  prevState          an ObjectState (from common_types.h) structure to clone
         * \param[in]  beaconMeasurement  a new PointMeasurement (position+timestamp) to set
         * \result                        Cloned prevState with new position+timestamp
         */
        static ObjectState beacon_navigation(const ObjectState &prevState, const PointMeasurement &beaconMeasurement);

        /** \brief Extrapolate a number of timestamped Beacon Measurements to a timestamp ie_time
         *
         *  Apparently this routine interpolates a sequence of timed beacon measurements m to a given time ie_time.
         *  Uses the external routine inxstrapolate1() from "inxtrapolate.h". 
         *  A measurement includes both rssi and txPower.
         *
         *  Note1: BeaconMeasurementsContainer is actually std::list<BeaconMeasurement>
         * 
         *  Note2: What kind of word is "inxtrapolate" or "inxstrapolate" ????
         *  Is it a mix of "interpolate" and "extrapolate" ?
         *
         *  Used in Sensors::Hardware::Beacon.
         *
         *  \param[in] m        A list of measurements
         *  \param[in] ie_time  A tiimetamp to interpolate to
         *  \result             The interpolated result (rssi and txPower)
         */
        static BeaconMeasurement inxtrapolate(const BeaconMeasurementsContainer &m, timestamp_t ie_time); // intra/extrapolation of measurement (rssi) to time ie_time,

        // Support classes
        
        /** \brief This is only used internally in bmath.cpp for extrapolation */
        template <class X, class Y>
        struct BeaconRssiTimeToPoint {
            General::Math::DataFitting::SimplePointType<X, Y> operator() (const BeaconMeasurement &m) const {
                return General::Math::DataFitting::SimplePointType<X, Y>((X)m.timestamp, (Y)m.rssi);
            }
        };
        
        /** \brief This is only used internally in bmath.cpp for extrapolation */
        template <class X, class Y>
        struct BeaconTxPowerTimeToPoint {
            General::Math::DataFitting::SimplePointType<X, Y> operator() (const BeaconMeasurement &m) const {
                return General::Math::DataFitting::SimplePointType<X, Y>((X)m.timestamp, (Y)m.txPower);
            }
        };
};


#endif // BMATH_H
