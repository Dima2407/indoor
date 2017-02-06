#pragma warning(push)
#pragma warning(disable : 4244) // Disable warnings from external toolkit.
#include "bmath.h"
#include "Eigen/Dense"
#pragma warning(pop)

double BMath::get_distance (double rssi, double txPower, double damp) {
#if defined(DEBUG_MODE)
#   if defined(ASTUDIO)
    damp = 4;
#   endif
#endif
    assert(damp != 0);
    return pow(10.0, (txPower - rssi) / (10.0 * damp));
}

// ===================================================
// Realization of is a modification of waynewang (2014) sources:
// https://github.com/Wayne82/Trilateration
// (Created by waynewang on 19/4/14. Copyright (c) 2014 waynewang. All rights reserved.)
// ===================================================
bool BMath::TrilatLocation2d(const PointContainer &beaconsPos,
                      const DistancesContainer   &beaconsDist,
                      Point& location) {

    // To locate position on a 2d plan, have to get at least 3 becaons,
    // otherwise return false.
    if (beaconsPos.size() < 3 || (beaconsPos.size() != beaconsDist.size())) {
        return false;
    }

    // Define the matrix that we are going to use
    size_t count = beaconsPos.size();
    size_t rows = count * (count - 1) / 2;
    Eigen::MatrixXd m(rows, 2);
    Eigen::VectorXd b(rows);

    // Fill in matrix according to the equations
    size_t row = 0;
    double x1, x2, y1, y2, r1, r2;
    Point beacon1, beacon2;

    PointContainer::const_iterator cit_i;
    PointContainer::const_iterator cit_j;
    DistancesContainer::const_iterator dit_i;
    DistancesContainer::const_iterator dit_j;

    for (cit_i = beaconsPos.begin(), dit_i = beaconsDist.begin();
         cit_i != beaconsPos.end();
         ++cit_i, ++dit_i)
    {
        beacon1 = *cit_i;
        cit_j = cit_i;
        dit_j = dit_i;
        for (++cit_j, ++dit_j;
             cit_j != beaconsPos.end();
             ++cit_j, ++dit_j)
        {
            beacon2 = *cit_j;
            x1 = beacon1.x, y1 = beacon1.y;
            x2 = beacon2.x, y2 = beacon2.y;
            r1 = *dit_i;
            r2 = *dit_j;
            m(row, 0) = x1 - x2;
            m(row, 1) = y1 - y2;
            b(row) = ((std::pow(x1, 2) - std::pow(x2, 2)) +
                      (std::pow(y1, 2) - std::pow(y2, 2)) -
                      (std::pow(r1, 2) - std::pow(r2, 2))) / 2;
            row++;
        }
    }

    // Then calculate to solve the equations, using the least square solution
    Eigen::Vector2d pos = m.jacobiSvd(Eigen::ComputeThinU|Eigen::ComputeThinV).solve(b);

    location.x = pos(0);
    location.y = pos(1);
    location.z = 0;

    return true;
}

// ===================================================
// Realization of is a modification of waynewang (2014) sources:
// https://github.com/Wayne82/Trilateration
// (Created by waynewang on 19/4/14. Copyright (c) 2014 waynewang. All rights reserved.)
// ===================================================
bool BMath::TrilatLocation3d(const PointContainer &beaconsPos,
                      const DistancesContainer   &beaconsDist,
                      Point& location) {
    /*// To locate position in a 3D space, have to get at least 4 becaons,
    // otherwise return false.*/

    if (beaconsPos.size() < 4 || (beaconsPos.size() != beaconsDist.size())) {
        return false;
    }

    // Define the matrix that we are going to use
    size_t count = beaconsPos.size();
    size_t rows = count * (count - 1) / 2;
    Eigen::MatrixXd m(rows, 3);
    Eigen::VectorXd b(rows);

    // Fill in matrix according to the equations
    size_t row = 0;
    double x1, x2, y1, y2, z1, z2, r1, r2;
    Point beacon1, beacon2;

    PointContainer::const_iterator cit_i;
    PointContainer::const_iterator cit_j;
    DistancesContainer::const_iterator dit_i;
    DistancesContainer::const_iterator dit_j;

    for (cit_i = beaconsPos.begin(), dit_i = beaconsDist.begin();
         cit_i != beaconsPos.end();
         ++cit_i, ++dit_i)
    {
        beacon1 = *cit_i;
        cit_j = cit_i;
        dit_j = dit_i;
        for (++cit_j, ++dit_j;
             cit_j != beaconsPos.end();
             ++cit_j, ++dit_j)
        {
            beacon2 = *cit_j;
            x1 = beacon1.x, y1 = beacon1.y; z1 = beacon1.z;
            x2 = beacon2.x, y2 = beacon2.y; z2 = beacon2.z;
            r1 = *dit_i;
            r2 = *dit_j;
            m(row, 0) = x1 - x2;
            m(row, 1) = y1 - y2;
            m(row, 2) = z1 - z2;
            b(row) = ((std::pow(x1, 2) - std::pow(x2, 2)) +
                      (std::pow(y1, 2) - std::pow(y2, 2)) +
                      (std::pow(z1, 2) - std::pow(z2, 2)) -
                      (std::pow(r1, 2) - std::pow(r2, 2))) / 2;
            row++;
        }
    }

    // Then calculate to solve the equations, using the least square solution
    Eigen::Vector3d pos = m.jacobiSvd(Eigen::ComputeThinU|Eigen::ComputeThinV).solve(b);

    location.x = pos(0);
    location.y = pos(1);
    location.z = pos(2);

    return true;
}

ObjectState BMath::beacon_navigation(const ObjectState &prevState, const PointMeasurement &beaconMeasurement) {
    ObjectState newState = prevState;
    newState.timestamp = beaconMeasurement.timestamp;
    newState.position  = beaconMeasurement.position;

    return newState;
}

BeaconMeasurement BMath::inxtrapolate(const BeaconMeasurementsContainer &mc, timestamp_t ie_time) {
    BeaconMeasurement m;
    if (mc.size() > 0) {
        double rssi = 1.0;
        double tx_power = 1.0;
        if (mc.size() > 1) {
            rssi     = General::Math::DataFitting::LinearInxtrapolator::inxstrapolate1(mc, ie_time, BMath::BeaconRssiTimeToPoint<timestamp_t, double>());
            tx_power = General::Math::DataFitting::LinearInxtrapolator::inxstrapolate1(mc, ie_time, BMath::BeaconTxPowerTimeToPoint<timestamp_t, double>());
        } else {
            rssi = mc.begin()->rssi;
            tx_power = mc.begin()->txPower;
        }
        m.rssi = rssi;
        m.txPower = tx_power;
        m.hash = mc.begin()->hash;
        m.timestamp = ie_time;
    }

    return m;
}
