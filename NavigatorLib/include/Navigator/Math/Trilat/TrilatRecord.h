//
// Created by  Oleksiy Grechnyev on 3/29/2017.
//

#pragma once

#include <cmath>


#include "Navigator/Math/Position3D.h"
#include "Navigator/Beacons/BeaconUID.h"


namespace Navigator {
    namespace Math {
        namespace Trilat {

            /// Data record (position, distance) used for trilateration
            struct TrilatRecord {
                TrilatRecord(const Position3D &pos,
                             double rssi,
                             double dist,
                             const Beacons::BeaconUID & uid = Beacons::BeaconUID()) :
                        pos(pos), rssi(rssi), dist(dist), uid(uid) {}

                TrilatRecord() {}

                /// Relation for sorting
                bool operator<(const TrilatRecord &rhs) const {
//                    return dist < rhs.dist;   // Old smaller distance
                    return rssi > rhs.rssi;   // New: larger RSSI (stronger signal)
                }

                Position3D pos;
                double rssi = std::nan("");
                double dist = std::nan("");
                Beacons::BeaconUID uid;
            };

        }
    }
}

