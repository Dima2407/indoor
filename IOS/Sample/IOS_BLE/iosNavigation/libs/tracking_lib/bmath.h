#ifndef MATH_H
#define MATH_H

#include "common_types.h"
#include "inxtrapolate.h"
#include <vector>

class BMath {
    public:
        static double get_distance (double rssi, double txPower, double damp);

        static bool TrilatLocation2d(const PointContainer &beaconsPos,
                          const DistancesContainer   &beaconsDist,
                          Point &location);

        static bool TrilatLocation3d(const PointContainer &beacons,
                          const DistancesContainer   &beaconsDist,
                          Point &location);

        static ObjectState beacon_navigation(const ObjectState &prevState, const PointMeasurement &beaconMeasurement);

        static BeaconMeasurement inxtrapolate(const BeaconMeasurementsContainer &m, timestamp_t ie_time); // intra/extrapolation of measurement (rssi) to time ie_time,

        // Support classes

        template <class X, class Y>
        struct BeaconRssiTimeToPoint {
            General::Math::DataFitting::SimplePointType<X, Y> operator() (const BeaconMeasurement &m) const {
                return General::Math::DataFitting::SimplePointType<X, Y>((X)m.timestamp, (Y)m.rssi);
            }
        };
        template <class X, class Y>
        struct BeaconTxPowerTimeToPoint {
            General::Math::DataFitting::SimplePointType<X, Y> operator() (const BeaconMeasurement &m) const {
                return General::Math::DataFitting::SimplePointType<X, Y>((X)m.timestamp, (Y)m.txPower);
            }
        };
};


#endif // MATH_H
