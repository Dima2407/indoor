#include <unordered_set>

#include <Navigator/Math/Trilat/trilat.h>
#include <Navigator/Math/Trilat/TrilatRecord.h>

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
        checkTimeout(timeStamp);

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

        lastPosition = postProcess(lastPosition); // Use mesh+mask
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

void KalmanBeaconNavigator::runTrilat() {
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

//    std::cout << "Trilat for " << records.size() << " beacons !" << std::endl;

    // Select useNearest nearest beacons only
    if (config.useNearest > 0 && config.useNearest < records.size()) {
        // Sort
        std::sort(records.begin(), records.end());
        records.resize(config.useNearest); // Use only useNearest beacons
    }

    // Run trilateration if there are at least 3 (or 4 for 3D) active beacon processors
    // Result is written to lastPosition
    if (config.use3DTrilat) {
        if (records.size() >= 4)
            lastPosition = Math::Trilat::trilatLocation3d(records);
    } else {
        if (records.size() >= 3)
            lastPosition = Math::Trilat::trilatLocation2d(records);
    }
}
//====================================================

void KalmanBeaconNavigator::processPacket(const BeaconReceivedData &brd) {
    /// The tolerance when comparing the current timestamp to the old one
    constexpr double NEGATIVE_TOLERANCE = 1.0e-3;
    // Find the beacon processor with uid from brd
    // Do nothing (ignore the packet) if not found
    auto search = beaconProcessorList.find(brd.uid);

    if (search != beaconProcessorList.end()) {
        // Reset if the timestamp is negative
        BeaconProcessor &processor = *(search->second);

        // EXCEPTION if going back in time (timestamp < last timestamp)
        if (brd.timestamp < processor.getLastTimeStamp() - NEGATIVE_TOLERANCE)
            throw std::runtime_error("TrilatBeaconNavigator: Travelling back in time is forbidden.");

        // Process the data packet brd with the respective beacon
        // This makes the processor active if it was not active before
        processor.process(brd.rssi, brd.timestamp);
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

Math::Position3D KalmanBeaconNavigator::postProcess(Math::Position3D pos)
{
    // Postprocess using mesh+masktable
    if (mesh != nullptr && config.useMeshMask)
        return mesh->process(pos);
    else if (mesh != nullptr && config.useMapEdges)
        return mesh->checkEdges(pos);
    else
        return pos;
}
//====================================================

}
}
