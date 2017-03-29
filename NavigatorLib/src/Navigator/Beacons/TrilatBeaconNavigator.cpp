//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#include "Navigator/Beacons/TrilatBeaconNavigator.h"

#include "Navigator/Math/Trilat/Trilat.h"

namespace Navigator {
    namespace Beacons {


        const Math::Position3D &TrilatBeaconNavigator::process(const BeaconReceivedData &brd) {

            /// The tolerance when comparing the current timestamp to the old one
            constexpr double NEGATIVE_TOLERANCE = 1.0e-3;

            //----------------------------
            // Check the timelines of all active processors, reset it if the beacon is inactive
            // For more than beaconTimeout seconds
            // This is done for all beacons, not only for the beacon of the current brd
            //
            // Also reset the beacon with packet's UID if the timeline
            // Is smaller than the previos one (travelling back in time)
            // With tolerance NEGATIVE_TOLERANCE
            for (const auto &pair: beaconProcessorList) {
                BeaconProcessor &processor = *pair.second;
                if (processor.isActive()) {
                    double t = processor.getLastTimeStamp(); // Last measurement of this beacon, aka old timestamp

                    // The correct new timestamp must be < t + beaconTimeout
                    // If timed out, reset the processor, erasing filters history
                    // Note: reset makes a processor inactive
                    if (brd.timestamp > t + beaconTimeout)
                        processor.reset(); // Reset the processsor if timed out

                    if ((brd.uid == processor.getBeacon().getUid()) && (brd.timestamp < t - NEGATIVE_TOLERANCE))
                        processor.reset(); // Reset if going back in time

                }
            }

            //----------------------------
            // Find the beacon processor with uid from brd
            // Run rssi+timestamp from brd through this processor
            // After that, run the trilateration

            auto search = beaconProcessorList.find(brd.uid);

            if (search != beaconProcessorList.end()) {
                // Process the data packet brd with the respective beacon
                // This makes the processor active if it was not before
                search->second->process(brd.rssi, brd.timestamp);
            }

            // Now run the trilateration

            runTrilat();

            return lastPosition;
        }

//====================================================

        void TrilatBeaconNavigator::runTrilat() {
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

            // Run trilateration if there are at least 3 (or 4 for 3D) active beacon processors
            // Result is written to lastPosition

            if (use3DTrilat) {
                if (beaconPositions.size() >= 4)
                    lastPosition = Math::Trilat::trilatLocation3d(beaconPositions, beaconDistances);
            } else {
                if (beaconPositions.size() >= 3)
                    lastPosition = Math::Trilat::trilatLocation2d(beaconPositions, beaconDistances);
            }
        }

//====================================================

    }
}