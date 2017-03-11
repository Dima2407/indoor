//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#pragma once

#include <string>

#include "./BeaconUID.h"
#include "./Position3D.h"

namespace navi {
    namespace beacon {
        /// Beacon position, rssi and damp
        class Beacon {
        public:
            //---------------------------------------------
            // Public methods
            //---------------------------------------------

            /// Constructor
            Beacon(const BeaconUID &uid, double txPower, double damp, const Position3D &pos, const std::string &meta) :
                    uid(uid),
                    txPower(txPower),
                    damp(damp),
                    pos(pos),
                    meta(meta) {}

            // Getters

            const BeaconUID &getUid() const
            {
                return uid;
            }

            double getTxPower() const
            {
                return txPower;
            }

            double getDamp() const
            {
                return damp;
            }

            const Position3D &getPos() const
            {
                return pos;
            }

            const std::string &getMeta() const
            {
                return meta;
            }

            //---------------------------------------------
            // Private fields
            //---------------------------------------------
        private:
            /// Unique ID of the beacon
            BeaconUID uid;

            /// Beacon TXPower (basically, power of the emission)
            double txPower;

            /// Damping parameter (=2 for vacuum)
            double damp;

            /// Beacon position
            Position3D pos;

            /// Some extra data if needed, don't ask
            std::string meta;

        };
    }
}
