//
// Created by  Oleksiy Grechnyev on 3/12/2017.
//

#pragma once

#include <memory>
#include <cmath>


#include "Navigator/Math/Filter/IFilter.h"
#include "Navigator/Math/Filter/NoFilter.h"
#include "Navigator/Beacons/Beacon.h"


namespace Navigator {
    namespace Beacons {

        /** @brief Calculates distance as a function of RSSI for a beacon
         *
         * @startuml
         * class BeaconProcessor {
         * - beacon : Beacon
         * - rssiFilter : std::shared_ptr<IFilter>
         * - distanceFilter : std::shared_ptr<IFilter>
         * - lastTimeStamp : double
         * - lastDistance : double
         * - active : bool
         * --
         * + BeaconProcessor(beacon : const Beacon &,
         *                  rssiFilter : const std::shared_ptr<IFilter> &,
         *                  distanceFilter : const std::shared_ptr<IFilter> &)
         * ..
         * + process(rssi : double, timeStamp : double) : double
         * + reset() : void
         * + reset(newBeacon : const Beacon &) : void
         * ..
         * + getters()
         * ..
         * - const calculateDistance(rssi : double ) : double
         * }
         * note bottom
         * // Beacon Processor //
         * // Calculates distance as a function of RSSI for a beacon //
         * // using both RSSI filter and distance filter //
         * // Includes beacon data, and shared_ptr's to the filters //
         * // Keeps last timestamp and distance //
         * endnote
         * @enduml
         *
         */
        class BeaconProcessor
        {
        public:  // == TYPES ==
            using IFilter = Navigator::Math::Filter::IFilter;
            using NoFilter = Navigator::Math::Filter::NoFilter;
            
        public:
            /** @brief Constructor
             *
             *  Note: While nullptr can be used to switch off a filter, it
             *  is better to use std::make_shared<Filter::NoFilter>()
             *
             * @param[in]  beacon           Beacon data (uid, location, txPower, damp)
             * @param[in]  rssiFilter       RSSI filter (nullptr = for no filter)
             * @param[in]  distanceFilter   distance filter (nullptr = for no filter)
             */
            BeaconProcessor(const Beacon &beacon,
                            const std::shared_ptr<IFilter> &rssiFilter     = std::make_shared<NoFilter>(),
                            const std::shared_ptr<IFilter> &distanceFilter = std::make_shared<NoFilter>()
                ) : beacon(beacon),
                    rssiFilter(rssiFilter),
                    distanceFilter(distanceFilter) {}


            //---------------------------------------------
            // Public methods
            //---------------------------------------------

            /** @brief Calculate distance from rssi using filters
             *
             * Both RSSI and distance filters are used if defined
             * The timeStamp is saved as lastTimeStamp
             *
             * @param[in]   rssi       The input RSSI (in dBm or something like this)
             * @param[in]   timeStamp  The input timestamp
             * @return                 The distance in meters
             */
            double process(double rssi, double timeStamp);

            /// Reset the filters
            void reset()
            {

                active = false; // No more active

                if (rssiFilter != nullptr) // Reset if not null
                    rssiFilter -> reset();

                if (distanceFilter != nullptr) // Reset if not null
                    distanceFilter -> reset();
            }

            /// Reset the filters and update beacon data
            void reset(const Beacon & newBeacon)
            {
                beacon = newBeacon; // Set new Beacon
                reset(); // Reset the filters
            }

            /// Reset processor with new filters
            void changeFilters(const std::shared_ptr<IFilter> &rssiFilter,
                               const std::shared_ptr<IFilter> &distanceFilter){

                reset();
                lastTimeStamp = nan("");
                lastDistance = nan("");

                this->rssiFilter = rssiFilter;
                this->distanceFilter = distanceFilter;
            }

            //==================== Getters

            const Beacon &getBeacon() const
            {
                return beacon;
            }

            double getLastTimeStamp() const {
                return lastTimeStamp;
            }

            double getLastRssi() const {
                return lastRssi;
            }

            double getLastDistance() const {
                return lastDistance;
            }

            const std::shared_ptr<IFilter> &getRssiFilter() const {
                return rssiFilter;
            }

            const std::shared_ptr<IFilter> &getDistanceFilter() const {
                return distanceFilter;
            }

            bool isActive() const {
                return active;
            }

        protected:
            //---------------------------------------------
            // Protected methods
            //---------------------------------------------

            /** @brief The raw distance function, no filters
             *
             *  The formula is
             *  distance = 10^((txpower-rssi) / (10*damp))
             *
             *  10 in the denominator comes from the definition of dB
             *  The ideal (vacuum) damp is 2.0
             *
             * @param[in]   rssi   Input RSSI (in dBm or something like this)
             * @return             Distance (im meters)
             */
            double calculateDistance(double rssi) const
            {
                double dist = pow(10.0, (beacon.getTxPower() - rssi) / (10.0 * beacon.getDamp()));
                if (dist < 1.0)  // 1-meter corrrection
                    dist = 1.0;
                return dist;
            }
            //---------------------------------------------
            // Private fields
            //---------------------------------------------

            /// The Beacon data object
            Beacon beacon;

            /// The rssi filter (1st filter)
            std::shared_ptr<Math::Filter::IFilter> rssiFilter;

            /// The distance filter (2nd filter)
            std::shared_ptr<Math::Filter::IFilter> distanceFilter;

            /// The last timestamp
            double lastTimeStamp = nan("");

            /// The last distance calculated
            double lastDistance = nan("");

            /// The last filtered RSSI
            double lastRssi = nan("");

            /// Is the beacon active (has last distance ,timestamp) ?
            bool active = false;
        };

    }
}
