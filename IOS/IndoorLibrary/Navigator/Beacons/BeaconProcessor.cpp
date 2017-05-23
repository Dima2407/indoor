//
// Created by  Oleksiy Grechnyev on 3/29/2017.
//

#include "Navigator/Beacons/BeaconProcessor.h"

namespace Navigator {
    namespace Beacons {

        double BeaconProcessor::process(double rssi, double timeStamp) {
            // Filter rssi
            IFilter::Value rssiPair(rssi, timeStamp);

            if (rssiFilter != nullptr) // Apply rssi filter if defined
                rssiPair = rssiFilter->process(rssiPair);

            // Calculate raw distance from the filtered RSSI
            double distance = calculateDistance(rssiPair.val);

            IFilter::Value distPair(distance, rssiPair.timeStamp);

            if (distanceFilter != nullptr) // Apply distance filter if defined
                distPair = distanceFilter->process(distPair);

            distance = distPair.val;

            active = true; // We are now active
            lastTimeStamp = distPair.timeStamp; // Save timestamp
            lastDistance = distance; // Save distance

            return distance;
        }
    }
}