//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#include "Navigator/Beacons/TrilatBeaconNavigator.h"

#include "Navigator/Math/Trilat/trilat.h"

namespace Navi {
    namespace Beacons {

        const Math::Position3D &TrilatBeaconNavigator::process(const BeaconReceivedData &brd) {


            //----------------------------
            // Check the timelines of all active processors, restart if needed
            // This is done for all beacons, not only for the beacon of the current brd
            for (const auto &pair: beaconProcessorList) {

                BeaconProcessor &processor = *pair.second;
                if (processor.isActive()) {
                    double t = processor.getLastTimeStamp(); // Last measurement of this beacon, aka old timestamp

                    // The correct new timestamp lies between t and t + BEACON_TIMEOUT
                    // If incorrect, reset the processor, erasing filters history
                    // Note: reset makes a processor inactive
                    if (brd.timestamp < t || brd.timestamp > t + BEACON_TIMEOUT)
                        processor.reset(); // Reset every processsor with wrong timestamp
                }
            }

            //----------------------------
            // Find the beacon processor with uid from brd
            // Run rssi+timestamp from brd through this processor
            // After that, run the trilateration

            auto search = beaconProcessorList.find(brd.uid);

            if (search != beaconProcessorList.end()) {
                // Process the data package brd with the respective beacon
                // This makes the processor active if it was not before
                search->second->process(brd.rssi, brd.timestamp);

                //----------------------------
                // Now run the trilateration

                // Beacon positions of all active processors in trilateration format
                std::vector<Math::Position3D> beaconPositions;

                // Distances to the beacons
                std::vector<double> beaconDistances;

                // Now loop over all active beacon processors again
                // Note: only active processors have meaningful lastDistance
                for (const auto &pair: beaconProcessorList) {
                    BeaconProcessor &processor = *pair.second;
                    if (processor.isActive()) {
                        beaconPositions.push_back(processor.getBeacon().getPos()); // Add beacon position
                        beaconDistances.push_back(processor.getLastDistance()); // Add distance
                    }
                }

                // Run trilateration if there are at least 3 active beacon processors
                // Result is written to lastPosition
                if (beaconPositions.size() >= 3)
                    Math::Trilat::trilatLocation2d(beaconPositions, beaconDistances, lastPosition);
            }

            return lastPosition;
        }
    }
}