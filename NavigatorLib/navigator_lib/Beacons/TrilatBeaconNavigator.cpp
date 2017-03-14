//
// Created by  Oleksiy Grechnyev on 3/9/2017.
//

#include "./TrilatBeaconNavigator.h"

namespace Navi {
    namespace Beacons {

        Math::Position3D &TrilatBeaconNavigator::process(const BeaconReceivedData & brd) {
            // TODO finish this

            // Check the timelines of all active processors, restart if needed
            // This is done for all beacons, not only for the beacon of the current brd
            for (const auto & pair: beaconProcessorList){

                BeaconProcessor & processor = *pair.second;
                if (processor.isActive()){
                    double t = processor.getLastTimeStamp(); // Last measurement of this beacon, aka old timestamp

                    // The correct new timestamp lies between t and t + BEACON_TIMEOUT
                    if (brd.timestamp < t || brd.timestamp > t + BEACON_TIMEOUT)
                        processor.reset(); // Reset every processsor with wrong timestamp
                }
            }

            // Find the beacon with this uid
            auto search = beaconProcessorList.find(brd.uid);

            // Do trilateration if the uid is correct
            if (search != beaconProcessorList.end()){
                
                for (const auto & pair: beaconProcessorList){

                }

            }

            return lastPosition;
        }
    }
}