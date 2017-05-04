//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#include <algorithm>

#include "Navigator/Beacons/TrilatBeaconNavigator.h"

#include "Navigator/Math/Trilat/trilat.h"

namespace Navigator {
    namespace Beacons {


        const Math::Position3D &TrilatBeaconNavigator::process(const BeaconReceivedData &brd) {

            // Check for timeout
            checkTimeout(brd.timestamp);

            // Process the packet
            processPacket(brd);

            // Now run the trilateration
            runTrilat();

            return lastPosition;
        }

//====================================================

        void TrilatBeaconNavigator::runTrilat() {
            using namespace Math;
            using namespace Math::Trilat;

            // Trilateration records (position, distance) each
            std::vector<TrilatRecord> records;

            // Now loop over all active beacon processors again
            // Note: only active processors have meaningful lastDistance
            for (const auto &pair: beaconProcessorList) {
                BeaconProcessor &processor = *pair.second;
                if (processor.isActive()) {
                    records.push_back(TrilatRecord(processor.getBeacon().getPos(), processor.getLastDistance()));
                }
            }

            // Select useNearest nearest beacons only
            if (useNearest > 0 && useNearest < records.size()) {
                // Sort
                std::sort(records.begin(), records.end());
                records.resize(useNearest); // Use only useNearest beacons
            }

            // Run trilateration if there are at least 3 (or 4 for 3D) active beacon processors
            // Result is written to lastPosition
            if (use3DTrilat) {
                if (records.size() >= 4)
                    lastPosition = Math::Trilat::trilatLocation3d(records);
            } else {
                if (records.size() >= 3)
                    lastPosition = Math::Trilat::trilatLocation2d(records);
            }
        }
//====================================================

        void TrilatBeaconNavigator::processPacket(const BeaconReceivedData &brd) {
            /// The tolerance when comparing the current timestamp to the old one
            constexpr double NEGATIVE_TOLERANCE = 1.0e-3;


            //----------------------------
            // Find the beacon processor with uid from brd
            // Run rssi+timestamp from brd through this processor
            // Do nothing (ignore the packet) if not found

            auto search = beaconProcessorList.find(brd.uid);

            if (search != beaconProcessorList.end()) {
                // Rreset if the timestamp is negative
                BeaconProcessor &processor = *(search->second);

                // EXCEPTION if going back in time (timestamp < last timestamp)
                // Previously reset, now exception
                if (brd.timestamp < processor.getLastTimeStamp() - NEGATIVE_TOLERANCE) {
//                    processor.reset();
                    throw std::runtime_error("TrilatBeaconNavigator: Travelling back in time is forbidden.");
                }

                // Process the data packet brd with the respective beacon
                // This makes the processor active if it was not active before
                processor.process(brd.rssi, brd.timestamp);
            }
        }
//====================================================

        void TrilatBeaconNavigator::checkTimeout(double timeStamp) {

            //----------------------------
            // Check the timelines of all active processors, reset it if the beacon is inactive
            // For more than beaconTimeout seconds
            // This is done for all beacons
            for (const auto &pair: beaconProcessorList) {
                BeaconProcessor &processor = *pair.second;
                if (processor.isActive()) {
                    double t = processor.getLastTimeStamp(); // Last measurement of this beacon, aka old timestamp

                    // The correct new timestamp must be < t + beaconTimeout
                    // If timed out, reset the processor, erasing filters history
                    // Note: reset makes a processor inactive
                    if (timeStamp > t + beaconTimeout)
                        processor.reset(); // Reset the processsor if timed out

                }
            }

        }
//====================================================

        const Math::Position3D &TrilatBeaconNavigator::process(const std::vector<BeaconReceivedData> &brds) {
            if (! brds.empty()) {
                // Timestamp of the first element is forced as the common one
                double timeStamp = brds[0].timestamp;

                // Check for timeout: only once
                checkTimeout(timeStamp);

                // Process each packet in turn
                for (BeaconReceivedData b : brds) {
                    // We make a copy to modify it
                    b.timestamp = timeStamp; // Force the common timestamp
                    processPacket(b);
                }

                // Now run the trilateration: only once
                runTrilat();
            }

            return lastPosition;
        }
//====================================================

        const std::shared_ptr<BeaconProcessor> TrilatBeaconNavigator::findProcessorByUid(const BeaconUID & uid) const{
            auto search = beaconProcessorList.find(uid);

            if (search == beaconProcessorList.end()) {
                return nullptr;
            } else {
                return (*search).second;
            }
        }

//====================================================

    }
}
