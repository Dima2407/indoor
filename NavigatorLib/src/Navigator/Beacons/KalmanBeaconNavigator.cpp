#include <unordered_set>

#include "Navigator/Beacons/KalmanBeaconNavigator.h"

// By Oleksiy Grechnyev

namespace Navigator {
namespace Beacons {
//====================================================
const Math::Position3D &KalmanBeaconNavigator::process(const std::vector<BeaconReceivedData> &brds)
{
    using namespace std;
    if (! brds.empty()) {
        unordered_set<BeaconUID> uids;  // UIDs of all received packets

        // Timestamp of the first element is forced as the common one
        double timeStamp = brds[0].timestamp;

        // Check for timeout: only once
//        checkTimeout(timeStamp);

        // Process each packet in turn
        for (BeaconReceivedData b : brds) {
            // We make a copy to modify it
            b.timestamp = timeStamp; // Force the common timestamp
            processPacket(b);
            uids.insert(b.uid); // Store the uid in set
        }

        // Now run prediction for all active beacons without a packet
        for (const auto &pair: beaconProcessorList) {
            KalmanBeaconProcessor &processor = *pair.second;
            if (processor.isActive() && uids.count(processor.getBeacon().getUid()) == 0) {
                processor.processOnlyPredict(timeStamp);
            }
        }

        // Now run the trilateration: only once
        runTrilat();
    }
    return lastPosition;
}

//====================================================
const std::shared_ptr<BeaconProcessor> KalmanBeaconNavigator::findProcessorByUid(const BeaconUID &uid) const
{
    auto search = beaconProcessorList.find(uid);

    if (search == beaconProcessorList.end()) {
        return nullptr;
    } else {
        return (*search).second;
    }
}
//====================================================
void KalmanBeaconNavigator::reset()
{
    // Reset variables
    lastPosition = Math::Position3D();

    // Reset filters for each beacon
    for( auto & proc : beaconProcessorList ){
        proc.second->reset();
    }
}
//====================================================
        void KalmanBeaconNavigator::checkTimeout(double timeStamp) {

            //----------------------------
            // Check the timelines of all active processors, reset it if the beacon is inactive
            // For more than config.hardTimeout seconds
            // This is done for all beacons
            for (const auto &pair: beaconProcessorList) {
                KalmanBeaconProcessor &processor = *pair.second;
                if (processor.isActive()) {
                    double t = processor.getLastTimeStamp(); // Last measurement of this beacon, aka old timestamp

                    // The correct new timestamp must be < t + beaconTimeout
                    // If timed out, reset the processor, erasing filters history
                    // Note: reset makes a processor inactive
                    if (timeStamp > t + config.hardTimeout)
                        processor.reset(); // Reset the processsor if timed out
                }
            }
        }
//====================================================

}
}
